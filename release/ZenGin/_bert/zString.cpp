/******************************************************************************** 
 
     $Workfile:: zstring.cpp          $                $Date:: 1.02.01 19:26     $
     $Revision:: 18                   $             $Modtime:: 1.02.01 17:56    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zstring.cpp $
 * 
 * 18    1.02.01 19:26 Speckels
 * 
 * 17    1.02.01 13:13 Moos
 * 
 * 16    29.01.01 0:39 Hildebrandt
 * removed debug ctor/dtor counters
 * 
 * 15    26.01.01 10:16 Moos
 * 
 * 14    25.01.01 12:14 Moos
 * 
 * 13    20.11.00 15:14 Keskenti
 * 
 * 12    11.09.00 20:51 Speckels
 * 
 * 11    6.09.00 18:22 Speckels
 * 
  * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 18 $ ($Modtime: 1.02.01 17:56 $)

#include "zcore.h"
#include "zString.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

//#pragma optimize( "", off )

// constants
const int CHAR_ANZ = 32;

// starting at ascii 65


const int lochar[CHAR_ANZ] = {		
	129,130,131,132,133,134,135,136,137,138,139,140,141,	
	145,147,148,149,150,151,152,155,160,161,162,163,164,
	234,199,228,231,236 };

const int upchar[CHAR_ANZ] = {
	154,144,182,142,183,143,128,210,211,212,216,215,221,	
	146,226,153,227,234,235,190,157,181,214,224,233,165,
	208,198,229,232,237 };


const unsigned char lower_characters[256] = {
	  0, 
	  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
	 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
	 61, 62, 63, 64,'a','b','c','d','e','f',
	'g','h','i','j','k','l','m','n','o','p',
	'q','r','s','t','u','v','w','x','y','z',
	 91, 92, 93, 94, 95, 96,'a','b','c','d',
	'e','f','g','h','i','j','k','l','m','n',
	'o','p','q','r','s','t','u','v','w','x',
	'y','z',123,124,125,126,127,135,129,130,
	131,132,133,134,135,136,137,138,139,140,
	141,132,134,130,145,145,147,148,149,150,
	151,152,148,129,155,156,155,158,159,160,
	161,162,163,164,164,166,167,168,169,170,
	171,172,173,174,175,176,177,178,179,180,
	160,131,133,184,185,186,187,188,189,152,
	191,192,193,194,195,196,197,199,199,200,
	
	201,202,203,204,205,206,207,234,209,136,
	137,138,213,161,140,139,217,218,219,220,
	141,222,223,162,225,147,149,228,228,230,
	231,231,163,150,151,236,236,238,239,240,
	241,242,243,244,245,246,247,248,249,250,
	251,252,253,254,255
};

const unsigned char upper_characters[256] = {
	  0, 
	  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
	 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
	 61, 62, 63, 64,'A','B','C','D','E','F',
	'G','H','I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X','Y','Z',
	 91, 92, 93, 94, 95, 96,'A','B','C','D',
	'E','F','G','H','I','J','K','L','M','N',
	'O','P','Q','R','S','T','U','V','W','X',
	'Y','Z',123,124,125,126,127,128,154,144,
	182,142,183,143,128,210,211,212,216,215,
	221,142,143,144,146,226,153,227,234,235,
	190,152,153,154,157,156,157,158,159,181,
	214,224,233,165,165,166,167,168,169,170,
	171,172,173,174,175,176,177,178,179,180,
	181,182,183,184,185,186,187,188,189,190,
	191,192,193,194,195,196,197,198,198,200,
	
	201,202,203,204,205,206,207,208,209,210,
	211,212,213,214,215,216,217,218,219,220,
	221,222,223,224,225,226,227,229,229,230,
	232,232,233,208,235,237,237,238,239,240,
	241,242,243,244,245,246,247,248,249,250,
	251,252,253,254,255
};


const unsigned char all_characters[256] = {
	  0, 
	  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
	 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
	 61, 62, 63, 64,'a','b','c','d','e','f',
	'g','h','i','j','k','l','m','n','o','p',
	'q','r','s','t','u','v','w','x','y','z',
	 91, 92, 93, 94, 95, 96,'A','B','C','D',
	'E','F','G','H','I','J','K','L','M','N',
	'O','P','Q','R','S','T','U','V','W','X',
	'Y','Z',123,124,125,126,127,128,129,130,
	131,132,133,134,135,136,137,138,139,140,
	141,142,143,144,145,146,147,148,149,150,
	151,152,153,154,155,156,157,158,159,160,
	161,162,163,164,165,166,167,168,169,170,
	171,172,173,174,175,176,177,178,179,180,
	181,182,183,184,185,186,187,188,189,190,
	191,192,193,194,195,196,197,198,199,200,
	
	201,202,203,204,205,206,207,208,209,210,
	211,212,213,214,215,216,217,218,219,220,
	221,222,223,224,225,226,227,228,229,230,
	231,232,233,234,235,236,237,238,239,240,
	241,242,243,244,245,246,247,248,249,250,
	251,252,253,254,255
};


const zSTRING zSTR_SKIP = "\r\t ";
const zSTRING zSTR_EMPTY = "";

const char zCHARBUF_SKIP[] = "\r\t ";
const char zCHARBUF_EMPTY[] = "";


//int zSTRING::construct_counter = 0;
//int zSTRING::destruct_counter = 0;

char spaceChar = ' ';


//////////////////////////////////////
// Some tools
//////////////////////////////////////



zSTRING Characters(char ch, int anzahl)
{	
	return zSTRING(anzahl,ch);
}

zSTRING Spaces(int anzahl)
{	
	return zSTRING(anzahl,' ');
}

inline char zSTRING::UpperChar(const char ch)
{
	return upper_characters[(unsigned char)(ch)];
};

inline char zSTRING::LowerChar(const char ch)
{
	return lower_characters[(unsigned char)(ch)];
};




//////////////////////////////////////
// zSTRING
//////////////////////////////////////




// conversion to a lowercase string using codepage XXX
zSTRING& zSTRING::Lower()
{
	//char ch,mustbe;
	long pos = size();
	while (pos--)	
	{	
		(*this)[pos] = lower_characters[(unsigned char)((*this)[pos])];
	}
	return *this;
}

// conversion to a uppercase string using codepage XXX
zSTRING& zSTRING::Upper()
{			
	// unsigned char ch, mustbe, was;
	long pos = size();
	while (pos--)
	{			
		(*this)[pos] = upper_characters[(unsigned char)((*this)[pos])];
	}	
	
	return *this;	
}


zSTRING& zSTRING::UpperFirstLowerRest()
{	
	if (size()<=0) return *this;
	
	Lower();
	at(0) = upper_characters[(unsigned char)at(0)];

	return *this;
};



zSTRING& zSTRING::Align(const zTSTR_ALIGN align, int room, const char c)
{
	char ch=' ';
	if (c != spaceChar) ch = c;
	if (room>size()) 
	{
		room = room-size();
		int left=0;
		int right=0;
		switch (align)
		{
			case zSTR_RIGHT:  left = room;break;
			case zSTR_LEFT:   right = room;break;
			case zSTR_CENTER: 
				left  = int(room / 2);
				right = room-left;				
				break;
		};
		if (left>0) insert((size_type)0,left,ch);
		if (right>0) append(right,ch);
	}
	return *this;
};



//////////////////////////////////////
// Tools for Parsing
//////////////////////////////////////


zSTRING zSTRING::PickWord(unsigned int num, const zSTRING& trenn, const zSTRING& skip) const
{	
	if (size()<=0) return "";
	zSTRING result;
	const char* str = PickWordPos(num,trenn,skip);
	if (!str) return result;

	//
	// Ende des gefundenen Wortes suchen
	//
	int	pos = 0;
	if (trenn.find_first_of(str[pos])!=npos) result=str[pos];
	while (str[pos]!='\0')
	{		
		if ((skip.find_first_of(str[pos])!=npos) || (trenn.find_first_of(str[pos])!=npos))
		{
			return result;
		};
		result+=str[pos];
		pos++;
	};
	return result;
}

const char* zSTRING::PickWordPos(unsigned int num, const zSTRING& trenn, const zSTRING& skip) const
{	
	const long	strsize = size();
	if (strsize>0)
	{
		char		ch;
		int			pos = 0;
		bool		inWord = false;	
		do
		{
			ch = (*this)[pos];
			if (/*!skip.IsEmpty() && */(skip.find_first_of(ch)!=string::npos))
			{
				inWord = false;
			}
			else if (/*!trenn.IsEmpty() && */(trenn.find_first_of(ch)!=string::npos))
			{			
				if ( (--num) == 0 ) return c_str()+pos;
				inWord = false;
			}
			else if (!inWord)
			{
				inWord = true;
				if ( (--num) == 0 ) return c_str()+pos;			
			};				
		} while ( (++pos) < strsize);
	};
	return NULL;
}

