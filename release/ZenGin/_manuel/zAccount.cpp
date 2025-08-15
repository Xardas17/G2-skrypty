/******************************************************************************** 
 
     $Workfile:: zAccount.cpp     $                $Date:: 9.02.01 13:24    $
     $Revision:: 12               $             $Modtime:: 9.02.01 10:38    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   RefCtr Accounting
   created: 5.2.2000

 * $Log: /current_work/ZenGin/_Manuel/zAccount.cpp $
 * 
 * 12    9.02.01 13:24 Moos
 * 
 * 11    8.02.01 14:53 Moos
 * 
 * 10    8.02.01 10:52 Moos
 * 
 * 9     8.02.01 10:46 Moos
 * 
 * 8     7.02.01 14:36 Moos
 * 
 * 7     7.02.01 12:53 Moos
 * 
 * 6     6.02.01 17:56 Moos
 * 
 * 5     6.02.01 12:40 Moos
 * 
 * 4     5.02.01 18:01 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 9.02.01 10:38 $)


#include "zCore.h"
#include "zSparseArray.h"
#include "zoption.h"
#include "zAccount.h"

#pragma warning ( disable:4073)
#pragma init_seg(lib)

static zBOOL s_inited          = FALSE;
static zBOOL s_account         = TRUE;
static zBOOL s_accountFull     = TRUE;
int   zCAccount::s_actCounter  = 0;

void zAccountInit(){
  if (zoptions){
      s_inited      = TRUE;
      s_account     = zoptions->Parm("ZACCOUNT");
      s_accountFull = zoptions->Parm("ZACCOUNTFULL");
      s_account    |= s_accountFull;
  }
}

int Hash(const zSTRING &s){
      int ret=0;
      int fak=1;
      for (int i = s.Length()-1; i>=0; i--)
    {
      ret += fak*s[i];
      fak *= 29;
    }

  return ret;
}


char *aliases[][2]={
  { "zWorld.cpp"        , "zVob.cpp"        },
  { "oGame.cpp"         , "oobjfactory.cpp" },
  { "oGameExternal.cpp" , "oobjfactory.cpp" },
  { ""                  , ""                }
};


class zTIndexA{
public:
  zSTRING file;
  
  zTIndexA(const char *f){

      int i=0;
      while(strlen(aliases[i][0])){
        if (!strcmp(f, aliases[i][0]))
	      f = aliases[i][1];

        i++;
      }

      file = f;
  }

  int operator == (const zTIndexA &b) const { return (file == b.file); }
};

class zTIndexB{
public:
  zSTRING file;
  int     line;
  
  zTIndexB(const zSTRING &f, int l):file(f), line(l){}

  int operator == (const zTIndexB &b) const { return file == b.file && line == b.line; }
};



inline void Hash<zTIndexA>(const zTIndexA *index, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb){
    int h = Hash(index->file);
    Hash(&h, p, hasha, hashb);
};

inline void Hash<zTIndexB>(const zTIndexB *index, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb){
    int h = Hash(index->file) + 137 * index->line;
    Hash(&h, p, hasha, hashb);
};


class zCAccountInfo{
  zCSparseArray<zTIndexA, int> fileCount;
  zCSparseArray<zTIndexB, int> locationCount;
  int                          sum;
public:
  zCAccountInfo(): fileCount (7), locationCount(13), sum(0){};
  

  void Add(const char *filename, int line, int num){
    zTIndexA a(filename);
    zTIndexB b(filename, line);

    if (    !fileCount[a])     *fileCount.Insert(a) = 0;
    if (!locationCount[b]) *locationCount.Insert(b) = 0;

    *fileCount[a]     += num;
    *locationCount[b] += num;
    sum               += num;
  }

  void SumUp(){
    for (zCSparseArrayIterator j(fileCount); j; j.Next())
        if (s_accountFull || *fileCount[j] != 0 )
        {
            zTIndexA &f = *fileCount.IteratorIndex(j);

            for (zCSparseArrayIterator i(locationCount); i; i.Next())
            {
                zTIndexB &b = *locationCount.IteratorIndex(i);
                
                if (b.file == f.file)
                {
                    zERR_MESSAGE(2, 0, "M: file: " + b.file + ", line: " + zSTRING(b.line) + 
		                                   ", count: " + zSTRING(*locationCount[i]) + ".");
                }
      
            }
        }

  }
};



static zCSparseArray<const void *, zCAccountInfo> s_accounts;



void zCAccount::Add(const void *object, const char *filename, int line, int num){
  const char *fn_run = filename;

  if (s_actCounter > 100 || !s_account) goto end;
  if (!s_inited)  zAccountInit();
  if (!s_inited)  goto end;

  while (*fn_run){
    if (*fn_run == '\\')
        filename = fn_run+1;
    fn_run++;
  }

  s_accounts.Insert(object)->Add(filename, line, num);

end:
  End();
}

void zCAccount::Sum(const void *object){
  if (!s_account) return;
  if (!s_inited) zAccountInit();

  s_accounts.Insert(object)->SumUp();
}

void zCAccount::Clear(const void *object){
  if (!s_account) return;
  if (!s_inited)  return;

  s_accounts.Delete(object);
}


void  zCAccount::Begin(){
    s_actCounter++;
}

void  zCAccount::End(){
    s_actCounter--;
}


zBOOL zCAccount::IsActive(){
    return (0 != s_actCounter);
}

// für das RefCtr-Accounting
void zCClassDef::ObjectCreated (zCObject *object, zCClassDef *objClassDef, const char *file, int line){
    zCAccount::Clear(object);
    zCAccount::Begin();
    ObjectCreated(object, objClassDef);
    zCAccount::Add(object, file, line, 1);
}
