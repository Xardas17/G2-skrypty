/******************************************************************************** 
 
     $Workfile:: zRayCache.cpp        $                $Date:: 7.11.00 17:23    $
     $Revision:: 7                    $             $Modtime:: 7.11.00 16:28    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Cache to accelerate TraceRay calls
   created: 25.5.2000

 * $Log: /current_work/zengin_work/_Dieter/zRayCache.cpp $
 * 
 * 7     7.11.00 17:23 Hildebrandt
 * 
 * 6     26.09.00 11:21 Moos
 * 
 * 5     22.09.00 17:14 Moos
 * 
 * 4     22.09.00 14:17 Moos
 * 
 * 3     21.09.00 22:12 Moos
 * 
 * 2     21.09.00 20:57 Moos
 * 
 * 1     21.09.00 18:51 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 7.11.00 16:28 $)

#include <zRayCache.h>
#include <zBsp.h>
#include <z3d.h>
#include <zWorld.h>
#include <zGrafix.h>



/*

Funktion des Ray-Cache:

Prinzip:
Für jedes Polygon im BSP-Tree werden die Plücker-Koordinaten p[i] der Kanten berechnet und normiert. 
(natürlich nur bei Bedarf) Ein Strahl mit Plücker-Koordinaten q geht genau dann durch dieses Polygon,
wenn  q * p[i] >=0 für alle i gilt. Erfreulicherweise gilt für das Plücker-Produkt * die Ungleichung

x * p <= |x| * |p|

und da die p[i] normiert sind, gilt speziell

x * p[i] <= |x|.

Für alle x. Nach dem ersten Strahltest mit q wird das Minimum M der q*p[i] gespeichert. Castet man nun einen 
zweiten Strahl q', so gilt nach obiger Ungleichung (setzte q-q' für x ein)

    q' * p[i] - q * p[i] = (q´-q) * p[i] <= |q´-q|

=>  q´ * p[i]                            <= |q´-q| + q * p[i]

also speziell für das i, für das q*p[i] minimal (also gleich M) wird:

   min q' * p[] <= q' *p[i] <= |q'-q| + q * p[i] = |q'- q| + M.

Das neue Minimum M´ ist also um höchstens |q'-q| größer als das alte M. Analog kann man zeigen, dass das M´
um höchstens |q'-q| kleiner ist als das alte (einfach q und q' austauschen).

Anstatt den Ray-Polygontest jedesmal neu zu berechnen, merkt sich der Cache daher einfach |M| aus der 
letzten Berechnung; (das Vorzeichen von M entscheidet ja darüber, ob der Strahl das Polygon trifft). Nur, wenn
|q'-q| größer ist als dieses |M|, muss der Volle Test gemacht werden, denn nur dann kann M möglicherweise das 
Vorzeichen Wechseln. Ansonsten kann man einfach statt als neuen Wert für |M|   |M| - |q'-q| eintragen, denn der
Echte Wert ist ja sicher größer.


Tricks:

Die gewählte Längenfunktion |p| ist willkürlich und hat im echtem mathematischen Plückerraum eigentlich keine
Bedeutung. Daher muss man darauf achten (für die Effizienz, nicht das prinzipielle Funktionieren des Cache,
dass die Größenordnugnen aller Koordinaten im Bereich von 1 liegen. Dazu werden die Berechnungen für jedes BSP-Leaf
in einem Koordinatensystem durchgeführt, in dem die Bounding-Box des Leafs die Koordinaten (-1,-1,-1),(1,1,1) hat.

Auch wird für jedes BSP-Leaf das absolute Minimum der |M| gespeichert und die Berechnung komplett abgebrochen,
wenn |q'-q| kleiner als dieses Minimum ist.


Verwendung:

Vor jeder Verwendung eines Caches wird die Funktion StartTraceRay(startpunkt, Endpunkt) aufgerufen, danach StopTraceRay.
Bei jedem vom Strahl durchlaufenen BSP-Leafs ruft man erst NextNode(leaf) auf und liest dann die Liste der vom STRAHL 
(der als unendlich lang gedacht werden muss) getroffenen Polygonindices mit HitList() aus.

 */




