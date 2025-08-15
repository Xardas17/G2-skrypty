/******************************************************************************** 
 
     $Workfile:: zFile3d.h            $                $Date:: 31.01.01 5:14    $
     $Revision:: 9                    $             $Modtime:: 31.01.01 5:14    $
        Author:: Hildebrandt                                                       
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ 3d-File Formats Library
   created       : 20.2.97

 * $Log: /current_work/zengin_work/_Dieter/zFile3d.h $
 * 
 * 9     31.01.01 5:14 Hildebrandt
 * 
 * 8     4.12.00 17:42 Hildebrandt
 * 
 * 7     11.09.00 19:40 Speckels
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 5     4.05.00 20:17 Hildebrandt
 * zenGin 089e
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 5     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 9 $ ($Modtime: 31.01.01 5:14 $)


#ifndef __ZFILE3D_H__
#define __ZFILE3D_H__

#ifndef __ZOBJECT_H__
#include "zobject.h"
#endif

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __Z3D_H__
#include <z3d.h>
#endif

#ifndef __ZDISK_H__
#include <zDisk.h>
#endif

// =============================================================================================

// 3D-Studio
class zENGINE_API zCFile3DS {
public:
	void Load3DS (const zSTRING& fileName, zCMesh *);
	void Save3DS (const zSTRING& fileName, zCMesh *sMesh);
};

// =============================================================================================

// Quake-BSP
class zENGINE_API zCFileQuakeBSP {
private:
	zFILE *file;
public:
	zCFileQuakeBSP();
	~zCFileQuakeBSP();
	void LoadQuakeBSP (const zSTRING& fileName, zCMesh *,  zCWorld* );
};

// =============================================================================================

// internal binary-format

/*
	zFCHUNK_TEXTURE			= 0x1000;
	zFCHUNK_MODELANI		= 0xA000;
	zFCHUNK_MODELMESH		= 0xD000;
	zFCHUNK_MODELHIERARCHY	= 0xD100;
	zFCHUNK_MESH			= 0xB000;
	zFCHUNK_PROGMESH		= 0xB100;
	zFCHUNK_BSP				= 0xC000;
	zFCHUNK_MORPHMESH		= 0xE000;
	zFCHUNK_MESHSOFTSKIN	= 0xE100;
*/

class zCFileBIN {
protected:
	int		lastStart;
	int		nextStart;
	zBOOL	externalFile;
public:
	zFILE	*file;

	zCFileBIN ()						{ file = 0;					lastStart = nextStart = -1; externalFile=FALSE; };
//	zCFileBIN (const zSTRING& fname)	{ file = new zFILE(fname);	lastStart = nextStart = -1; externalFile=FALSE; };
	zCFileBIN (const zSTRING& fname)	{ file = zfactory->CreateZFile(fname);	lastStart = nextStart = -1; externalFile=FALSE; };
	~zCFileBIN()						{ if (file) BinClose(); };
	zBOOL	BinEof		()				{ assert(file); return (nextStart>=file->Size()); }			// ??
	zBOOL	BinExists	()				{ assert(file); return file->Exists(); };
	void	BinOpen		(const zSTRING& name="") {
		if (!file) file = zfactory->CreateZFile (name);
		file->Open();
		lastStart	= nextStart = -1;
	};
	void	BinSetFile		(zFILE* inFile)	{ file=inFile; lastStart = nextStart = -1; externalFile=TRUE; };
	void	BinRead			(void* ptr, const int num) { assert (file); file->Read (ptr, num); };
	void	BinReadFloat	(float   &f)	{ assert (file); file->Read (&f, sizeof(f)); };
	void	BinReadInt		(int     &f)	{ assert (file); file->Read (&f, sizeof(f)); };
	void	BinReadDWord	(zDWORD  &f)	{ assert (file); file->Read (&f, sizeof(f)); };
	void	BinReadWord		(zWORD   &f)	{ assert (file); file->Read (&f, sizeof(f)); };
	void	BinReadByte		(zBYTE   &f)	{ assert (file); file->Read (&f, sizeof(f)); };
	void	BinReadString	(zSTRING &f)	{ 
		assert (file); 
		file->Read (f); 
	};
	void BinOpenChunk (zWORD& id, zLONG& len) {
		if (file==0) return;
		file->Read (&id , sizeof(id));
		if (file->Eof()) { id = 0; return; };
		file->Read (&len, sizeof(len));
		int actPos = file->Pos();
		nextStart  = actPos + len;
	};
	void BinSkipChunk () {
		if (file==0) return;
		if (nextStart>=file->Size()) return;
		file->Seek (nextStart);
	};
	zBOOL BinSeekChunk (const zWORD id) {
		if (file==0) return FALSE;
		zWORD fid;
		zLONG flen;
		BinOpenChunk (fid, flen);
		while ( (!file->Eof()) && (fid!=id)) {
			BinSkipChunk ();
			BinOpenChunk (fid, flen);
		};
		return ((fid==id) && (!file->Eof()));
	};

