/******************************************************************************** 
 
     $Workfile:: zPluecker.h      $                $Date:: 8.01.01 20:43    $
     $Revision:: 2                $             $Modtime:: 8.01.01 20:43    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Pluecker coordinates
   created: 25.5.2000

 * $Log: /current_work/zengin_work/_Dieter/zPluecker.h $
 * 
 * 2     8.01.01 20:43 Hildebrandt
 * 
 * 1     21.09.00 18:51 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 8.01.01 20:43 $)


#ifndef __ZPLUECKER_H__
#define __ZPLUECKER_H__


#ifndef __ZALGEBRA_H__
#include "zAlgebra.h"
#endif
 
class zCPluecker {
public:
  float dir[3];  //direction of the ray
  float pos[3];  //cross product of a point on the ray and the direction
  
  zCPluecker(const zVEC3 &a, const zVEC3 &d); // calculate the zCPluecker coordinates of the line through a in direction d
  zCPluecker();

  // normal vector math
  inline zCPluecker & operator += (const zCPluecker &b);
  inline zCPluecker & operator -= (const zCPluecker &b);
  inline zCPluecker & operator *= (float b);
  inline zCPluecker   operator-   (const zCPluecker &b) const;
  inline zCPluecker   operator-   ()                    const;
  inline zCPluecker   operator+   (const zCPluecker &b) const;
  inline zCPluecker   operator*   (float b)             const;

         float Length2() const;  // squared length
  inline float Length()  const;  // length
  void         Normalize();      // make unit length
};


// Pluecker scalar product; singn tells whether a passes "left" or "right" of b.
inline float operator *(const zCPluecker &a, const zCPluecker &b){
  float ret=0;
  for (int i=2;i>=0;i--)
    ret += a.dir[i] * b.pos[i] + b.dir[i] * a.pos[i];
  return ret;
}















// ***************************************
//           Implementation
// ***************************************


inline zCPluecker & zCPluecker::operator += (const zCPluecker &b){
    for(int i=5;i>=0;i--)
        dir[i]+=b.dir[i];

    return *this;
}

inline zCPluecker & zCPluecker::operator -= (const zCPluecker &b){
    for(int i=5;i>=0;i--)
        dir[i]-=b.dir[i];

    return *this;
}

inline zCPluecker & zCPluecker::operator *= (float b){
    for(int i=5;i>=0;i--)
        dir[i]*=b;

    return *this;
}

inline zCPluecker zCPluecker::operator-(const zCPluecker &b) const{
    return zCPluecker(*this)-=b;
}

inline zCPluecker zCPluecker::operator-() const{
    return zCPluecker()-*this;
}

inline zCPluecker zCPluecker::operator+(const zCPluecker &b) const{
    return zCPluecker(*this)+=b;
}

inline zCPluecker zCPluecker::operator*(float b) const{
    return zCPluecker(*this)*=b;
}

inline float zCPluecker::Length() const{
    return float(sqrt(Length2()));
}

#endif