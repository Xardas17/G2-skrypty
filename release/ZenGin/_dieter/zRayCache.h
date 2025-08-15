/******************************************************************************** 
 
     $Workfile:: zRayCache.h          $                $Date:: 8.01.01 20:44    $
     $Revision:: 5                    $             $Modtime:: 8.01.01 20:43    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Cache to accelerate TraceRay calls
   created: 25.5.2000

 * $Log: /current_work/zengin_work/_Dieter/zRayCache.h $
 * 
 * 5     8.01.01 20:44 Hildebrandt
 * 
 * 4     22.09.00 17:14 Moos
 * 
 * 3     22.09.00 14:17 Moos
 * 
 * 2     21.09.00 20:57 Moos
 * 
 * 1     21.09.00 18:51 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 8.01.01 20:43 $)

#ifndef __ZRAYCACHE_H__
#define __ZRAYCACHE_H__

#ifndef __ZPLUECKER_H__
#include <zPluecker.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

class zCRayCacheElement;
class zCBspBase;
class zCBspLeaf;

class zCRayCache{
public:
    zCRayCache():first(0),next(s_anchor){s_anchor = this;}
    ~zCRayCache();

    // zREAL Quality(const zVEC3 &a, const zVEC3 &e){return -(start-a).Length2() - (stop-e).Length2();} // not needed anymore

    void StartTraceRay(const zVEC3 &start, const zVEC3 &stop);  // must be called before a new ray is cast
    void StopTraceRay();                                        // dito for after
    void NextNode(const zCBspBase *leaf);                       // to be called at every BSP node the ray passes

    zCArray<zWORD> &HitList() const;  // the list of indices of polygons possibly hit by the ray in the current leaf
    char *Hit() const;                // the same info as array of flags (almost obsolete, will be removed after the testing phase)

    static void NodeDeleted(zCBspLeaf *leaf);  // to be cast by the destructor of zCBspLeaf (cleanup)

    static zREAL LastTraceRayEffort();     // returns 0: no real tests were performed .... 1:all possible real tests were performed

private:
    zCRayCacheElement   *first;            // the cache elements
    zCRayCache          *next;             // linked list

    static zCRayCacheElement *s_current;   // the current bsp node this ray is cast through

    static zVEC3 s_start, s_stop;          // coordinates of ray currently cast 

    static zCRayCache *s_anchor;           // anchor of the linked list of ray caches

friend class zCBspBase;
friend class zCBspTree;
};

#endif