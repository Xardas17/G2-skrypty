#ifndef _VDFS32E_H
#define _VDFS32E_H

#ifdef __cplusplus
extern "C" {
#endif

#define VDF_VIRTUAL         1
#define VDF_PHYSICAL        2
#define VDF_PHYSICALFIRST   4
#define VDF_PACKED          8
#define VDF_NOBUFFER       16

#define VDF_OPTID_MAXFILES  0
#define VDF_OPTID_MAXBUFFER 1

typedef struct
{
  char  name[64];
  long  size;
  long  attr;
  long  datetime;
} TVDFFINDDATA;

__declspec (dllimport) long vdf_fopen(char* filename, long flags);
__declspec (dllimport) long vdf_fclose(long filehandle);
__declspec (dllimport) long vdf_fread(long filehandle, char* buffer, long size);
__declspec (dllimport) long vdf_fseek(long filehandle, long pos);
__declspec (dllimport) long vdf_fseekrel(long filehandle, long pos);
__declspec (dllimport) long vdf_ftell(long filehandle);
__declspec (dllimport) long vdf_fexists(char* filename, long flags);
__declspec (dllimport) long vdf_fdirexists(char* pathname, long flags);
__declspec (dllimport) long vdf_changedir(char* pathname);
__declspec (dllimport) long vdf_getdir(char* buffer);
__declspec (dllimport) long vdf_findopen(char* path, long flags);
__declspec (dllimport) long vdf_findnext(long findhandle, TVDFFINDDATA* finddata );
__declspec (dllimport) long vdf_findclose(long findhandle);
__declspec (dllimport) long vdf_searchfile(char *filename, char *findresult);
__declspec (dllimport) long vdf_getlasterror(char *errtext);
__declspec (dllimport) long vdf_ffilesize(long filehandle);
__declspec (dllimport) long vdf_setoption(long optid, long value);
__declspec (dllimport) long vdf_getoption(long optid);
__declspec (dllimport) long vdf_initall(long numdisks, char* cdid, long* cddrives, long* disksfound);
__declspec (dllimport) long vdf_exitall();

#ifdef __cplusplus
};
#endif
#endif