static int s_CacheElements = 0;  // counter to estimate memory usage ( < 400 bytes per Element)

class zCRayCacheElement{
public:
    zCRayCacheElement(const zCBspLeaf *leaf, zCRayCacheElement **hook); 
    // creates a Cache Element for leaf *leaf and insert it into the linked list at *hook.

    ~zCRayCacheElement();
    // warning: deletes all elements after this (else: memory leaks)

    void JumpBack(zCRayCacheElement **hook); // jumps one position back in the list *hook

    char Hit(int i){return hit[i];}   

private:
    zCPluecker        last_cast_ray; // pluecker coordinates of the ray cast last time

    zCBspLeaf         *leaf;         // the BSP leaf we are responsible for
    zREAL             *updatePolys;  // array
    zREAL              min_updatePolys;
    char              *hit;          // array
    zCArray<zWORD>     hit_list;
    zCRayCacheElement *next;         // single linked list

friend class zCRayCache;

};



/*	------------------------------------------------------------------
	zCRayCacheElement::zCRayCacheElement(const zCBspLeaf *n, zCRayCacheElement **hook)
	7.11.00	[HILDEBRANDT]	
			Anpassung auf Namansaenderung von zCBspLeaf::polyPlueckerAddRef/Release auf
			zCBspLeaf::PolyPlueckerAddRef/Release
	------------------------------------------------------------------ */

zCRayCacheElement::zCRayCacheElement(const zCBspLeaf *n, zCRayCacheElement **hook)
:leaf((zCBspLeaf *)n),
 updatePolys(zNEW_ARRAY(zREAL, n->numPolys)),
 hit(zNEW_ARRAY(char, n->numPolys)), next(NULL)
{
    s_CacheElements++;

    next  = *hook;
    *hook = this;

    for (int i=n->numPolys-1;i>=0;i--){
        updatePolys[i] = -1;
        hit [i] = 0;
    }

    min_updatePolys = -100;
    leaf->PolyPlueckerAddRef();  // Register our use
}


#define CLEARRING 10
static zCBspLeaf *clearring[CLEARRING];
static int        ringpos=0;    

/*	------------------------------------------------------------------
	zCRayCacheElement::~zCRayCacheElement()

	7.11.00	[HILDEBRANDT]	
			Anpassung auf Namansaenderung von zCBspLeaf::polyPlueckerAddRef/Release auf
			zCBspLeaf::PolyPlueckerAddRef/Release
	------------------------------------------------------------------ */

zCRayCacheElement::~zCRayCacheElement(){
    s_CacheElements--;

    delete next;
    delete[] updatePolys;
    delete[] hit;

    next=NULL;
    updatePolys=NULL;
    hit=NULL;

    if (clearring[ringpos])
        clearring[ringpos]->PolyPlueckerRelease();  // Unregister a previous user
    clearring[ringpos] = leaf;                      // and add ourself to the clearring
    ringpos = (ringpos+1) % CLEARRING;

    leaf = NULL;
}



void zCRayCacheElement::JumpBack(zCRayCacheElement **hook){
    zERR_ASSERT(*hook == this);
    zERR_ASSERT(next);

    *hook = next;

    next = next->next;
    (*hook)->next = this;
}







//  *********************************
//            zCRayCache
//  *********************************

// static elements

zCRayCache *zCRayCache::s_anchor = NULL;
zVEC3 zCRayCache::s_start,zCRayCache::s_stop;
zCRayCacheElement *zCRayCache::s_current = NULL;
static zBOOL s_casting=false;  // to check correct start/stop usage

static int saved_ctr=0, hit_ctr=0, miss_ctr=0, all_saved_ctr=0, all_test_ctr=0;

static const int MAX_LASTUSED=100;
static zCRayCache *s_lastUsed[MAX_LASTUSED];
static zWORD       s_lastUsedPos=0;

static zCRayCache *s_clearRunning=NULL; // to gradually cleanup the caches


char *zCRayCache::Hit() const{
    zERR_ASSERT(s_current);
    return s_current->hit;
}