	// write
	void BinCreate	(const zSTRING& name) {
		file		= zfactory->CreateZFile(name);
		file->Create();
		lastStart	= -1;
	};
	void BinStartChunk	(const zWORD id) {
		if (file==0) return;
		// close last chunk: write len
		if (lastStart!=-1) {
			int actPos = file->Pos();
			int len    = actPos-lastStart-6; //6
			file->Seek  (lastStart+sizeof(id));
			file->Write (&len, sizeof(len));
			file->Seek  (actPos);
		};
		// write header-frame for new chunk
		zLONG len = 0;
		lastStart = file->Pos();
		file->Write (&id , sizeof(id));
		file->Write (&len, sizeof(len));
	};
	void BinEndChunk	() {
		// close last chunk: write len
		// 'lastStart' ist nur im WriteMode !=-1 !
		if (lastStart!=-1) {
			int actPos = file->Pos();
			int len    = actPos-lastStart-6; //6
			file->Seek  (lastStart+sizeof(zWORD));
			file->Write (&len    , sizeof(len));
			file->Seek  (actPos);
		};
	};
	void BinWrite		(const void* ptr, const int num) { assert (file); file->Write (ptr, num); };
	void BinWriteFloat  (const float  f)	{ assert (file); file->Write (&f, sizeof(f)); };
	void BinWriteInt    (const int    f)	{ assert (file); file->Write (&f, sizeof(f)); };
	void BinWriteDWord  (const zDWORD f)	{ assert (file); file->Write (&f, sizeof(f)); };
	void BinWriteWord   (const zWORD  f)	{ assert (file); file->Write (&f, sizeof(f)); };
	void BinWriteByte	(const zBYTE  f)	{ assert (file); file->Write (&f, sizeof(f)); };
	void BinWriteString (const zSTRING& s)	{ assert (file); file->Write (s+"\n"); };
	void BinClose () {
		// close last chunk: write len
		BinEndChunk();
		if (!externalFile) {
			file->Close();
			delete file;
		};
		file =0;
	};

	zBOOL BinWriteSrcFileStats (zSTRING& fileName) {
		zPATH ascPath;
		if (!fileName.IsEmpty())
		if (ascPath.SearchFile(fileName, zSTRING(zFILE::GetCurrentDir()))!=zERR_NONE) {
//			zerr.Warning ("D: MDL: zFile3D(zCFileBin::BinWriteSourceFileStats): File not found: "+fileName);
		};
		// File gefunden
		zFILE_STATS stats;
		{
			// [BENDLIN] 2002-06-26, zero memory (garbage in bin files because of alignment)
			memset(&stats, 0, sizeof(stats));
			zFILE* ascFile = zfactory->CreateZFile(ascPath.GetPath());
			ascFile->GetStats	(stats); 
			delete ascFile;
		}

		BinWrite		(&(stats.modifyDate), sizeof(stats.modifyDate));
		BinWriteString	(fileName);
		return TRUE;
	};

	zBOOL BinReadCompareSrcFileStats () {
		zDATE	date;
		zSTRING	fileName;
		zPATH	ascPath;

		BinRead		(&(date), sizeof(date));
		BinReadString	(fileName);

		if (fileName.IsEmpty())	return TRUE;

		if (ascPath.SearchFile(fileName, zSTRING(zFILE::GetCurrentDir()))!=zERR_NONE) {
//			zERR_WARNING("D: MDL: zFile3D(zCFileBin::BinReadCompareSrcFileStats): File not found: "+fileName);
			return TRUE;
		} else {
			// File gefunden
			zFILE_STATS ascStats;
			{
				zFILE* ascFile = zfactory->CreateZFile(ascPath.GetPath());
				ascFile->GetStats	(ascStats);
				delete ascFile;
			}

			if (ascStats.modifyDate>date) return FALSE;
		};
		return TRUE;
	};
};

// =============================================================================================


#endif