zSTRING zSTRING::PickWord_Old(int num, const zSTRING& trenn) const
{
	return PickWord(num, trenn, " ");
}



// insert a substring
int zSTRING::Insert(unsigned int pos, const zSTRING& xStr)
{	    
	if (pos>=size()) pos = size();
	insert(pos, xStr);
	return 0;
}

// insert a substring
zSTRING zSTRING::Inserted(unsigned int pos, const zSTRING& xStr) const
{	
	zSTRING s(this);
	s.Insert(pos,xStr);
    return s;
}

// Overwrite with a substring
int zSTRING::Overwrite(unsigned int pos, const zSTRING& xStr)
{
	if (pos>=size()) return 0;
	replace(pos,xStr.size(),xStr);
	return 0;
};	


// Overwrite with a substring
zSTRING zSTRING::Overwritten(unsigned int pos, const zSTRING& xStr) const
{
    zSTRING s(this);
	s.Overwrite(pos,xStr);
    return s;
}

int zSTRING::DeleteRight(unsigned int length)
{	
    if (length > size()) length = size();
	int startpos = size()-length;
	erase(startpos,length);
	return 0;
};


int zSTRING::Delete(unsigned int pos, unsigned long length)
{
	if (pos>=size()) return 0;	
	erase(pos,length);
	return 0;
}