zCArray<zWORD> &zCRayCache::HitList()const{
    zERR_ASSERT(s_current);
    return s_current->hit_list;
}

zREAL zCRayCache::LastTraceRayEffort(){
    return (hit_ctr+miss_ctr)/float(saved_ctr+hit_ctr+miss_ctr+1);
}

void zCRayCache::StartTraceRay(const zVEC3 &a, const zVEC3 &e){
    saved_ctr=hit_ctr=miss_ctr=0;
    zERR_ASSERT_STRICT(!s_casting);
    s_casting = true;
    zERR_ASSERT(!s_current);
    s_start=a;
    s_stop=e;
    s_current=NULL;


    // log use
    s_lastUsed[s_lastUsedPos++] = this;
    s_lastUsedPos %=  MAX_LASTUSED;

    // delete the last CacheElement of an arbitrary RayCache (to avoid memory overflow because of unused RayCaches)
    static int s_counter = 10;
    if (s_counter-- > 0)
        return;  // only continue once every while

    s_counter = 10;

    if (s_clearRunning)
        s_clearRunning = s_clearRunning->next;
    else
        s_clearRunning = s_anchor;

    for (int i = MAX_LASTUSED-1;i>=0;i--)
        if (s_clearRunning == s_lastUsed[i])
            return; // dont touch recently used caches

    if (s_clearRunning  && s_clearRunning->first){
 
        zCRayCacheElement **last = &(s_clearRunning->first);
        while ((*last)->next)
            last = &((*last)->next);

        delete (*last);
        *last = NULL;

    }
}


void zCRayCache::StopTraceRay(){
    zERR_ASSERT_STRICT(s_casting);
    s_casting = false;
    if (s_current){
        delete s_current->next;
        s_current->next=NULL;
        s_current      =NULL;
    }
}


zCRayCache::~zCRayCache(){
    if (s_clearRunning == this){
        s_clearRunning = NULL;
    }

    delete first;
    first=s_current=NULL;

    zCRayCache **run=&s_anchor;
    while (*run){
        if (*run == this)
            *run = next;
        if (*run)
            run = &((*run)->next);
    }

    if (!s_anchor)
    for (int i=CLEARRING-1;i>=0;i--)
        if (clearring[i]){
            clearring[i]->PolyPlueckerRelease();
            clearring[i] = NULL;
        }
    
}

// returns the collision inticator of ray and polygon. <0 -> no collision, > 0 collision
inline float plueckerPoly_Ray_Intersection(const zCPluecker &ray, const zCPluecker *&poly, int numVert){
    float ret=100000;
    for (int i=numVert-1;i>=0;i--){
        float s = ray * *(poly++);
        if (s < ret)
            ret = s;
    }

    return ret;
}



// #define CHECKCACHE

