/******************************************************************************** 
 
     $Workfile:: zPluecker.cpp    $                $Date:: 21.09.00 20:57   $
     $Revision:: 2                $             $Modtime:: 21.09.00 20:33   $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Pluecker coordinates
   created: 25.5.2000

 * $Log: /current_work/ZenGin/_Dieter/zPluecker.cpp $
 * 
 * 2     21.09.00 20:57 Moos
 * 
 * 1     21.09.00 18:51 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 21.09.00 20:33 $)

#include "zPluecker.h"

zCPluecker::zCPluecker(const zVEC3 &a, const zVEC3 &d){
  dir[0]=d[0];
  dir[1]=d[1];
  dir[2]=d[2];
  pos[0]=a[1]*d[2] - a[2]*d[1];
  pos[1]=a[2]*d[0] - a[0]*d[2];
  pos[2]=a[0]*d[1] - a[1]*d[0];
}

zCPluecker::zCPluecker(){
  for (int i=5;i>=0;i--)
    dir[i] = 0;
}


float zCPluecker::Length2() const{
    int i;
    float len = 0;
    for (i=2;i>=0;i--)
      len += dir[i]*dir[i] + pos[i]*pos[i];

    return len;
  }


void zCPluecker::Normalize(){
    int i;
    float len = 0;
    for (i=2;i>=0;i--)
      len += dir[i]*dir[i] + pos[i]*pos[i];

    if (len == 0){
        dir[0]=1;
        return;
    }

    len = float(1/sqrt(len));

    for (i=2;i>=0;i--){
      dir[i]*=len;
      pos[i]*=len;
    }
  }