// delete substring from position pos with length len
zSTRING zSTRING::Deleted(unsigned int pos, unsigned long length) const
{
    zSTRING s(this);
	s.Delete(pos,length);
	return s;
}


// delete relative to a substring
int zSTRING::Delete(const zSTRING& xStr, const zTSTR_KIND kind)
{        
	int pos = find(xStr);
    if (pos!=npos)
    {                
        switch(kind) 
		{
            case zSTR_BEFORE :	erase(0,pos);				break;
            case zSTR_TO     :	erase(0,pos+xStr.size());	break;
            case zSTR_AFTER  :	erase(pos+xStr.size());		break;
            case zSTR_FROM   :	erase(pos);					break;
            case zSTR_ONLY   :	erase(pos,xStr.size());		break;
			default			 :	erase(pos,xStr.size());		break;
        }        
    }
	return 0;
}

zSTRING zSTRING::Deleted(const zSTRING& xStr, const zTSTR_KIND kind) const
{
	zSTRING s(this);
	s.Delete(xStr,kind);
	return s;
};


int zSTRING::Copy(unsigned int pos, unsigned long length)
{		
	if (pos>=size()) 
	{
		erase();
	}
	else
	{
		assign(substr(pos,length));
	}
	return 0;
}

// Copied substring from position pos with length len
zSTRING zSTRING::Copied(unsigned int pos, unsigned long length) const
{
    zSTRING s(this);
	s.Copy(pos,length);
    return s;
}

// Copied relative to a substring
int zSTRING::Copy(const zSTRING& xStr,  const zTSTR_KIND& kind)
{
	int pos = find(xStr);
    if (pos!=npos)
    {                
        switch(kind) 
		{
            case zSTR_BEFORE :	assign(substr(0,pos));				break;
            case zSTR_TO     :	assign(substr(0,pos+xStr.size()));	break;
            case zSTR_AFTER  :	assign(substr(pos+xStr.size()));	break;
            case zSTR_FROM   :	assign(substr(pos));				break;
            case zSTR_ONLY	 :	assign(substr(pos, xStr.size()));	break;
			default			 :	assign(substr(pos, xStr.size()));	break;
        }        
    }
	else erase();
    return 0;
}

// Copied relative to a substring
zSTRING zSTRING::Copied(const zSTRING& xStr, const zTSTR_KIND& kind) const
{
        zSTRING s(this);
		s.Copy(xStr,kind);
		return s;
}

void zSTRING::TrimLeft(char ch)
{
	int pos = 0;
	while (pos<size() && ((*this)[pos]==ch)) pos++;
	if (pos>0) Delete(0,pos);	
};

void zSTRING::TrimRight(char ch)
{
	int pos = size()-1;
	while (pos>=0 && ((*this)[pos]==ch)) pos--;
	if (pos < (size()-1)) Delete(pos+1);	
};


int	zSTRING::Search(int startIndex, const char* substr,	unsigned int num) const
{
	if (!substr) return -1;	
	int index	= startIndex;
	int pos		= -1;
	for (int i=0;i<num;i++)
	{
		pos = find(substr, index);
		if (pos==string::npos) return -1;
		index = pos+1;
	}
	return pos;	
};

int zSTRING::SearchRev(const zSTRING& substr, unsigned int num) const
{		
	int pos = 0;

	//
	// simple case:
	//
	if (num == 1) 
	{
		pos = rfind(substr);
		if (pos==npos) return -1;
	}
	//
	// more complex case:		
	//
	else
	{		
		zSTRING text(this);
		for (unsigned int i=1;i<=num;i++)
		{
		   pos = text.rfind(substr);
		   if (pos==npos)	return -1;
		   if (i==num)		return pos;
		   text.erase(pos);		   
		}
		return -1;
	}	

	return pos;
}


bool zSTRING::Sprintf( const char* format, ... )
{
	if( format == NULL ) {
		return true;
	}

	va_list args;
	va_start( args, format );

	::vsprintf( this->ToChar(), format, args );

	va_end( args );

	return true;
}

#ifndef COMPILING_SPACER
zMEMPOOL_DEFINITION_BS_PA(zSTRING, 4096, 7*4096);
#endif