void zCRayCache::NextNode(const zCBspBase *n){
    zERR_ASSERT(n->IsLeaf());
    const zCBspLeaf *leaf = (const zCBspLeaf *)(const void *)n;

    zCRayCacheElement **hook =&s_current;

    if (*hook)
        hook = &(s_current->next);
    else{
        hook = &first;
    }

    if (!(*hook)) // end of cache reached. Create new cache element.
        zNEW(zCRayCacheElement)(leaf,hook);
    else if ((*hook)->leaf != leaf){
        // Oh dear. The treenode we passed last time was different...
        if ((*hook)->next && (*hook)->next->leaf == leaf){
            // luck. It is just the next leaf.
            (*hook)->JumpBack(hook);
        }
        else // no luck. Create new cache element
            zNEW(zCRayCacheElement)(leaf,hook);
    }

    s_current = *hook;

    zERR_ASSERT_STRICT(s_current && s_current->leaf == leaf);
    
    //
    //  Now: update all ray-polygon intersections
    //

    zVEC3 center = (leaf->bbox3D.mins+leaf->bbox3D.maxs)*.5;
    zREAL scale  = 1/(leaf->bbox3D.mins-leaf->bbox3D.maxs).Length();

    zCPluecker ray((s_start-center) * scale,s_stop-s_start);
    //    ray.Normalize();

    zREAL min_updatePolys = s_current->min_updatePolys;
    
    float difference = (ray - s_current->last_cast_ray).Length();
    if (difference < min_updatePolys){
        saved_ctr += leaf->numPolys;
        all_saved_ctr ++;
        return; // nothing to do
    }

    all_test_ctr ++;

    s_current->last_cast_ray = ray;

    zCPolygon ** polys    = leaf->GetPolyList();
    zCPluecker*  pluecker = leaf->polyPluecker;
    zREAL     *  update   = s_current->updatePolys;
    char      *  hit      =    s_current->hit;
    zCArray<zWORD> &hit_list = s_current->hit_list;

    zERR_ASSERT_STRICT(pluecker);

    min_updatePolys = ray.Length()*2;


#ifdef CHECKCACHE_PARANOID
    int j;

    for(j=leaf->numPolys -1; j>=0; j--){
        char h = (hit_list.Search(j) >= 0);
        zERR_ASSERT_STRICT (h == hit[j]);
    }
#endif

    for (int i=leaf->numPolys - 1; i>=0 ; i--){
        if ((update[i] -= difference) < 0){  // only in this case do we need to check further (pluecker magic)
            update[i] = plueckerPoly_Ray_Intersection(ray, pluecker, polys[i]->polyNumVert);
            if (update[i] > 0){

#ifdef CHECKCACHE_VERY_PARANOID
                for(j=leaf->numPolys -1; j>=0; j--){
                    char h = (hit_list.Search(j) >= 0);
                    zERR_ASSERT_STRICT (h == hit[j]);
                }
#endif

                if (!hit[i])
                    hit_list.Insert(i);

                hit[i] = true;
                hit_ctr++;

#ifdef CHECKCACHE_VERY_PARANOID
                for(j=leaf->numPolys -1; j>=0; j--){
                    char h = (hit_list.Search(j) >= 0);
                    zERR_ASSERT_STRICT (h == hit[j]);
                }
#endif
            }
            else{
#ifdef CHECKCACHE_VERY_PARANOID
                for(j=leaf->numPolys -1; j>=0; j--){
                    char h = (hit_list.Search(j) >= 0);
                    zERR_ASSERT_STRICT (h == hit[j]);
                }
#endif
                if (hit[i])
                    hit_list.RemoveIndex(hit_list.Search(i));

                hit[i] = false;
                update[i] = - update[i];
                miss_ctr++;

#ifdef CHECKCACHE_VERY_PARANOID
                for(j=leaf->numPolys -1; j>=0; j--){
                    char h = (hit_list.Search(j) >= 0);
                    zERR_ASSERT_STRICT (h == hit[j]);
                }
#endif
            }
        }
        else{
            saved_ctr++;
            pluecker += polys[i]->polyNumVert;
        }

        if (update[i] < min_updatePolys)
            min_updatePolys = update[i];
    }

#ifdef CHECKCACHE
    int j;

    for(j=leaf->numPolys -1; j>=0; j--){
        char h = (hit_list.Search(j) >= 0);
        zERR_ASSERT_STRICT (h == hit[j]);
    }
#endif

    s_current->min_updatePolys = min_updatePolys;
}

/*	------------------------------------------------------------------
	void zCRayCache::NodeDeleted(zCBspLeaf *leaf)

	7.11.00	[HILDEBRANDT]	
			Anpassung auf Namansaenderung von zCBspLeaf::polyPlueckerAddRef/Release auf
			zCBspLeaf::PolyPlueckerAddRef/Release
	------------------------------------------------------------------ */

void zCRayCache::NodeDeleted(zCBspLeaf *leaf){
    zCRayCache *run = s_anchor;
    while (run){
        zCRayCacheElement **run2 = &(run->first);
        while (*run2){
            if ((*run2)->leaf == leaf){
                zCRayCacheElement *del = *run2;
                *run2 = (*run2)->next;
                del->next = NULL;
                delete del;
            }
         else
            run2 = &((*run2)->next);

        }

        run = run->next;
    }

    for (int i=CLEARRING-1;i>=0;i--)
        if (clearring[i] == leaf){
            leaf->PolyPlueckerRelease();
            clearring[i] = NULL;
        }
}

