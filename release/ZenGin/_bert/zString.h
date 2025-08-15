/******************************************************************************** 
 
     $Workfile:: zString.h           $                 $Date:: 29.01.01 0:39    $
     $Revision:: 14                  $              $Modtime:: 29.01.01 0:19    $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH

   Description::
   Basic string-class implementing full featured operations on string especially
   for parsing large text-strings

 * $Log: /current_work/zengin_work/_Bert/zString.h $
 * 
 * 14    29.01.01 0:39 Hildebrandt
 * removed debug ctor/dtor counters
 * 
 * 13    25.01.01 19:10 Moos
 * 
 * 12    25.01.01 12:14 Moos
 * 
 * 11    4.12.00 18:22 Moos
 * 
 * 10    20.11.00 15:14 Keskenti
 * 
 * 9     11.09.00 20:51 Speckels
 * 
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 14 $ ($Modtime: 29.01.01 0:19 $)

#pragma warning( disable : 4530 ) 

#ifndef __ZSTRING_H__
#define __ZSTRING_H__

#ifndef _STRING_
#include <string>
#endif

#ifndef _INC_IOSTREAM
#include <iostream>
#endif

#ifndef __ZMEMPOOL_H__
#include <zMemPool.h>
#endif


#include "assert.h"

#pragma pack(push,8)

// definitions
enum zTSTR_KIND		{ zSTR_ONLY, zSTR_BEFORE, zSTR_AFTER, zSTR_TO, zSTR_FROM};
enum zTSTR_ALIGN	{ zSTR_RIGHT, zSTR_CENTER, zSTR_LEFT };

// the class
class zSTRING;

using std::string;

extern const zSTRING zSTR_SKIP;
extern const zSTRING zSTR_EMPTY;

extern const char zCHARBUF_SKIP[];
extern const char zCHARBUF_EMPTY[];

extern char  spaceChar;

const unsigned long zSTR_MAXSIZE = std::string::npos;

class zSTRING : public std::string
{
#ifndef COMPILING_SPACER	
    zMEMPOOL_DECLARATION( zSTRING )
#endif

public:

//	static int destruct_counter;
//	static int construct_counter;

	static inline char UpperChar(const char ch);
	static inline char LowerChar(const char ch);
	
	zSTRING()						: string()			{ Init(); };
	zSTRING(int n, char c)			: string(n,c)		{ Init(); };
	zSTRING(const zSTRING& xStr)	: string(xStr)		{ Init(); };
	zSTRING(const zSTRING* pStr)	: string(*pStr)		{ Init(); assert(pStr); };
	zSTRING(const char* pstring)	: string(pstring)	{ Init(); assert(pstring); };
	zSTRING(char ch)				: string(1,ch)		{ Init(); };

	// constructor (int)
	zSTRING(const int xWert)
	{		
		Init();
		char buffer[50];itoa(xWert,buffer,10);assign(buffer);
	}

	// constructor (long)
	zSTRING(const long xWert)
	{	
		Init();
		char buffer[50];ltoa(xWert,buffer,10);assign(buffer);				
	}

	// constructor (long)// constructor (long)	
	zSTRING(const unsigned long xWert)
	{	
		Init();
		char buffer[50];ultoa(xWert,buffer,10);assign(buffer);				
	}

	// constructor (float)
	zSTRING(const float xWert,int digits=20)
	{
		Init();
		if (digits>9 || digits<0) digits=9;	
	
		char format[5] = "%.9g";
		format[2] = char(digits+48);
		
		char buffer[100];	
		sprintf(buffer, format, xWert );
		assign(buffer);		
	}

	// constructor (float)
	zSTRING(const double xWert,int digits=20)
	{	
		Init();
		if (digits>9 || digits<0) digits=9;
	
		char format[5] = "%.9g";
		format[2] = char(digits+48);

		char buffer[100];	
		sprintf(buffer, format, xWert );
		assign(buffer);		
	}
	
	// destructor
	virtual ~zSTRING()									{ };	// FIXME: is this dtor still needed? (base class has virtual dtor??)
//	virtual ~zSTRING()									{ destruct_counter++; };
	
	//** assignments
	zSTRING& operator= (const zSTRING& pStr)	{ assign(pStr);return *this; };
	zSTRING& operator= (const char* pstring)	{ assert(pstring);assign(pstring);return *this; };
	zSTRING& operator+=(const zSTRING& xStr)	{ append(xStr);return *this; }
	zSTRING& operator+=(const char* pstring)	{ assert(pstring);append(pstring);return *this; }

	/// align current string RIGHT, LEFT or CENTERed in string with 'room'-count character 'c'. will return resulting string AND change itself	
	zSTRING&	Align(const zTSTR_ALIGN align, int room, const char c = spaceChar);
	char		GetLastChar() { if (size()==0) return ' ' ; else return at(size()-1); };

	void		Reset()			{ erase(); };
	void		Clear()			{ erase(); };
	bool		IsEmpty() const	{ return empty(); };
		
	//*** query, conversion
	int			Length()   const  { return size(); }
	char*		ToChar()   const  { return (char*)c_str(); }
	long int	ToInt()    const  { return atol(c_str()); }
	float		ToFloat()  const  { return (float)atof(c_str()); }
	double		ToDouble() const  { return (double)atof(c_str()); }

	bool		Sprintf( const char* format, ... );

	//*** comparison
	
	friend int operator< (const zSTRING& xStr1, const zSTRING& xStr2) { return xStr1.compare(xStr2)<0; }
	friend int operator<=(const zSTRING& xStr1, const zSTRING& xStr2) { return xStr1.compare(xStr2)<=0; }
	friend int operator> (const zSTRING& xStr1, const zSTRING& xStr2) { return xStr1.compare(xStr2)>0; }
	friend int operator>=(const zSTRING& xStr1, const zSTRING& xStr2) { return xStr1.compare(xStr2)>=0; }
	
	friend int operator!=(const zSTRING& xStr1, const zSTRING& xStr2) { return xStr1.compare(xStr2)!=0; }
	friend int operator==(const zSTRING& xStr1, const zSTRING& xStr2) { return xStr1.compare(xStr2)==0; }
	
	friend int operator!=(const zSTRING& xStr1, const char* const xStr2) { return xStr1.compare(xStr2)!=0; }
	friend int operator==(const zSTRING& xStr1, const char* const xStr2) { return xStr1.compare(xStr2)==0; }

	friend int operator!=(const char* xStr1, const zSTRING& xStr2) { return xStr2.compare(xStr1)!=0; }
	friend int operator==(const char* xStr1, const zSTRING& xStr2) { return xStr2.compare(xStr1)==0; }

	int CompareTo (const zSTRING& xStr2)	const { return compare(xStr2); }
	int CompareTo (const char* cstr)		const { return compare(cstr); }

	//*** Concatenation
	
	inline friend zSTRING operator+ (const zSTRING& xStr1,	const zSTRING& xStr2);
	inline friend zSTRING operator+ (const zSTRING& xStr1,	const char* pstring);
	inline friend zSTRING operator+ (const zSTRING& xStr2,	const char ch);
	inline friend zSTRING operator+ (const char* pstring,	const zSTRING& xStr2);
	inline friend zSTRING operator+ (const char ch,			const zSTRING& xStr2);
	
	//** index-operators	
	
	      char& operator[](unsigned int index)			{ return ( index>=size() ) ? spaceChar : at(index); };
	const char& operator[](unsigned int index) const	{ return at(index); };
	
	//*** output

	friend ostream& operator<<(ostream& stream, const zSTRING& xStr) { return ( stream << xStr.ToChar()  ); }
	friend ostream& operator<<(ostream& stream, const zSTRING* xStr) { return ( stream << xStr->ToChar() ); }

	//*** tools

	zSTRING& Upper();
	zSTRING& Lower();
	zSTRING& UpperFirstLowerRest();

	//*** complex tools for parsing

	zSTRING		PickWord	(unsigned int num, const zSTRING& trenn, const zSTRING& skip=zSTR_SKIP) const;			
	const char*	PickWordPos	(unsigned int num, const zSTRING& trenn, const zSTRING& skip=zSTR_SKIP) const;
	zSTRING		PickWord_Old(int num, const zSTRING& trenn) const;

	int			Insert		(unsigned int pos, const zSTRING& xStr);	
	zSTRING		Inserted	(unsigned int pos, const zSTRING& xStr) const;

	int			Overwrite	(unsigned int pos, const zSTRING& xStr);
	zSTRING		Overwritten	(unsigned int pos, const zSTRING& xStr) const;

	int			Copy		(unsigned int pos, unsigned long length=zSTR_MAXSIZE);	
	zSTRING		Copied		(unsigned int pos, unsigned long length=zSTR_MAXSIZE) const;
	int			Copy		(const zSTRING& xStr,  const zTSTR_KIND& kind = zSTR_ONLY);
	zSTRING		Copied		(const zSTRING& xStr,  const zTSTR_KIND& kind = zSTR_ONLY) const;

	int			Delete		(unsigned int pos, unsigned long length=zSTR_MAXSIZE);	
	zSTRING		Deleted		(unsigned int pos, unsigned long length=zSTR_MAXSIZE) const;
	int			Delete		(const zSTRING& xStr, const zTSTR_KIND kind = zSTR_ONLY);
	zSTRING		Deleted		(const zSTRING& xStr, zTSTR_KIND kind = zSTR_ONLY) const;

	int			DeleteRight	(unsigned int length);
	
	void		TrimLeft	(char ch = ' ');
	void		TrimRight	(char ch = ' ');
	
	int			Search		(int startIndex, const char* substr,	unsigned int num=1) const;	
	inline int	Search		(int startIndex, const zSTRING& substr, unsigned int num=1) const;
	inline int	Search		(const zSTRING& substr, unsigned int num=1) const;	
	inline int	Search		(const char* substr,	unsigned int num=1) const;		

	int			SearchRev	(const zSTRING& substr, unsigned int num=1) const;

protected:

	// Constructor for concatenation	
	zSTRING		(const zSTRING& xStr1, const char* pstring)		: string(xStr1) { assert(pstring);append(pstring); };
	zSTRING		(const zSTRING& xStr1, const zSTRING& xStr2)	: string(xStr1) { append(xStr2); };
	zSTRING		(const zSTRING& xStr1, const char ch)			: string(xStr1) { append(1,ch); };	

	inline void Init	() { };
//	inline void Init	() { construct_counter++; };
};

#pragma pack(pop)

// Tools

zSTRING Characters(char ch, int anzahl);
zSTRING Spaces(int anzahl);


//
// inline
//


int	zSTRING::Search(const char* substr,	unsigned int num) const
{
	return Search(0,substr,num);
};

int	zSTRING::Search	(int startIndex, const zSTRING& substr, unsigned int num) const
{
	return Search(startIndex,substr.ToChar(),num);
};

int zSTRING::Search(const zSTRING& substr, unsigned int num) const
{	
	return Search(0,substr.ToChar(),num);	
}


// Concatenation
//
// The following methods are using special protected concatenation-constructors
//
zSTRING operator+ (const zSTRING& xStr1, const zSTRING& xStr2)
{	
	return zSTRING(xStr1,xStr2);
}

zSTRING operator+ (const char* str, const zSTRING& xStr2)
{	
	return zSTRING( zSTRING(str),xStr2);
};

zSTRING operator+ (const char ch, const zSTRING& xStr2)
{	
	return zSTRING( zSTRING(ch),xStr2);
};

zSTRING operator+ (const zSTRING& xStr1, const char* str)
{	
	return zSTRING(xStr1,str);
};

zSTRING operator+ (const zSTRING& xStr1, const char ch)
{	
	return zSTRING(xStr1,ch);
};



#endif

