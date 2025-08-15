/******************************************************************************** 
 
     $Workfile:: zContainer.cpp       $                $Date:: 6.02.01 11:43    $
     $Revision:: 7                    $             $Modtime:: 6.02.01 10:06    $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ container templates
   created       : 7.9.97

 * $Log: /current_work/ZenGin/_Dieter/zContainer.cpp $
 * 
 * 7     6.02.01 11:43 Moos
 * 
 * 6     1.02.01 13:12 Moos
 * 
 * 5     25.01.01 18:08 Moos
 * 
 * 4     25.01.01 12:14 Moos
 * 
 * 3     22.09.00 19:18 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 7 $ ($Modtime: 6.02.01 10:06 $)

#include <zcore.h>

#include <search.h>
#include <memory.h>
#include <zcontainer.h>
#include <zlist.h>

// [Moos] damit die MemPools als allererstes initialisiert werden
#pragma warning ( disable:4073)
#pragma init_seg(lib)

int zArraySortDefaultCompare (const void* ele1,const void* ele2) {
	if (*((unsigned int*)ele1)<(*(unsigned int*)ele2))	return -1;
	if (*((unsigned int*)ele1)>(*(unsigned int*)ele2))	return +1;
	else												return  0;
};


// Sortierfunktion; interface fast kompatibel zu qsort [Moos]

#define MAXSIZE 24
#define d(i) (((char *)data)+(i)*size)

void insertionsort(void *data, size_t num, size_t size, int (__cdecl *compare)(const void *, const void *),bool falltoqs){
    char swapplace[MAXSIZE];

   // qsort(data,num,size,compare);
    
    if (size>MAXSIZE){
        qsort(data,num,size,compare);
        return;
    }
     
    int swaps=0;
    for (int i=1;i<(int)num;i++){
        void *lower=d(i);
        for (int j=i-1;j>=0;j--){
            void *upper=lower;
            lower=d(j);
            if ((*compare)(upper,lower) < 0){ // ok. Ist im Moment BubbleSort. Was solls...
                swaps++;
                memcpy(&swapplace,upper,size);
                memcpy(upper,lower,size);
                memcpy(lower,&swapplace,size);
            }
            else
                j=0; // hier kann man die innere Schleife schon abbrechen.
        }
        if (falltoqs && swaps > 5*i+5){
            qsort(data,num,size,compare);
            return;
        }
    }

}

zMEMPOOL_DEFINITION_TEMPLATE_BS_PA(zCTree<void>    , s_TreePool     , 4096, 4 * 4096)
zMEMPOOL_DEFINITION_TEMPLATE_BS_PA(zCList<void>    , s_ListPool     , 4096, 5 * 4096)
zMEMPOOL_DEFINITION_TEMPLATE_BS_PA(zCListSort<void>, s_ListSortPool , 4096, 5 * 4096)