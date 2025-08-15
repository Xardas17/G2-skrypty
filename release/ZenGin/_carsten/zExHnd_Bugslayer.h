/*----------------------------------------------------------------------
       John Robbins - Microsoft Systems Journal Bugslayer Column
------------------------------------------------------------------------

The BugslayerUtil.DLL file contains various routines that are useful
across various projects, not just those for a single column.  I will
be adding to the DLL in future columns.

HISTORY     :

FEB '98 - Initial version.  This also incorporated the October '97
          memory dumper and validator library.

APR '98 - Added the CSymbolEngine class in SymbolEngine.h

AUG '98 - Added the Crash Handler functions to assist in crash
          information.
        - Set all exported functions to __stdcall.

OCT '98 - Fixed HookImportedFunctionsByName to no patch addresses
          about 2GB on Win95.  Also changed the function so that
          the user can pass NULL for the returned orignal function
          array and NULL for the number of functions hooked.
        - Added the IsNT function to the export list.

FEB '99 - Updated the CrashHandler code to work on Win9x.
        - Updated CSymbolEngine to support getting the versions of
          IMAGEHLP.DLL as well as the PDB reader DLL, MSDBI.DLL or
          MSPDB50.DLL.
        - Moved to VC6.
        - Fixed bug reported by Frank McGrath in
          HookImportedFunctionsByName.
        - Added the ASSERT and SUPERASSERT cool macros all in
          DiagAssert.h/.cpp.
        - Removed the old ASSERT/TRACE stuff in MSJDBG.H.

----------------------------------------------------------------------*/

#ifndef __ZEXHND_BUGSLAYER_H__
#define __ZEXHND_BUGSLAYER_H__

/*//////////////////////////////////////////////////////////////////////
                                Includes
//////////////////////////////////////////////////////////////////////*/
// If windows.h has not yet been included, include it now.
#ifndef _INC_WINDOWS
#include <windows.h>
#endif

/*++ BUILD Version: 0001     Increment this if a change has global effects

Copyright (c) 1990-1999  Microsoft Corporation

Module Name:

    imagehlp.h

Abstract:

    This module defines the prototypes and constants required for the image
    help routines.

Revision History:

--*/

#ifndef _IMAGEHLP_
#define _IMAGEHLP_

#if _MSC_VER > 1020
#pragma once
#endif


#ifdef _WIN64
#ifndef _IMAGEHLP64
#define _IMAGEHLP64
#endif
#endif


#ifndef WINTRUST_H
#include <wintrust.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _IMAGEHLP_SOURCE_
#define IMAGEAPI __stdcall
#else
#define IMAGEAPI DECLSPEC_IMPORT __stdcall
#endif

#define IMAGE_SEPARATION (64*1024)

typedef struct _LOADED_IMAGE {
    PSTR                  ModuleName;
    HANDLE                hFile;
    PUCHAR                MappedAddress;
#ifdef _IMAGEHLP64
    PIMAGE_NT_HEADERS64   FileHeader;
#else
    PIMAGE_NT_HEADERS32   FileHeader;
#endif
    PIMAGE_SECTION_HEADER LastRvaSection;
    ULONG                 NumberOfSections;
    PIMAGE_SECTION_HEADER Sections;
    ULONG                 Characteristics;
    BOOLEAN               fSystemImage;
    BOOLEAN               fDOSImage;
    LIST_ENTRY            Links;
    ULONG                 SizeOfImage;
} LOADED_IMAGE, *PLOADED_IMAGE;


BOOL
IMAGEAPI
BindImage(
    IN PSTR ImageName,
    IN PSTR DllPath,
    IN PSTR SymbolPath
    );

typedef enum _IMAGEHLP_STATUS_REASON {
    BindOutOfMemory,
    BindRvaToVaFailed,
    BindNoRoomInImage,
    BindImportModuleFailed,
    BindImportProcedureFailed,
    BindImportModule,
    BindImportProcedure,
    BindForwarder,
    BindForwarderNOT,
    BindImageModified,
    BindExpandFileHeaders,
    BindImageComplete,
    BindMismatchedSymbols,
    BindSymbolsNotUpdated
} IMAGEHLP_STATUS_REASON;

typedef
BOOL
(__stdcall *PIMAGEHLP_STATUS_ROUTINE)(
    IMAGEHLP_STATUS_REASON Reason,
    PSTR ImageName,
    PSTR DllName,
    ULONG_PTR Va,
    ULONG_PTR Parameter
    );


BOOL
IMAGEAPI
BindImageEx(
    IN DWORD Flags,
    IN PSTR ImageName,
    IN PSTR DllPath,
    IN PSTR SymbolPath,
    IN PIMAGEHLP_STATUS_ROUTINE StatusRoutine
    );

#define BIND_NO_BOUND_IMPORTS  0x00000001
#define BIND_NO_UPDATE         0x00000002
#define BIND_ALL_IMAGES        0x00000004
#define BIND_CACHE_IMPORT_DLLS 0x00000008       // Cache dll's across
                                                //  calls to BindImageEx
                                                //  (same as NT 3.1->NT 4.0)

BOOL
IMAGEAPI
ReBaseImage(
    IN     PSTR CurrentImageName,
    IN     PSTR SymbolPath,
    IN     BOOL  fReBase,           // TRUE if actually rebasing, false if only summing
    IN     BOOL  fRebaseSysfileOk,  // TRUE is system images s/b rebased
    IN     BOOL  fGoingDown,        // TRUE if the image s/b rebased below the given base
    IN     ULONG CheckImageSize,    // Max size allowed  (0 if don't care)
    OUT    ULONG *OldImageSize,     // Returned from the header
    OUT    ULONG_PTR *OldImageBase, // Returned from the header
    OUT    ULONG *NewImageSize,     // Image size rounded to next separation boundary
    IN OUT ULONG_PTR *NewImageBase, // (in) Desired new address.
                                    // (out) Next address (actual if going down)
    IN     ULONG TimeStamp          // new timestamp for image, if non-zero
    );

BOOL
IMAGEAPI
ReBaseImage64(
    IN     PSTR CurrentImageName,
    IN     PSTR SymbolPath,
    IN     BOOL  fReBase,          // TRUE if actually rebasing, false if only summing
    IN     BOOL  fRebaseSysfileOk, // TRUE is system images s/b rebased
    IN     BOOL  fGoingDown,       // TRUE if the image s/b rebased below the given base
    IN     ULONG CheckImageSize,   // Max size allowed  (0 if don't care)
    OUT    ULONG *OldImageSize,    // Returned from the header
    OUT    ULONG64 *OldImageBase,  // Returned from the header
    OUT    ULONG *NewImageSize,    // Image size rounded to next separation boundary
    IN OUT ULONG64 *NewImageBase,  // (in) Desired new address.
                                   // (out) Next address (actual if going down)
    IN     ULONG TimeStamp         // new timestamp for image, if non-zero
    );

//
// Define checksum return codes.
//

#define CHECKSUM_SUCCESS            0
#define CHECKSUM_OPEN_FAILURE       1
#define CHECKSUM_MAP_FAILURE        2
#define CHECKSUM_MAPVIEW_FAILURE    3
#define CHECKSUM_UNICODE_FAILURE    4

// Define Splitsym flags.

#define SPLITSYM_REMOVE_PRIVATE     0x00000001      // Remove CV types/symbols and Fixup debug
                                                    //  Used for creating .dbg files that ship
                                                    //  as part of the product.

#define SPLITSYM_EXTRACT_ALL        0x00000002      // Extract all debug info from image.
                                                    //  Normally, FPO is left in the image
                                                    //  to allow stack traces through the code.
                                                    //  Using this switch is similar to linking
                                                    //  with -debug:none except the .dbg file
                                                    //  exists...

#define SPLITSYM_SYMBOLPATH_IS_SRC  0x00000004      // The SymbolFilePath contains an alternate
                                                    //  path to locate the pdb.


//
// Define checksum function prototypes.
//

PIMAGE_NT_HEADERS
IMAGEAPI
CheckSumMappedFile (
    PVOID BaseAddress,
    DWORD FileLength,
    PDWORD HeaderSum,
    PDWORD CheckSum
    );

DWORD
IMAGEAPI
MapFileAndCheckSumA (
    PSTR Filename,
    PDWORD HeaderSum,
    PDWORD CheckSum
    );

DWORD
IMAGEAPI
MapFileAndCheckSumW (
    PWSTR Filename,
    PDWORD HeaderSum,
    PDWORD CheckSum
    );

#ifdef UNICODE
#define MapFileAndCheckSum  MapFileAndCheckSumW
#else
#define MapFileAndCheckSum  MapFileAndCheckSumA
#endif // !UNICODE

BOOL
IMAGEAPI
GetImageConfigInformation(
    PLOADED_IMAGE LoadedImage,
    PIMAGE_LOAD_CONFIG_DIRECTORY ImageConfigInformation
    );

DWORD
IMAGEAPI
GetImageUnusedHeaderBytes(
    PLOADED_IMAGE LoadedImage,
    PDWORD SizeUnusedHeaderBytes
    );

BOOL
IMAGEAPI
SetImageConfigInformation(
    PLOADED_IMAGE LoadedImage,
    PIMAGE_LOAD_CONFIG_DIRECTORY ImageConfigInformation
    );

// Image Integrity API's

#define CERT_PE_IMAGE_DIGEST_DEBUG_INFO         0x01
#define CERT_PE_IMAGE_DIGEST_RESOURCES          0x02
#define CERT_PE_IMAGE_DIGEST_ALL_IMPORT_INFO    0x04
#define CERT_PE_IMAGE_DIGEST_NON_PE_INFO        0x08      // include data outside the PE image

#define CERT_SECTION_TYPE_ANY                   0xFF      // Any Certificate type

typedef PVOID DIGEST_HANDLE;

typedef BOOL (WINAPI *DIGEST_FUNCTION) (DIGEST_HANDLE refdata, PBYTE pData, DWORD dwLength);

BOOL
IMAGEAPI
ImageGetDigestStream(
    IN      HANDLE  FileHandle,
    IN      DWORD   DigestLevel,
    IN      DIGEST_FUNCTION DigestFunction,
    IN      DIGEST_HANDLE   DigestHandle
    );

BOOL
IMAGEAPI
ImageAddCertificate(
    IN      HANDLE  FileHandle,
    IN      LPWIN_CERTIFICATE   Certificate,
    OUT     PDWORD  Index
    );

BOOL
IMAGEAPI
ImageRemoveCertificate(
    IN      HANDLE   FileHandle,
    IN      DWORD    Index
    );

BOOL
IMAGEAPI
ImageEnumerateCertificates(
    IN      HANDLE  FileHandle,
    IN      WORD    TypeFilter,
    OUT     PDWORD  CertificateCount,
    IN OUT  PDWORD  Indices OPTIONAL,
    IN OUT  DWORD   IndexCount  OPTIONAL
    );

BOOL
IMAGEAPI
ImageGetCertificateData(
    IN      HANDLE  FileHandle,
    IN      DWORD   CertificateIndex,
    OUT     LPWIN_CERTIFICATE Certificate,
    IN OUT  PDWORD  RequiredLength
    );

BOOL
IMAGEAPI
ImageGetCertificateHeader(
    IN      HANDLE  FileHandle,
    IN      DWORD   CertificateIndex,
    IN OUT  LPWIN_CERTIFICATE Certificateheader
    );

PLOADED_IMAGE
IMAGEAPI
ImageLoad(
    PSTR DllName,
    PSTR DllPath
    );

BOOL
IMAGEAPI
ImageUnload(
    PLOADED_IMAGE LoadedImage
    );

BOOL
IMAGEAPI
MapAndLoad(
    PSTR ImageName,
    PSTR DllPath,
    PLOADED_IMAGE LoadedImage,
    BOOL DotDll,
    BOOL ReadOnly
    );

BOOL
IMAGEAPI
UnMapAndLoad(
    PLOADED_IMAGE LoadedImage
    );

BOOL
IMAGEAPI
TouchFileTimes (
    HANDLE FileHandle,
    PSYSTEMTIME pSystemTime
    );

BOOL
IMAGEAPI
SplitSymbols (
    PSTR ImageName,
    PSTR SymbolsPath,
    PSTR SymbolFilePath,
    DWORD Flags                 // Combination of flags above
    );

BOOL
IMAGEAPI
UpdateDebugInfoFile(
    PSTR ImageFileName,
    PSTR SymbolPath,
    PSTR DebugFilePath,
    PIMAGE_NT_HEADERS32 NtHeaders
    );

BOOL
IMAGEAPI
UpdateDebugInfoFileEx(
    PSTR ImageFileName,
    PSTR SymbolPath,
    PSTR DebugFilePath,
    PIMAGE_NT_HEADERS32 NtHeaders,
    DWORD OldChecksum
    );


HANDLE
IMAGEAPI
FindDebugInfoFile (
    PSTR FileName,
    PSTR SymbolPath,
    PSTR DebugFilePath
    );

typedef BOOL
(CALLBACK *PFIND_DEBUG_FILE_CALLBACK)(
    HANDLE FileHandle,
    PSTR FileName,
    PVOID CallerData
    );

HANDLE
IMAGEAPI
FindDebugInfoFileEx (
    PSTR FileName,
    PSTR SymbolPath,
    PSTR DebugFilePath,
    PFIND_DEBUG_FILE_CALLBACK Callback,
    PVOID CallerData
    );

HANDLE
IMAGEAPI
FindExecutableImage(
    PSTR FileName,
    PSTR SymbolPath,
    PSTR ImageFilePath
    );

PIMAGE_NT_HEADERS
IMAGEAPI
ImageNtHeader (
    IN PVOID Base
    );

PVOID
IMAGEAPI
ImageDirectoryEntryToDataEx (
    IN PVOID Base,
    IN BOOLEAN MappedAsImage,
    IN USHORT DirectoryEntry,
    OUT PULONG Size,
    OUT PIMAGE_SECTION_HEADER *FoundHeader OPTIONAL
    );

PVOID
IMAGEAPI
ImageDirectoryEntryToData (
    IN PVOID Base,
    IN BOOLEAN MappedAsImage,
    IN USHORT DirectoryEntry,
    OUT PULONG Size
    );

PIMAGE_SECTION_HEADER
IMAGEAPI
ImageRvaToSection(
    IN PIMAGE_NT_HEADERS NtHeaders,
    IN PVOID Base,
    IN ULONG Rva
    );

PVOID
IMAGEAPI
ImageRvaToVa(
    IN PIMAGE_NT_HEADERS NtHeaders,
    IN PVOID Base,
    IN ULONG Rva,
    IN OUT PIMAGE_SECTION_HEADER *LastRvaSection
    );

#ifndef _WIN64
// This api won't be ported to Win64 - Fix your code.

typedef struct _IMAGE_DEBUG_INFORMATION {
    LIST_ENTRY List;
    DWORD ReservedSize;
    PVOID ReservedMappedBase;
    USHORT ReservedMachine;
    USHORT ReservedCharacteristics;
    DWORD ReservedCheckSum;
    DWORD ImageBase;
    DWORD SizeOfImage;

    DWORD ReservedNumberOfSections;
    PIMAGE_SECTION_HEADER ReservedSections;

    DWORD ReservedExportedNamesSize;
    PSTR ReservedExportedNames;

    DWORD ReservedNumberOfFunctionTableEntries;
    PIMAGE_FUNCTION_ENTRY ReservedFunctionTableEntries;
    DWORD ReservedLowestFunctionStartingAddress;
    DWORD ReservedHighestFunctionEndingAddress;

    DWORD ReservedNumberOfFpoTableEntries;
    PFPO_DATA ReservedFpoTableEntries;

    DWORD SizeOfCoffSymbols;
    PIMAGE_COFF_SYMBOLS_HEADER CoffSymbols;

    DWORD ReservedSizeOfCodeViewSymbols;
    PVOID ReservedCodeViewSymbols;

    PSTR ImageFilePath;
    PSTR ImageFileName;
    PSTR ReservedDebugFilePath;

    DWORD ReservedTimeDateStamp;

    BOOL  ReservedRomImage;
    PIMAGE_DEBUG_DIRECTORY ReservedDebugDirectory;
    DWORD ReservedNumberOfDebugDirectories;

    DWORD ReservedOriginalFunctionTableBaseAddress;

    DWORD Reserved[ 2 ];

} IMAGE_DEBUG_INFORMATION, *PIMAGE_DEBUG_INFORMATION;


PIMAGE_DEBUG_INFORMATION
IMAGEAPI
MapDebugInformation(
    HANDLE FileHandle,
    PSTR FileName,
    PSTR SymbolPath,
    DWORD ImageBase
    );

BOOL
IMAGEAPI
UnmapDebugInformation(
    PIMAGE_DEBUG_INFORMATION DebugInfo
    );

#endif

BOOL
IMAGEAPI
SearchTreeForFile(
    PSTR RootPath,
    PSTR InputPathName,
    PSTR OutputPathBuffer
    );

BOOL
IMAGEAPI
MakeSureDirectoryPathExists(
    PCSTR DirPath
    );

//
// UnDecorateSymbolName Flags
//

#define UNDNAME_COMPLETE                 (0x0000)  // Enable full undecoration
#define UNDNAME_NO_LEADING_UNDERSCORES   (0x0001)  // Remove leading underscores from MS extended keywords
#define UNDNAME_NO_MS_KEYWORDS           (0x0002)  // Disable expansion of MS extended keywords
#define UNDNAME_NO_FUNCTION_RETURNS      (0x0004)  // Disable expansion of return type for primary declaration
#define UNDNAME_NO_ALLOCATION_MODEL      (0x0008)  // Disable expansion of the declaration model
#define UNDNAME_NO_ALLOCATION_LANGUAGE   (0x0010)  // Disable expansion of the declaration language specifier
#define UNDNAME_NO_MS_THISTYPE           (0x0020)  // NYI Disable expansion of MS keywords on the 'this' type for primary declaration
#define UNDNAME_NO_CV_THISTYPE           (0x0040)  // NYI Disable expansion of CV modifiers on the 'this' type for primary declaration
#define UNDNAME_NO_THISTYPE              (0x0060)  // Disable all modifiers on the 'this' type
#define UNDNAME_NO_ACCESS_SPECIFIERS     (0x0080)  // Disable expansion of access specifiers for members
#define UNDNAME_NO_THROW_SIGNATURES      (0x0100)  // Disable expansion of 'throw-signatures' for functions and pointers to functions
#define UNDNAME_NO_MEMBER_TYPE           (0x0200)  // Disable expansion of 'static' or 'virtual'ness of members
#define UNDNAME_NO_RETURN_UDT_MODEL      (0x0400)  // Disable expansion of MS model for UDT returns
#define UNDNAME_32_BIT_DECODE            (0x0800)  // Undecorate 32-bit decorated names
#define UNDNAME_NAME_ONLY                (0x1000)  // Crack only the name for primary declaration;
                                                                                                   //  return just [scope::]name.  Does expand template params
#define UNDNAME_NO_ARGUMENTS             (0x2000)  // Don't undecorate arguments to function
#define UNDNAME_NO_SPECIAL_SYMS          (0x4000)  // Don't undecorate special names (v-table, vcall, vector xxx, metatype, etc)

DWORD
IMAGEAPI
WINAPI
UnDecorateSymbolName(
    PCSTR   DecoratedName,         // Name to undecorate
    PSTR    UnDecoratedName,       // If NULL, it will be allocated
    DWORD    UndecoratedLength,     // The maximym length
    DWORD    Flags                  // See above.
    );

//
// StackWalking API
//

typedef enum {
    AddrMode1616,
    AddrMode1632,
    AddrModeReal,
    AddrModeFlat
} ADDRESS_MODE;

typedef struct _tagADDRESS64 {
    DWORD64       Offset;
    WORD          Segment;
    ADDRESS_MODE  Mode;
} ADDRESS64, *LPADDRESS64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define ADDRESS ADDRESS64
#define LPADDRESS LPADDRESS64
#else
typedef struct _tagADDRESS {
    DWORD         Offset;
    WORD          Segment;
    ADDRESS_MODE  Mode;
} ADDRESS, *LPADDRESS;

__inline
void
Address32To64(
    LPADDRESS a32,
    LPADDRESS64 a64
    )
{
    a64->Offset = (ULONG64)(LONG64)(LONG)a32->Offset;
    a64->Segment = a32->Segment;
    a64->Mode = a32->Mode;
}

__inline
void
Address64To32(
    LPADDRESS64 a64,
    LPADDRESS a32
    )
{
    a32->Offset = (ULONG)a64->Offset;
    a32->Segment = a64->Segment;
    a32->Mode = a64->Mode;
}
#endif

//
// This structure is included in the STACKFRAME structure,
// and is used to trace through usermode callbacks in a thread's
// kernel stack.  The values must be copied by the kernel debugger
// from the DBGKD_GET_VERSION and WAIT_STATE_CHANGE packets.
//

//
// New KDHELP structure for 64 bit system support.
// This structure is preferred in new code.
//
typedef struct _KDHELP64 {

    //
    // address of kernel thread object, as provided in the
    // WAIT_STATE_CHANGE packet.
    //
    DWORD64   Thread;

    //
    // offset in thread object to pointer to the current callback frame
    // in kernel stack.
    //
    DWORD   ThCallbackStack;

    //
    // offset in thread object to pointer to the current callback backing
    // store frame in kernel stack.
    //
    DWORD   ThCallbackBStore;

    //
    // offsets to values in frame:
    //
    // address of next callback frame
    DWORD   NextCallback;

    // address of saved frame pointer (if applicable)
    DWORD   FramePointer;


    //
    // Address of the kernel function that calls out to user mode
    //
    DWORD64   KiCallUserMode;

    //
    // Address of the user mode dispatcher function
    //
    DWORD64   KeUserCallbackDispatcher;

    //
    // Lowest kernel mode address
    //
    DWORD64   SystemRangeStart;

    DWORD64  Reserved[8];

} KDHELP64, *PKDHELP64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define KDHELP KDHELP64
#define PKDHELP PKDHELP64
#else
typedef struct _KDHELP {

    //
    // address of kernel thread object, as provided in the
    // WAIT_STATE_CHANGE packet.
    //
    DWORD   Thread;

    //
    // offset in thread object to pointer to the current callback frame
    // in kernel stack.
    //
    DWORD   ThCallbackStack;

    //
    // offsets to values in frame:
    //
    // address of next callback frame
    DWORD   NextCallback;

    // address of saved frame pointer (if applicable)
    DWORD   FramePointer;

    //
    // Address of the kernel function that calls out to user mode
    //
    DWORD   KiCallUserMode;

    //
    // Address of the user mode dispatcher function
    //
    DWORD   KeUserCallbackDispatcher;

    //
    // Lowest kernel mode address
    //
    DWORD   SystemRangeStart;

    //
    // offset in thread object to pointer to the current callback backing
    // store frame in kernel stack.
    //
    DWORD   ThCallbackBStore;

    DWORD  Reserved[8];

} KDHELP, *PKDHELP;

__inline
void
KdHelp32To64(
    PKDHELP p32,
    PKDHELP64 p64
    )
{
    p64->Thread = p32->Thread;
    p64->ThCallbackStack = p32->ThCallbackStack;
    p64->NextCallback = p32->NextCallback;
    p64->FramePointer = p32->FramePointer;
    p64->KiCallUserMode = p32->KiCallUserMode;
    p64->KeUserCallbackDispatcher = p32->KeUserCallbackDispatcher;
    p64->SystemRangeStart = p32->SystemRangeStart;
}
#endif

typedef struct _tagSTACKFRAME64 {
    ADDRESS64   AddrPC;               // program counter
    ADDRESS64   AddrReturn;           // return address
    ADDRESS64   AddrFrame;            // frame pointer
    ADDRESS64   AddrStack;            // stack pointer
    ADDRESS64   AddrBStore;           // backing store pointer
    PVOID       FuncTableEntry;       // pointer to pdata/fpo or NULL
    DWORD64     Params[4];            // possible arguments to the function
    BOOL        Far;                  // WOW far call
    BOOL        Virtual;              // is this a virtual frame?
    DWORD64     Reserved[3];
    KDHELP64    KdHelp;
} STACKFRAME64, *LPSTACKFRAME64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define STACKFRAME STACKFRAME64
#define LPSTACKFRAME LPSTACKFRAME64
#else
typedef struct _tagSTACKFRAME {
    ADDRESS     AddrPC;               // program counter
    ADDRESS     AddrReturn;           // return address
    ADDRESS     AddrFrame;            // frame pointer
    ADDRESS     AddrStack;            // stack pointer
    PVOID       FuncTableEntry;       // pointer to pdata/fpo or NULL
    DWORD       Params[4];            // possible arguments to the function
    BOOL        Far;                  // WOW far call
    BOOL        Virtual;              // is this a virtual frame?
    DWORD       Reserved[3];
    KDHELP      KdHelp;
    ADDRESS     AddrBStore;           // backing store pointer
} STACKFRAME, *LPSTACKFRAME;
#endif


typedef
BOOL
(__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)(
    HANDLE      hProcess,
    DWORD64     qwBaseAddress,
    PVOID       lpBuffer,
    DWORD       nSize,
    LPDWORD     lpNumberOfBytesRead
    );

typedef
PVOID
(__stdcall *PFUNCTION_TABLE_ACCESS_ROUTINE64)(
    HANDLE  hProcess,
    DWORD64 AddrBase
    );

typedef
DWORD64
(__stdcall *PGET_MODULE_BASE_ROUTINE64)(
    HANDLE  hProcess,
    DWORD64 Address
    );

typedef
DWORD64
(__stdcall *PTRANSLATE_ADDRESS_ROUTINE64)(
    HANDLE    hProcess,
    HANDLE    hThread,
    LPADDRESS64 lpaddr
    );

BOOL
IMAGEAPI
StackWalk64(
    DWORD                             MachineType,
    HANDLE                            hProcess,
    HANDLE                            hThread,
    LPSTACKFRAME64                    StackFrame,
    PVOID                             ContextRecord,
    PREAD_PROCESS_MEMORY_ROUTINE64    ReadMemoryRoutine,
    PFUNCTION_TABLE_ACCESS_ROUTINE64  FunctionTableAccessRoutine,
    PGET_MODULE_BASE_ROUTINE64        GetModuleBaseRoutine,
    PTRANSLATE_ADDRESS_ROUTINE64      TranslateAddress
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)

#define PREAD_PROCESS_MEMORY_ROUTINE PREAD_PROCESS_MEMORY_ROUTINE64
#define PFUNCTION_TABLE_ACCESS_ROUTINE PFUNCTION_TABLE_ACCESS_ROUTINE64
#define PGET_MODULE_BASE_ROUTINE PGET_MODULE_BASE_ROUTINE64
#define PTRANSLATE_ADDRESS_ROUTINE PTRANSLATE_ADDRESS_ROUTINE64

#define StackWalk StackWalk64

#else

typedef
BOOL
(__stdcall *PREAD_PROCESS_MEMORY_ROUTINE)(
    HANDLE  hProcess,
    DWORD   lpBaseAddress,
    PVOID   lpBuffer,
    DWORD   nSize,
    PDWORD  lpNumberOfBytesRead
    );

typedef
PVOID
(__stdcall *PFUNCTION_TABLE_ACCESS_ROUTINE)(
    HANDLE  hProcess,
    DWORD   AddrBase
    );

typedef
DWORD
(__stdcall *PGET_MODULE_BASE_ROUTINE)(
    HANDLE  hProcess,
    DWORD   Address
    );

typedef
DWORD
(__stdcall *PTRANSLATE_ADDRESS_ROUTINE)(
    HANDLE    hProcess,
    HANDLE    hThread,
    LPADDRESS lpaddr
    );

BOOL
IMAGEAPI
StackWalk(
    DWORD                             MachineType,
    HANDLE                            hProcess,
    HANDLE                            hThread,
    LPSTACKFRAME                      StackFrame,
    PVOID                             ContextRecord,
    PREAD_PROCESS_MEMORY_ROUTINE      ReadMemoryRoutine,
    PFUNCTION_TABLE_ACCESS_ROUTINE    FunctionTableAccessRoutine,
    PGET_MODULE_BASE_ROUTINE          GetModuleBaseRoutine,
    PTRANSLATE_ADDRESS_ROUTINE        TranslateAddress
    );

#endif


#define API_VERSION_NUMBER 9

typedef struct API_VERSION {
    USHORT  MajorVersion;
    USHORT  MinorVersion;
    USHORT  Revision;
    USHORT  Reserved;
} API_VERSION, *LPAPI_VERSION;

LPAPI_VERSION
IMAGEAPI
ImagehlpApiVersion(
    VOID
    );

LPAPI_VERSION
IMAGEAPI
ImagehlpApiVersionEx(
    LPAPI_VERSION AppVersion
    );

DWORD
IMAGEAPI
GetTimestampForLoadedLibrary(
    HMODULE Module
    );

//
// typedefs for function pointers
//
typedef BOOL
(CALLBACK *PSYM_ENUMMODULES_CALLBACK64)(
    PSTR ModuleName,
    DWORD64 BaseOfDll,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PSYM_ENUMSYMBOLS_CALLBACK64)(
    PSTR SymbolName,
    DWORD64 SymbolAddress,
    ULONG SymbolSize,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PSYM_ENUMSYMBOLS_CALLBACK64W)(
    PWSTR SymbolName,
    DWORD64 SymbolAddress,
    ULONG SymbolSize,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PENUMLOADED_MODULES_CALLBACK64)(
    PSTR ModuleName,
    DWORD64 ModuleBase,
    ULONG ModuleSize,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PSYMBOL_REGISTERED_CALLBACK64)(
    HANDLE  hProcess,
    ULONG   ActionCode,
    ULONG64 CallbackData,
    ULONG64 UserContext
    );

typedef
PVOID
(CALLBACK *PSYMBOL_FUNCENTRY_CALLBACK)(
    HANDLE  hProcess,
    DWORD   AddrBase,
    PVOID   UserContext
    );

typedef
PVOID
(CALLBACK *PSYMBOL_FUNCENTRY_CALLBACK64)(
    HANDLE  hProcess,
    ULONG64 AddrBase,
    ULONG64 UserContext
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)

#define PSYM_ENUMMODULES_CALLBACK PSYM_ENUMMODULES_CALLBACK64
#define PSYM_ENUMSYMBOLS_CALLBACK PSYM_ENUMSYMBOLS_CALLBACK64
#define PSYM_ENUMSYMBOLS_CALLBACKW PSYM_ENUMSYMBOLS_CALLBACK64W
#define PENUMLOADED_MODULES_CALLBACK PENUMLOADED_MODULES_CALLBACK64
#define PSYMBOL_REGISTERED_CALLBACK PSYMBOL_REGISTERED_CALLBACK64
#define PSYMBOL_FUNCENTRY_CALLBACK PSYMBOL_FUNCENTRY_CALLBACK64

#else

typedef BOOL
(CALLBACK *PSYM_ENUMMODULES_CALLBACK)(
    PSTR  ModuleName,
    ULONG BaseOfDll,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PSYM_ENUMSYMBOLS_CALLBACK)(
    PSTR  SymbolName,
    ULONG SymbolAddress,
    ULONG SymbolSize,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PSYM_ENUMSYMBOLS_CALLBACKW)(
    PWSTR  SymbolName,
    ULONG SymbolAddress,
    ULONG SymbolSize,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PENUMLOADED_MODULES_CALLBACK)(
    PSTR  ModuleName,
    ULONG ModuleBase,
    ULONG ModuleSize,
    PVOID UserContext
    );

typedef BOOL
(CALLBACK *PSYMBOL_REGISTERED_CALLBACK)(
    HANDLE  hProcess,
    ULONG   ActionCode,
    PVOID   CallbackData,
    PVOID   UserContext
    );

#endif


//
// symbol flags
//

#define SYMF_OMAP_GENERATED   0x00000001
#define SYMF_OMAP_MODIFIED    0x00000002

//
// symbol type enumeration
//
typedef enum {
    SymNone,
    SymCoff,
    SymCv,
    SymPdb,
    SymExport,
    SymDeferred,
    SymSym                  // .sym file
} SYM_TYPE;

//
// symbol data structure
//

typedef struct _IMAGEHLP_SYMBOL64 {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_SYMBOL64)
    DWORD64                     Address;                // virtual address including dll base address
    DWORD                       Size;                   // estimated size of symbol, can be zero
    DWORD                       Flags;                  // info about the symbols, see the SYMF defines
    DWORD                       MaxNameLength;          // maximum size of symbol name in 'Name'
    CHAR                        Name[1];                // symbol name (null terminated string)
} IMAGEHLP_SYMBOL64, *PIMAGEHLP_SYMBOL64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define IMAGEHLP_SYMBOL IMAGEHLP_SYMBOL64
#define PIMAGEHLP_SYMBOL PIMAGEHLP_SYMBOL64
#else
typedef struct _IMAGEHLP_SYMBOL {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_SYMBOL)
    DWORD                       Address;                // virtual address including dll base address
    DWORD                       Size;                   // estimated size of symbol, can be zero
    DWORD                       Flags;                  // info about the symbols, see the SYMF defines
    DWORD                       MaxNameLength;          // maximum size of symbol name in 'Name'
    CHAR                        Name[1];                // symbol name (null terminated string)
} IMAGEHLP_SYMBOL, *PIMAGEHLP_SYMBOL;
#endif

//
// module data structure
//

typedef struct _IMAGEHLP_MODULE64 {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_MODULE64)
    DWORD64                     BaseOfImage;            // base load address of module
    DWORD                       ImageSize;              // virtual size of the loaded module
    DWORD                       TimeDateStamp;          // date/time stamp from pe header
    DWORD                       CheckSum;               // checksum from the pe header
    DWORD                       NumSyms;                // number of symbols in the symbol table
    SYM_TYPE                    SymType;                // type of symbols loaded
    CHAR                        ModuleName[32];         // module name
    CHAR                        ImageName[256];         // image name
    CHAR                        LoadedImageName[256];   // symbol file name
} IMAGEHLP_MODULE64, *PIMAGEHLP_MODULE64;

typedef struct _IMAGEHLP_MODULE64W {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_MODULE64)
    DWORD64                     BaseOfImage;            // base load address of module
    DWORD                       ImageSize;              // virtual size of the loaded module
    DWORD                       TimeDateStamp;          // date/time stamp from pe header
    DWORD                       CheckSum;               // checksum from the pe header
    DWORD                       NumSyms;                // number of symbols in the symbol table
    SYM_TYPE                    SymType;                // type of symbols loaded
    WCHAR                       ModuleName[32];         // module name
    WCHAR                       ImageName[256];         // image name
    WCHAR                       LoadedImageName[256];   // symbol file name
} IMAGEHLP_MODULEW64, *PIMAGEHLP_MODULEW64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define IMAGEHLP_MODULE IMAGEHLP_MODULE64
#define PIMAGEHLP_MODULE PIMAGEHLP_MODULE64
#define IMAGEHLP_MODULEW IMAGEHLP_MODULEW64
#define PIMAGEHLP_MODULEW PIMAGEHLP_MODULEW64
#else
typedef struct _IMAGEHLP_MODULE {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_MODULE)
    DWORD                       BaseOfImage;            // base load address of module
    DWORD                       ImageSize;              // virtual size of the loaded module
    DWORD                       TimeDateStamp;          // date/time stamp from pe header
    DWORD                       CheckSum;               // checksum from the pe header
    DWORD                       NumSyms;                // number of symbols in the symbol table
    SYM_TYPE                    SymType;                // type of symbols loaded
    CHAR                        ModuleName[32];         // module name
    CHAR                        ImageName[256];         // image name
    CHAR                        LoadedImageName[256];   // symbol file name
} IMAGEHLP_MODULE, *PIMAGEHLP_MODULE;

typedef struct _IMAGEHLP_MODULEW {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_MODULE)
    DWORD                       BaseOfImage;            // base load address of module
    DWORD                       ImageSize;              // virtual size of the loaded module
    DWORD                       TimeDateStamp;          // date/time stamp from pe header
    DWORD                       CheckSum;               // checksum from the pe header
    DWORD                       NumSyms;                // number of symbols in the symbol table
    SYM_TYPE                    SymType;                // type of symbols loaded
    WCHAR                       ModuleName[32];         // module name
    WCHAR                       ImageName[256];         // image name
    WCHAR                       LoadedImageName[256];   // symbol file name
} IMAGEHLP_MODULEW, *PIMAGEHLP_MODULEW;
#endif

//
// source file line data structure
//

typedef struct _IMAGEHLP_LINE64 {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_LINE64)
    PVOID                       Key;                    // internal
    DWORD                       LineNumber;             // line number in file
    PCHAR                       FileName;               // full filename
    DWORD64                     Address;                // first instruction of line
} IMAGEHLP_LINE64, *PIMAGEHLP_LINE64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define IMAGEHLP_LINE IMAGEHLP_LINE64
#define PIMAGEHLP_LINE PIMAGEHLP_LINE64
#else
typedef struct _IMAGEHLP_LINE {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_LINE)
    PVOID                       Key;                    // internal
    DWORD                       LineNumber;             // line number in file
    PCHAR                       FileName;               // full filename
    DWORD                       Address;                // first instruction of line
} IMAGEHLP_LINE, *PIMAGEHLP_LINE;
#endif

//
// data structures used for registered symbol callbacks
//

#define CBA_DEFERRED_SYMBOL_LOAD_START          0x00000001
#define CBA_DEFERRED_SYMBOL_LOAD_COMPLETE       0x00000002
#define CBA_DEFERRED_SYMBOL_LOAD_FAILURE        0x00000003
#define CBA_SYMBOLS_UNLOADED                    0x00000004
#define CBA_DUPLICATE_SYMBOL                    0x00000005
#define CBA_READ_MEMORY                         0x00000006
#define CBA_DEBUG_INFO                          0x10000000

typedef struct _IMAGEHLP_CBA_READ_MEMORY {
    DWORD64   addr;                                     // address to read from
    PVOID     buf;                                      // buffer to read to
    DWORD     bytes;                                    // amount of bytes to read
    DWORD    *bytesread;                                // pointer to store amount of bytes read
} IMAGEHLP_CBA_READ_MEMORY, *PIMAGEHLP_CBA_READ_MEMORY;

typedef struct _IMAGEHLP_DEFERRED_SYMBOL_LOAD64 {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_DEFERRED_SYMBOL_LOAD64)
    DWORD64                     BaseOfImage;            // base load address of module
    DWORD                       CheckSum;               // checksum from the pe header
    DWORD                       TimeDateStamp;          // date/time stamp from pe header
    CHAR                        FileName[MAX_PATH];     // symbols file or image name
    BOOLEAN                     Reparse;                // load failure reparse
} IMAGEHLP_DEFERRED_SYMBOL_LOAD64, *PIMAGEHLP_DEFERRED_SYMBOL_LOAD64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define IMAGEHLP_DEFERRED_SYMBOL_LOAD IMAGEHLP_DEFERRED_SYMBOL_LOAD64
#define PIMAGEHLP_DEFERRED_SYMBOL_LOAD PIMAGEHLP_DEFERRED_SYMBOL_LOAD64
#else
typedef struct _IMAGEHLP_DEFERRED_SYMBOL_LOAD {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_DEFERRED_SYMBOL_LOAD)
    DWORD                       BaseOfImage;            // base load address of module
    DWORD                       CheckSum;               // checksum from the pe header
    DWORD                       TimeDateStamp;          // date/time stamp from pe header
    CHAR                        FileName[MAX_PATH];     // symbols file or image name
    BOOLEAN                     Reparse;                // load failure reparse
} IMAGEHLP_DEFERRED_SYMBOL_LOAD, *PIMAGEHLP_DEFERRED_SYMBOL_LOAD;
#endif

typedef struct _IMAGEHLP_DUPLICATE_SYMBOL64 {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_DUPLICATE_SYMBOL64)
    DWORD                       NumberOfDups;           // number of duplicates in the Symbol array
    PIMAGEHLP_SYMBOL64          Symbol;                 // array of duplicate symbols
    DWORD                       SelectedSymbol;         // symbol selected (-1 to start)
} IMAGEHLP_DUPLICATE_SYMBOL64, *PIMAGEHLP_DUPLICATE_SYMBOL64;

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define IMAGEHLP_DUPLICATE_SYMBOL IMAGEHLP_DUPLICATE_SYMBOL64
#define PIMAGEHLP_DUPLICATE_SYMBOL PIMAGEHLP_DUPLICATE_SYMBOL64
#else
typedef struct _IMAGEHLP_DUPLICATE_SYMBOL {
    DWORD                       SizeOfStruct;           // set to sizeof(IMAGEHLP_DUPLICATE_SYMBOL)
    DWORD                       NumberOfDups;           // number of duplicates in the Symbol array
    PIMAGEHLP_SYMBOL            Symbol;                 // array of duplicate symbols
    DWORD                       SelectedSymbol;         // symbol selected (-1 to start)
} IMAGEHLP_DUPLICATE_SYMBOL, *PIMAGEHLP_DUPLICATE_SYMBOL;
#endif


//
// options that are set/returned by SymSetOptions() & SymGetOptions()
// these are used as a mask
//
#define SYMOPT_CASE_INSENSITIVE  0x00000001
#define SYMOPT_UNDNAME           0x00000002
#define SYMOPT_DEFERRED_LOADS    0x00000004
#define SYMOPT_NO_CPP            0x00000008
#define SYMOPT_LOAD_LINES        0x00000010
#define SYMOPT_OMAP_FIND_NEAREST 0x00000020
#define SYMOPT_DEBUG             0x80000000


DWORD
IMAGEAPI
SymSetOptions(
    IN DWORD   SymOptions
    );

DWORD
IMAGEAPI
SymGetOptions(
    VOID
    );

BOOL
IMAGEAPI
SymCleanup(
    IN HANDLE hProcess
    );

BOOL
IMAGEAPI
SymEnumerateModules64(
    IN HANDLE                       hProcess,
    IN PSYM_ENUMMODULES_CALLBACK64  EnumModulesCallback,
    IN PVOID                        UserContext
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymEnumerateModules SymEnumerateModules64
#else
BOOL
IMAGEAPI
SymEnumerateModules(
    IN HANDLE                     hProcess,
    IN PSYM_ENUMMODULES_CALLBACK  EnumModulesCallback,
    IN PVOID                      UserContext
    );
#endif

BOOL
IMAGEAPI
SymEnumerateSymbols64(
    IN HANDLE                       hProcess,
    IN DWORD64                      BaseOfDll,
    IN PSYM_ENUMSYMBOLS_CALLBACK64  EnumSymbolsCallback,
    IN PVOID                        UserContext
    );

BOOL
IMAGEAPI
SymEnumerateSymbolsW64(
    IN HANDLE                       hProcess,
    IN DWORD64                      BaseOfDll,
    IN PSYM_ENUMSYMBOLS_CALLBACK64W EnumSymbolsCallback,
    IN PVOID                        UserContext
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymEnumerateSymbols SymEnumerateSymbols64
#define SymEnumerateSymbolsW SymEnumerateSymbolsW64
#else
BOOL
IMAGEAPI
SymEnumerateSymbols(
    IN HANDLE                     hProcess,
    IN DWORD                      BaseOfDll,
    IN PSYM_ENUMSYMBOLS_CALLBACK  EnumSymbolsCallback,
    IN PVOID                      UserContext
    );

BOOL
IMAGEAPI
SymEnumerateSymbolsW(
    IN HANDLE                       hProcess,
    IN DWORD                        BaseOfDll,
    IN PSYM_ENUMSYMBOLS_CALLBACKW   EnumSymbolsCallback,
    IN PVOID                        UserContext
    );
#endif

BOOL
IMAGEAPI
EnumerateLoadedModules64(
    IN HANDLE                           hProcess,
    IN PENUMLOADED_MODULES_CALLBACK64   EnumLoadedModulesCallback,
    IN PVOID                            UserContext
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define EnumerateLoadedModules EnumerateLoadedModules64
#else
BOOL
IMAGEAPI
EnumerateLoadedModules(
    IN HANDLE                         hProcess,
    IN PENUMLOADED_MODULES_CALLBACK   EnumLoadedModulesCallback,
    IN PVOID                          UserContext
    );
#endif

PVOID
IMAGEAPI
SymFunctionTableAccess64(
    HANDLE  hProcess,
    DWORD64 AddrBase
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymFunctionTableAccess SymFunctionTableAccess64
#else
PVOID
IMAGEAPI
SymFunctionTableAccess(
    HANDLE  hProcess,
    DWORD   AddrBase
    );
#endif

BOOL
IMAGEAPI
SymGetModuleInfo64(
    IN  HANDLE                  hProcess,
    IN  DWORD64                 qwAddr,
    OUT PIMAGEHLP_MODULE64      ModuleInfo
    );

BOOL
IMAGEAPI
SymGetModuleInfoW64(
    IN  HANDLE                  hProcess,
    IN  DWORD64                 qwAddr,
    OUT PIMAGEHLP_MODULEW64     ModuleInfo
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetModuleInfo   SymGetModuleInfo64
#define SymGetModuleInfoW  SymGetModuleInfoW64
#else
BOOL
IMAGEAPI
SymGetModuleInfo(
    IN  HANDLE              hProcess,
    IN  DWORD               dwAddr,
    OUT PIMAGEHLP_MODULE  ModuleInfo
    );

BOOL
IMAGEAPI
SymGetModuleInfoW(
    IN  HANDLE              hProcess,
    IN  DWORD               dwAddr,
    OUT PIMAGEHLP_MODULEW  ModuleInfo
    );
#endif

DWORD64
IMAGEAPI
SymGetModuleBase64(
    IN  HANDLE              hProcess,
    IN  DWORD64             qwAddr
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetModuleBase SymGetModuleBase64
#else
DWORD
IMAGEAPI
SymGetModuleBase(
    IN  HANDLE              hProcess,
    IN  DWORD               dwAddr
    );
#endif

BOOL
IMAGEAPI
SymGetSymFromAddr64(
    IN  HANDLE              hProcess,
    IN  DWORD64             qwAddr,
    OUT PDWORD64            pdwDisplacement,
    OUT PIMAGEHLP_SYMBOL64  Symbol
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetSymFromAddr SymGetSymFromAddr64
#else
BOOL
IMAGEAPI
SymGetSymFromAddr(
    IN  HANDLE            hProcess,
    IN  DWORD             dwAddr,
    OUT PDWORD            pdwDisplacement,
    OUT PIMAGEHLP_SYMBOL  Symbol
    );
#endif

BOOL
IMAGEAPI
SymGetSymFromName64(
    IN  HANDLE              hProcess,
    IN  PSTR                Name,
    OUT PIMAGEHLP_SYMBOL64  Symbol
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetSymFromName SymGetSymFromName64
#else
BOOL
IMAGEAPI
SymGetSymFromName(
    IN  HANDLE            hProcess,
    IN  PSTR              Name,
    OUT PIMAGEHLP_SYMBOL  Symbol
    );
#endif

BOOL
IMAGEAPI
SymGetSymNext64(
    IN     HANDLE              hProcess,
    IN OUT PIMAGEHLP_SYMBOL64  Symbol
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetSymNext SymGetSymNext64
#else
BOOL
IMAGEAPI
SymGetSymNext(
    IN     HANDLE            hProcess,
    IN OUT PIMAGEHLP_SYMBOL  Symbol
    );
#endif

BOOL
IMAGEAPI
SymGetSymPrev64(
    IN     HANDLE              hProcess,
    IN OUT PIMAGEHLP_SYMBOL64  Symbol
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetSymPrev SymGetSymPrev64
#else
BOOL
IMAGEAPI
SymGetSymPrev(
    IN     HANDLE            hProcess,
    IN OUT PIMAGEHLP_SYMBOL  Symbol
    );
#endif

BOOL
IMAGEAPI
SymGetLineFromAddr64(
    IN  HANDLE                  hProcess,
    IN  DWORD64                 qwAddr,
    OUT PDWORD                  pdwDisplacement,
    OUT PIMAGEHLP_LINE64        Line
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetLineFromAddr SymGetLineFromAddr64
#else
BOOL
IMAGEAPI
SymGetLineFromAddr(
    IN  HANDLE                hProcess,
    IN  DWORD                 dwAddr,
    OUT PDWORD                pdwDisplacement,
    OUT PIMAGEHLP_LINE        Line
    );
#endif

BOOL
IMAGEAPI
SymGetLineFromName64(
    IN     HANDLE               hProcess,
    IN     PSTR                 ModuleName,
    IN     PSTR                 FileName,
    IN     DWORD                dwLineNumber,
       OUT PLONG                plDisplacement,
    IN OUT PIMAGEHLP_LINE64     Line
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetLineFromName SymGetLineFromName64
#else
BOOL
IMAGEAPI
SymGetLineFromName(
    IN     HANDLE             hProcess,
    IN     PSTR               ModuleName,
    IN     PSTR               FileName,
    IN     DWORD              dwLineNumber,
       OUT PLONG              plDisplacement,
    IN OUT PIMAGEHLP_LINE     Line
    );
#endif

BOOL
IMAGEAPI
SymGetLineNext64(
    IN     HANDLE               hProcess,
    IN OUT PIMAGEHLP_LINE64     Line
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetLineNext SymGetLineNext64
#else
BOOL
IMAGEAPI
SymGetLineNext(
    IN     HANDLE             hProcess,
    IN OUT PIMAGEHLP_LINE     Line
    );
#endif

BOOL
IMAGEAPI
SymGetLinePrev64(
    IN     HANDLE               hProcess,
    IN OUT PIMAGEHLP_LINE64     Line
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymGetLinePrev SymGetLinePrev64
#else
BOOL
IMAGEAPI
SymGetLinePrev(
    IN     HANDLE             hProcess,
    IN OUT PIMAGEHLP_LINE     Line
    );
#endif

BOOL
IMAGEAPI
SymMatchFileName(
    IN  PSTR  FileName,
    IN  PSTR  Match,
    OUT PSTR *FileNameStop,
    OUT PSTR *MatchStop
    );

BOOL
IMAGEAPI
SymInitialize(
    IN HANDLE   hProcess,
    IN PSTR     UserSearchPath,
    IN BOOL     fInvadeProcess
    );

BOOL
IMAGEAPI
SymGetSearchPath(
    IN  HANDLE          hProcess,
    OUT PSTR            SearchPath,
    IN  DWORD           SearchPathLength
    );

BOOL
IMAGEAPI
SymSetSearchPath(
    IN HANDLE           hProcess,
    IN PSTR             SearchPath
    );

DWORD64
IMAGEAPI
SymLoadModule64(
    IN  HANDLE          hProcess,
    IN  HANDLE          hFile,
    IN  PSTR            ImageName,
    IN  PSTR            ModuleName,
    IN  DWORD64         BaseOfDll,
    IN  DWORD           SizeOfDll
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymLoadModule SymLoadModule64
#else
DWORD
IMAGEAPI
SymLoadModule(
    IN  HANDLE          hProcess,
    IN  HANDLE          hFile,
    IN  PSTR            ImageName,
    IN  PSTR            ModuleName,
    IN  DWORD           BaseOfDll,
    IN  DWORD           SizeOfDll
    );
#endif

BOOL
IMAGEAPI
SymUnloadModule64(
    IN  HANDLE          hProcess,
    IN  DWORD64         BaseOfDll
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymUnloadModule SymUnloadModule64
#else
BOOL
IMAGEAPI
SymUnloadModule(
    IN  HANDLE          hProcess,
    IN  DWORD           BaseOfDll
    );
#endif

BOOL
IMAGEAPI
SymUnDName64(
    IN  PIMAGEHLP_SYMBOL64 sym,               // Symbol to undecorate
    OUT PSTR               UnDecName,         // Buffer to store undecorated name in
    IN  DWORD              UnDecNameLength    // Size of the buffer
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymUnDName SymUnDName64
#else
BOOL
IMAGEAPI
SymUnDName(
    IN  PIMAGEHLP_SYMBOL sym,               // Symbol to undecorate
    OUT PSTR             UnDecName,         // Buffer to store undecorated name in
    IN  DWORD            UnDecNameLength    // Size of the buffer
    );
#endif

BOOL
IMAGEAPI
SymRegisterCallback64(
    IN HANDLE                        hProcess,
    IN PSYMBOL_REGISTERED_CALLBACK64 CallbackFunction,
    IN ULONG64                       UserContext
    );

BOOL
IMAGEAPI
SymRegisterFunctionEntryCallback64(
    IN HANDLE                       hProcess,
    IN PSYMBOL_FUNCENTRY_CALLBACK64 CallbackFunction,
    IN ULONG64                      UserContext
    );

#if !defined(_IMAGEHLP_SOURCE_) && defined(_IMAGEHLP64)
#define SymRegisterCallback SymRegisterCallback64
#define SymRegisterFunctionEntryCallback SymRegisterFunctionEntryCallback64
#else
BOOL
IMAGEAPI
SymRegisterCallback(
    IN HANDLE                      hProcess,
    IN PSYMBOL_REGISTERED_CALLBACK CallbackFunction,
    IN PVOID                       UserContext
    );

BOOL
IMAGEAPI
SymRegisterFunctionEntryCallback(
    IN HANDLE                     hProcess,
    IN PSYMBOL_FUNCENTRY_CALLBACK CallbackFunction,
    IN PVOID                      UserContext
    );
#endif

#ifdef __cplusplus
}
#endif


#endif // _IMAGEHLP_

/*//////////////////////////////////////////////////////////////////////
                            Special Defines
//////////////////////////////////////////////////////////////////////*/
// The defines that set up how the functions or classes are exported or
//  imported.
#ifndef BUGSUTIL_DLLINTERFACE
#ifdef BUILDING_BUGSUTILITY_DLL
#define BUGSUTIL_DLLINTERFACE __declspec ( dllexport )
#else
#define BUGSUTIL_DLLINTERFACE __declspec ( dllimport )
#endif  // BUILDING_BUGSTILITY_DLL
#endif  // BUGSUTIL_DLLINTERFACE

/*//////////////////////////////////////////////////////////////////////
                            Special Includes
//////////////////////////////////////////////////////////////////////*/
// Include the headers that do the memory dumping and validation
//  routines.
// Force the include of the debug run-time header file and make sure the
//  allocation mapping functions are in effect.
//#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef __cplusplus
extern "C" {
#endif      // __cplusplus

// This library can only be used in _DEBUG builds.
#ifdef _DEBUG

////////////////////////////////////////////////////////////////////////
// The typedefs for the dumper and validator functions.
////////////////////////////////////////////////////////////////////////
// The memory dumper function.  The only parameter is a pointer to the
//  block of memory.  This function can output the memory data for the
//  block any way it likes but it might be nice if it uses the same
//  Debug CRT reporting mechanism that everything else in the runtime
//  uses.
typedef void (*PFNMEMDUMPER)(const void *) ;
// The validator function.  The first parameter is the memory block to
//  validate and the second parameter is the context information passed
//  to the ValidateAllBlocks function.
typedef void (*PFNMEMVALIDATOR)(const void * , const void *) ;

////////////////////////////////////////////////////////////////////////
// Useful Macros.
////////////////////////////////////////////////////////////////////////
// The macro used to set a client block value.  This is the ONLY
//  approved means of setting a value for the dwValue field in the
//  DVINFO structure below.
#define CLIENT_BLOCK_VALUE(x) (_CLIENT_BLOCK|(x<<16))
// A macro to pick out the subtype.
#define CLIENT_BLOCK_SUBTYPE(x) ((x >> 16) & 0xFFFF)

////////////////////////////////////////////////////////////////////////
// The header used to initialize the dumper and validator for a specific
//  type of client block.
////////////////////////////////////////////////////////////////////////
typedef struct tag_DVINFO
{
    // The value for the client blocks.  This must be set with the
    //  CLIENT_BLOCK_VALUE macro above.  See the AddClientDV function
    //  for how to have the library assign this number.
    unsigned long   dwValue      ;
    // The pointer to the dumper function.
    PFNMEMDUMPER    pfnDump     ;
    // The pointer to the dumper function.
    PFNMEMVALIDATOR pfnValidate ;
} DVINFO , * LPDVINFO ;

/*----------------------------------------------------------------------
FUNCTION        :   AddClientDV
DISCUSSION      :
    Adds a client block dumper and validator to the list.  If the
dwValue field in the DVINFO structure is ZERO, then the next value in
the list is assigned.  This means that the value returned must always be
passed to _malloc_dbg as the value of the client block.
    If the value is set with CLIENT_BLOCK_VALUE, then a macro can be
used for the value to _malloc_dbg.
    No, there is no corresponding remove function.  Why possibly
introduce bugs in debugging code?  Performance is a non issue when it
comes to finding errors.
PARAMETERS      :
    lpDVInfo - The pointer to the DVINFO structure.
RETURNS         :
    1 - The client block dumper and validator was properly added.
    0 - The client block dumper and validator could not be added.
----------------------------------------------------------------------*/
    int BUGSUTIL_DLLINTERFACE __stdcall AddClientDV (LPDVINFO lpDVInfo);

/*----------------------------------------------------------------------
FUNCTION        :   ValidateAllBlocks
DISCUSSION      :
    Checks all the memory allocated out of the local heap.  Also goes
through all client blocks and calls the special validator function for
the different types of client blocks.
    It is probably best to call this function with the VALIDATEALLBLOCKS
macro below.
PARAMETERS      :
    pContext - The context information that will be passed to each
               call to the validator function.
RETURNS         :
    None.
----------------------------------------------------------------------*/
    void BUGSUTIL_DLLINTERFACE __stdcall
                                 ValidateAllBlocks ( void * pContext ) ;

#ifdef __cplusplus
////////////////////////////////////////////////////////////////////////
// Helper C++ class macros.
////////////////////////////////////////////////////////////////////////
// Declare this macro in your class just like the MFC ones.
#define DECLARE_MEMDEBUG(classname)                                 \
public   :                                                          \
    static DVINFO  m_stDVInfo ;                                     \
    static void ClassDumper ( const void * pData ) ;                \
    static void ClassValidator ( const void * pData ,               \
                                     const void * pContext )       ;\
    static void * operator new ( size_t nSize )                     \
    {                                                               \
        if ( 0 == m_stDVInfo.dwValue )                              \
        {                                                           \
            m_stDVInfo.pfnDump     = classname::ClassDumper ;       \
            m_stDVInfo.pfnValidate = classname::ClassValidator ;    \
            AddClientDV ( &m_stDVInfo ) ;                           \
        }                                                           \
        return ( _malloc_dbg ( nSize                   ,            \
                               (int)m_stDVInfo.dwValue ,            \
                               __FILE__                ,            \
                               __LINE__                 ) ) ;       \
    }                                                               \
    static void * operator new ( size_t nSize        ,              \
                                 char * lpszFileName ,              \
                                 int    nLine         )             \
    {                                                               \
        if ( 0 == m_stDVInfo.dwValue )                              \
        {                                                           \
            m_stDVInfo.pfnDump     = classname::ClassDumper ;       \
            m_stDVInfo.pfnValidate = classname::ClassValidator ;    \
            AddClientDV ( &m_stDVInfo ) ;                           \
        }                                                           \
        return ( _malloc_dbg ( nSize                   ,            \
                               (int)m_stDVInfo.dwValue ,            \
                               lpszFileName            ,            \
                               nLine                    ) ) ;       \
    }                                                               \
    static void operator delete ( void * pData )                    \
    {                                                               \
        _free_dbg ( pData , (int)m_stDVInfo.dwValue ) ;             \
    }

// Declare this one at the top of the CPP file.
#define IMPLEMENT_MEMDEBUG(classname)                               \
    DVINFO  classname::m_stDVInfo

// The macro for memory debugging allocations.  If DEBUG_NEW is defined,
//  then it can be used.
#ifdef DEBUG_NEW
#define MEMDEBUG_NEW DEBUG_NEW
#else
#define MEMDEBUG_NEW new ( __FILE__ , __LINE__ )
#endif

#endif      // __cplusplus defined.

////////////////////////////////////////////////////////////////////////
// Helper C macros.
////////////////////////////////////////////////////////////////////////

// For C style allocations, here is the macro to use.  Unfortunately,
//  with C it is not so easy to use the auto-increment feature of
//  AddClientDV.
#define INITIALIZE_MEMDEBUG(bType , pfnD , pfnV )   \
    {                                               \
        DVINFO dvInfo ;                             \
        dvInfo.dwValue = bType ;                    \
        dvInfo.pfnDump = pfnD ;                     \
        dvInfo.pfnValidate = pfnV ;                 \
        AddClientDV ( &dvInfo ) ;                   \
    }

// The macros that map the C-style allocations.  It might be easier if
//  you use macros to wrap these so you don't have to remember which
//  client block value to drag around with each memory usage function.
#define MEMDEBUG_MALLOC(bType , nSize)  \
            _malloc_dbg ( nSize , bType , __FILE__ , __LINE__ )
#define MEMDEBUG_REALLOC(bType , pBlock , nSize)    \
            _realloc_dbg( pBlock , nSize , bType , __FILE__ , __LINE__ )
#define MEMDEBUG_EXPAND(bType , pBlock , nSize )    \
            _expand_dbg( pBlock , nSize , bType , __FILE__ , __LINE__ )
#define MEMDEBUG_FREE(bType , pBlock)   \
            _free_dbg ( pBlock , bType )
#define MEMDEBUG_MSIZE(bType , pBlock)  \
            _msize_dbg ( pBlock , bType )

// Macro to call ValidateAllBlocks
#define VALIDATEALLBLOCKS(x)   ValidateAllBlocks ( x )

#else       // _DEBUG is NOT defined

#ifdef __cplusplus
#define DECLARE_MEMDEBUG(classname)
#define IMPLEMENT_MEMDEBUG(classname)
#define MEMDEBUG_NEW new
#endif      // __cplusplus

#define MEMDEBUG_MALLOC(bType , nSize)              malloc ( nSize )
#define MEMDEBUG_REALLOC(bType , pBlock , nSize)    \
                                              realloc ( pBlock , nSize )
#define MEMDEBUG_EXPAND(bType , pBlock , nSize)     \
                                              _expand ( pBlock , nSize )
#define MEMDEBUG_FREE(bType , pBlock)               free ( pBlock )
#define MEMDEBUG_MSIZE(bType , pBlock)              _msize ( pBlock )

#define VALIDATEALLBLOCKS(x)

#endif      // _DEBUG

#ifdef __cplusplus
}
#endif      // __cplusplus


/*//////////////////////////////////////////////////////////////////////
                            Type Definitions
//////////////////////////////////////////////////////////////////////*/
// The type for the filter function called by the Crash Handler API.
typedef LONG ( __stdcall *PFNCHFILTFN ) ( EXCEPTION_POINTERS * pExPtrs ) ;

/*//////////////////////////////////////////////////////////////////////
                   Crash Handler Function Definitions
//////////////////////////////////////////////////////////////////////*/

/*----------------------------------------------------------------------
FUNCTION        :   SetCrashHandlerFilter
DISCUSSION      :
    Sets the filter function that will be called when there is a fatal
crash.  The passed in function will only be called if the crash is one
of the modules passed to AddCrashHandlerLimitModule.  If no modules have
been added to narrow down the interested modules then the callback
filter function will always be called.
PARAMETERS      :
    pFn - A valid code pointer.  If this is NULL, then the Crash Handler
          filter function is removed.
RETURNS         :
    1 - The crash handler was properly set.
    0 - There was a problem.
----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall
                             SetCrashHandlerFilter ( PFNCHFILTFN pFn ) ;

/*----------------------------------------------------------------------
FUNCTION        :   AddCrashHandlerLimitModule
DISCUSSION      :
    Adds a module to the list of modules that CrashHandler will call the
callbeack function for.  If no modules are added, then the callback is
called for all crashes.  Limiting the specific modules allows the crash
handler to be installed for just the modules you are responsible for.
PARAMETERS      :
    hMod - The HMODULE or HINSTANCE.
RETURNS         :
    1 - The module was added.
    0 - There was a problem.
----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall
                           AddCrashHandlerLimitModule ( HMODULE hMod ) ;

/*----------------------------------------------------------------------
FUNCTION        :   GetLimitModuleCount
DISCUSSION      :
    Returns the number of limit modules for the crash handler.
PARAMETERS      :
    None.
RETURNS         :
    The item count.  This can be zero if not limiting modules have been
added.
----------------------------------------------------------------------*/
UINT BUGSUTIL_DLLINTERFACE __stdcall GetLimitModuleCount ( void ) ;

/*----------------------------------------------------------------------
FUNCTION        :   GetLimitModulesArray
DISCUSSION      :
    Returns the limit modules currently active.
PARAMETERS      :
    pahMod - The array that the active limit modules are copied into.
    uiSize - The size of ahMod in items.
RETURNS         :
    Note:  Since VB blows away the last error value, this function
           returns values indicating what went wrong.
    GLMA_SUCCESS        - The limit items where copied.
    GLMA_BADPARAM       - The parameter(s) were invalid.
    GLMA_BUFFTOOSMALL   - The ahMod was too small to copy all the
                          values.
    GLMA_FAILURE        - There was a major problem.
----------------------------------------------------------------------*/
#define GLMA_SUCCESS        1
#define GLMA_BADPARAM       -1
#define GLMA_BUFFTOOSMALL   -2
#define GLMA_FAILURE        0
int BUGSUTIL_DLLINTERFACE __stdcall
               GetLimitModulesArray ( HMODULE * pahMod , UINT uiSize ) ;

/*//////////////////////////////////////////////////////////////////////
          EXCEPTION_POINTER Translation Functions Declarations
//////////////////////////////////////////////////////////////////////*/

/*----------------------------------------------------------------------
FUNCTION        :   GetFaultReason
DISCUSSION      :
    Returns a string that describes the fault that occured.  The return
string looks similar to the string returned by Win95's fault dialog.
The returned buffer is constant and do not change it.
    This function can only be called from the callback.
PARAMETERS      :
    pExPtrs - The exeption pointers passed to the callback.
RETURNS         :
    !NULL - The constant string that describes the fault.
    NULL  - There was a problem translating the string.
----------------------------------------------------------------------*/
LPCTSTR BUGSUTIL_DLLINTERFACE __stdcall
                       GetFaultReason ( EXCEPTION_POINTERS * pExPtrs ) ;

/*----------------------------------------------------------------------
FUNCTION        :   GetFaultReasonVB
DISCUSSION      :
    The VB wrapper for GetFaultReason.  This calls GetFaultReason and
copys the resulting string into the passed in buffer.
PARAMETERS      :
    pExPtrs - The exeption pointers passed to the callback.
    szBuff  - The output buffer.
    uiSize  - The size of the output buffer.
RETURNS         :
    TRUE  - The buffer is filled.
    FALSE - There was a problem.
----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall
                       GetFaultReasonVB ( EXCEPTION_POINTERS * pExPtrs ,
                                          LPTSTR               szBuff  ,
                                          UINT                 uiSize );

/*----------------------------------------------------------------------
FUNCTION        :   GetFirstStackTraceString
                    GetNextStackTraceString
DISCUSSION      :
    These functions allow you to get the stack trace information for a
crash.  Call GetFirstStackTraceString and then GetNextStackTraceString
to get the entire stack trace for a crash.
    The options GSTSO_PARAMS, GSTSO_MODULE, GSTSO_SYMBOL, and
GSTSO_SRCLINE, appear in that order in the string.
PARAMETERS      :
    dwOpts   - The options flags  "Or" the following options together.
                0             - Just put the PC address in the string.
                GSTSO_PARAMS  - Include the possible params.
                GSTSO_MODULE  - Include the module name as well.
                GSTSO_SYMBOL  - Include the symbol name of the stack
                                address.
                GSTSO_SRCLINE - Include source and line info of the
                                stack address.
    pExtPtrs - The exception pointers passed to the crash handler
               function.
RETURNS         :
    !NULL - The requested stack trace string.
    NULL  - There was a problem.
----------------------------------------------------------------------*/
#define GSTSO_PARAMS    0x01
#define GSTSO_MODULE    0x02
#define GSTSO_SYMBOL    0x04
#define GSTSO_SRCLINE   0x08
LPCTSTR BUGSUTIL_DLLINTERFACE __stdcall
             GetFirstStackTraceString ( DWORD                dwOpts  ,
                                        EXCEPTION_POINTERS * pExPtrs  );
LPCTSTR BUGSUTIL_DLLINTERFACE __stdcall
             GetNextStackTraceString ( DWORD                dwOpts  ,
                                       EXCEPTION_POINTERS * pExPtrs  ) ;

/*----------------------------------------------------------------------
FUNCTION        :   GetFirstStackTraceStringVB
                    GetNextStackTraceStringVB
DISCUSSION      :
    The VB wrappers on GetFirstStackTraceString and
GetNextStackTraceString since VB cannot handle returning a string from
a DLL call.
PARAMETERS      :
    dwOpts   - The options flags  "Or" the following options together.
                0             - Just put the PC address in the string.
                GSTSO_PARAMS  - Include the possible params.
                GSTSO_MODULE  - Include the module name as well.
                GSTSO_SYMBOL  - Include the symbol name the stack
                                address.
                GSTSO_SRCLINE - Include source and line info for the
                                address.
    pExtPtrs - The exception pointers passed to the crash handler
               function.
    szBuff   - The output buffer.
    uiSize   - The size of the output buffer.
RETURNS         :
    TRUE  - The string was copied into szBuff.
    FALSE - There was a problem.
----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall
           GetFirstStackTraceStringVB ( DWORD                dwOpts  ,
                                        EXCEPTION_POINTERS * pExPtrs ,
                                        LPTSTR               szBuff  ,
                                        UINT                 uiSize   );
BOOL BUGSUTIL_DLLINTERFACE __stdcall
           GetNextStackTraceStringVB ( DWORD                dwOpts  ,
                                       EXCEPTION_POINTERS * pExPtrs ,
                                       LPTSTR               szBuff  ,
                                       UINT                 uiSize   );

/*----------------------------------------------------------------------
FUNCTION        :   GetRegisterString
DISCUSSION      :
    Returns a string with all the registers and their values.  This
function hides all the platform differences.
PARAMETERS      :
    pExtPtrs - The exception pointers passed to the crash handler
               function.
RETURNS         :
    !NULL - The requested register string.
    NULL  - There was a problem.
----------------------------------------------------------------------*/
LPCTSTR BUGSUTIL_DLLINTERFACE __stdcall
              GetRegisterString ( EXCEPTION_POINTERS * pExPtrs ) ;

/*----------------------------------------------------------------------
FUNCTION        :   GetRegisterStringVB
DISCUSSION      :
    Handles GetRegisterString for VB.
PARAMETERS      :
    pExtPtrs - The exception pointers passed to the crash handler
               function.
    szBuff   - The output buffer.
    uiSize   - The size of the output buffer.
RETURNS         :
    TRUE  - The string was copied into szBuff.
    FALSE - There was a problem.
----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall
              GetRegisterStringVB ( EXCEPTION_POINTERS * pExPtrs ,
                                    LPTSTR               szBuff  ,
                                    UINT                 uiSize   ) ;

#ifndef __cplusplus
}
#endif  //__cplusplus

/*//////////////////////////////////////////////////////////////////////
                      C Function Declaration Area
                                 START
//////////////////////////////////////////////////////////////////////*/
#ifdef __cplusplus
extern "C" {
#endif  // _cplusplus

/*----------------------------------------------------------------------
FUNCTION        :   GetLoadedModules
DISCUSSION      :
    For the specified process id, this function returns the HMODULES for
all modules loaded into that process address space.  This function works
for both NT and 95.
PARAMETERS      :
    dwPID        - The process ID to look into.
    uiCount      - The number of slots in the paModArray buffer.  If
                   this value is 0, then the return value will be TRUE
                   and puiRealCount will hold the number of items
                   needed.
    paModArray   - The array to place the HMODULES into.  If this buffer
                   is too small to hold the result and uiCount is not
                   zero, then FALSE is returned, but puiRealCount will
                   be the real number of items needed.
    puiRealCount - The count of items needed in paModArray, if uiCount
                   is zero, or the real number of items in paModArray.
RETURNS         :
    FALSE - There was a problem, check GetLastError.
    TRUE  - The function succeeded.  See the parameter discussion for
            the output parameters.
----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall
                           GetLoadedModules ( DWORD     dwPID        ,
                                              UINT      uiCount      ,
                                              HMODULE * paModArray   ,
                                              LPUINT    puiRealCount  );

/*----------------------------------------------------------------------
FUNCTION        :   AllocAndFillProcessModuleList
DISCUSSION      :
    Hides the work to get the loaded module list for the current
process.  This function returns a pointer to memory allocated from the
specified heap and that memory must be deallocated with a call to
HeapFree from the same heap.
PARAMETERS      :
    hHeap    - The heap to allocate from.
    puiCount - The total elements in the returned array.
RETURNS         :
    NULL  - There was a problem.
    !NULL - The block of memory holding the HMODULEs.
----------------------------------------------------------------------*/
HMODULE * /*BUGSUTIL_DLLINTERFACE*/ __stdcall
                     AllocAndFillProcessModuleList ( HANDLE hHeap    ,
                                                     LPUINT puiCount  );

typedef struct tag_HOOKFUNCDESCA
{
    // The name of the function to hook.
    LPCSTR szFunc   ;
    // The procedure to blast in.
    PROC   pProc    ;
} HOOKFUNCDESCA , * LPHOOKFUNCDESCA ;

typedef struct tag_HOOKFUNCDESCW
{
    // The name of the function to hook.
    LPCWSTR szFunc   ;
    // The procedure to blast in.
    PROC    pProc    ;
} HOOKFUNCDESCW , * LPHOOKFUNCDESCW ;

#ifdef UNICODE
#define HOOKFUNCDESC   HOOKFUNCDESCW
#define LPHOOKFUNCDESC LPHOOKFUNCDESCW
#else
#define HOOKFUNCDESC   HOOKFUNCDESCA
#define LPHOOKFUNCDESC LPHOOKFUNCDESCA
#endif  // UNICODE

/*----------------------------------------------------------------------
FUNCTION        :   HookImportedFunctionsByName
DISCUSSION      :
    Hooks the specified functions imported into hModule by the module
indicated by szImportMod.  This function can be used to hook from one
to 'n' of the functions imported.
    The techniques used in the function are slightly different than
that shown by Matt Pietrek in his book, "Windows 95 System Programming
Secrets."  He uses the address of the function to hook as returned by
GetProcAddress.  Unfortunately, while this works in almost all cases, it
does not work when the program being hooked is running under a debugger
on Windows95 (and presumably, Windows98).  The problem is that
GetProcAddress under a debugger returns a "debug thunk," not the address
that is stored in the Import Address Table (IAT).
    This function gets around that by using the real thunk list in the
PE file, the one not bashed by the loader when the module is loaded and
fixed up, to find where the named import is located.  Once the named
import is found, then the original table is blasted to make the hook.
As the name implies, this function will only hook functions imported by
name.
PARAMETERS      :
    hModule     - The module where the imports will be hooked.
    szImportMod - The name of the module whose functions will be
                  imported.
    uiCount     - The number of functions to hook.  This is the size of
                  the paHookArray and paOrigFuncs arrays.
    paHookArray - The array of function descriptors that list which
                  functions to hook.  At this point, the array does not
                  have to be in szFunc name order.  Also, if a
                  particular pProc is NULL, then that item will just be
                  skipped.  This makes it much easier for debugging.
    paOrigFuncs - The array of original addresses that were hooked.  If
                  a function was not hooked, then that item will be
                  NULL.  This parameter can be NULL if the returned
                  information is not needed.
    puiHooked   - Returns the number of functions hooked out of
                  paHookArray.  This parameter can be NULL if the
                  returned information is not needed.
RETURNS         :
    FALSE - There was a problem, check GetLastError.
    TRUE  - The function succeeded.  See the parameter discussion for
            the output parameters.
----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall
        HookImportedFunctionsByName ( HMODULE         hModule     ,
                                      LPCSTR          szImportMod ,
                                      UINT            uiCount     ,
                                      LPHOOKFUNCDESCA paHookArray ,
                                      PROC *          paOrigFuncs ,
                                      LPUINT          puiHooked    ) ;

/*----------------------------------------------------------------------
FUNCTION        :   BSUGetModuleBaseName
DISCUSSION      :
    Returns the base name of the specified module in a manner that is
portable between NT and Win95/98.
PARAMETERS      :
    hProcess   - The handle to the process.  In Win95/98 this is
                 ignored.
    hModule    - The module to look up.  If this is NULL, then the
                 module returned is the executable.
    lpBaseName - The buffer that recieves the base name.
    nSize      - The size of the buffer.
RETURNS         :
    !0 - The length of the string copied to the buffer.
    0  - The function failed.  To get extended error information,
         call GetLastError
----------------------------------------------------------------------*/
DWORD BUGSUTIL_DLLINTERFACE __stdcall
      BSUGetModuleBaseName ( HANDLE  hProcess   ,
                             HMODULE hModule    ,
                             LPTSTR  lpBaseName ,
                             DWORD   nSize       ) ;

/*----------------------------------------------------------------------
FUNCTION        :   IsNT
DISCUSSION      :
    Returns TRUE if the operating system is NT.  I simply got tired of
always having to call GetVersionEx each time I needed to check.
Additionally, I also need to check the OS inside loops so this function
caches the results so it is faster.
PARAMETERS      :
    None.
RETURNS         :

----------------------------------------------------------------------*/
BOOL BUGSUTIL_DLLINTERFACE __stdcall IsNT ( void ) ;


#ifdef __cplusplus
}
#endif  // _cplusplus
/*//////////////////////////////////////////////////////////////////////
                                  END
                      C Function Declaration Area
//////////////////////////////////////////////////////////////////////*/

/*//////////////////////////////////////////////////////////////////////
                         C++ Only Declarations
                                 START
//////////////////////////////////////////////////////////////////////*/
#ifdef __cplusplus

#include "imagehlp.h"
#include <tchar.h>

// Include these in case the user forgets to link against them.
#pragma comment (lib,"imagehlp.lib")
#pragma comment (lib,"version.lib")

// The API_VERSION_NUMBER define is 5 with the NT4 IMAGEHLP.H.  It is
//  7 with the November Platform SDK version.  This seems to be the only
//  reliable way to see which header is being used.
#if ( API_VERSION_NUMBER < 7 )
#define SYMENG_EXTRAWORK
#define SYMENG_NEEDDECLS
#else
#undef SYMENG_EXTRAWORK
#undef SYMENG_NEEDDECLS
#endif

// If FLEXIBLE_SYMBOLENGINE is defined, ALWAYS define SYMENG_EXTRAWORK
#ifdef FLEXIBLE_SYMBOLENGINE
#define SYMENG_EXTRAWORK
#endif // FLEXIBLE_SYMBOLENGINE

// I will define the structures that need defining in case the included
//  IMAGEHLP.H is from NT4.0.

#ifdef SYMENG_NEEDDECLS
// source file line data structure
typedef struct _IMAGEHLP_LINE
{
    DWORD SizeOfStruct;           // set to sizeof(IMAGEHLP_LINE)
    DWORD Key;                    // internal
    DWORD LineNumber;             // line number in file
    PCHAR FileName;               // full filename
    DWORD Address;                // first instruction of line
} IMAGEHLP_LINE, *PIMAGEHLP_LINE;
#endif  // SYMENG_NEEDDECLS

#ifndef SYMOPT_LOAD_LINES
#define SYMOPT_LOAD_LINES        0x00000010
#endif  // SYMOPT_LOAD_LINES

#ifndef SYMOPT_OMAP_FIND_NEAREST
#define SYMOPT_OMAP_FIND_NEAREST 0x00000020
#endif  // SYMOPT_OMAP_FIND_NEAREST

/*//////////////////////////////////////////////////////////////////////
I just lifted the prototypes right out of the NT5 header.

Note: I had a whopper of a bug here.  I had the declarations and
      typedefs like the following:

    BOOL
    IMAGEAPI
    SymGetLineFromAddr(
        IN  HANDLE                  hProcess,
        IN  DWORD                   dwAddr,
        OUT PDWORD                  pdwDisplacement,
        OUT PIMAGEHLP_LINE          Line
        );

    typedef
    BOOL (*PFNSYMGETLINEFROMADDR) ( IN  HANDLE         hProcess        ,
                                    IN  DWORD          dwAddr          ,
                                    OUT PDWORD         pdwDisplacement ,
                                    OUT PIMAGEHLP_LINE Line           );

    Whenever I ran the release build, it always crashed because the
    stack was not restoring the registers when certain functions in this
    class were called.  Looking at the disassembly, I kept seeing
    instructions like ADD ESP,10h after certain calls.  This was driving
    me nuts until it dawned on me that the extra ADD after the calls
    were cleaning up the stack for CDECL calls but that Windows API
    calls are all STDCALL.  I had a calling convention mismatch!

    I just thought I'd mention this so that it might save you some
    problems if you do something like this.  Watch those calling
    conventions!

//////////////////////////////////////////////////////////////////////*/

#ifdef SYMENG_NEEDDECLS
BOOL
__stdcall
SymGetLineFromAddr(
    IN  HANDLE                  hProcess,
    IN  DWORD                   dwAddr,
    OUT PDWORD                  pdwDisplacement,
    OUT PIMAGEHLP_LINE          Line
    );

BOOL
__stdcall
SymGetLineFromName(
    IN     HANDLE               hProcess,
    IN     LPSTR                ModuleName,
    IN     LPSTR                FileName,
    IN     DWORD                dwLineNumber,
       OUT PLONG                plDisplacement,
    IN OUT PIMAGEHLP_LINE       Line
    );

BOOL
__stdcall
SymGetLineNext(
    IN     HANDLE               hProcess,
    IN OUT PIMAGEHLP_LINE       Line
    );

BOOL
__stdcall
SymGetLinePrev(
    IN     HANDLE               hProcess,
    IN OUT PIMAGEHLP_LINE       Line
    );

BOOL
__stdcall
SymMatchFileName(
    IN  LPSTR  FileName,
    IN  LPSTR  Match,
    OUT LPSTR *FileNameStop,
    OUT LPSTR *MatchStop
    );
#endif  // SYMENG_NEEDDECLS

// The great Bugslayer idea of creating wrapper classes on structures
//  that have size fields came from fellow MSJ columnist, Paul DiLascia.
// Thanks, Paul!

// I did not wrap IMAGEHLP_SYMBOL because that is a variable size
//  structure.

// The IMAGEHLP_MODULE wrapper class.
struct CImageHlp_Module : public IMAGEHLP_MODULE
{
    CImageHlp_Module ( )
    {
        memset ( this , NULL , sizeof ( IMAGEHLP_MODULE ) ) ;
        SizeOfStruct = sizeof ( IMAGEHLP_MODULE ) ;
    }
} ;

// The IMAGEHLP_LINE wrapper class.
struct CImageHlp_Line : public IMAGEHLP_LINE
{
    CImageHlp_Line ( )
    {
        memset ( this , NULL , sizeof ( IMAGEHLP_LINE ) ) ;
        SizeOfStruct = sizeof ( IMAGEHLP_LINE ) ;
    }
} ;

// Typedefs for the new source and line functions.
typedef
BOOL (__stdcall *PFNSYMGETLINEFROMADDR)
                              ( IN  HANDLE         hProcess         ,
                                IN  DWORD          dwAddr           ,
                                OUT PDWORD         pdwDisplacement  ,
                                OUT PIMAGEHLP_LINE Line              ) ;
typedef
BOOL (__stdcall *PFNSYMGETLINEFROMNAME)
                              ( IN     HANDLE         hProcess      ,
                                IN     LPSTR          ModuleName    ,
                                IN     LPSTR          FileName      ,
                                IN     DWORD          dwLineNumber  ,
                                OUT    PLONG          plDisplacement,
                                IN OUT PIMAGEHLP_LINE Line           ) ;
typedef
BOOL (__stdcall *PFNSYMGETLINENEXT) ( IN     HANDLE         hProcess ,
                                      IN OUT PIMAGEHLP_LINE Line      );
typedef
BOOL (__stdcall *PFNSYMGETLINEPREV) ( IN     HANDLE         hProcess ,
                                      IN OUT PIMAGEHLP_LINE Line      );
typedef
BOOL (__stdcall *PFNSYMMATCHFILENAME) ( IN  LPSTR   FileName      ,
                                        IN  LPSTR   Match         ,
                                        OUT LPSTR * FileNameStop  ,
                                        OUT LPSTR * MatchStop      ) ;

// The symbol engine class.
class CSymbolEngine
{
/*----------------------------------------------------------------------
                  Public Construction and Destruction
----------------------------------------------------------------------*/
public      :
    // The constructor just does the work of finding the new functions.
    //  Use this class just line the normal C functions and call the
    //  SymInitialize function to get everything started.
    CSymbolEngine ( void )
    {
#ifdef SYMENG_EXTRAWORK
        HINSTANCE hInstImageHlp = GetModuleHandleA ( "IMAGEHLP.DLL" ) ;

        m_pfnSymGetLineFromAddr =
            (PFNSYMGETLINEFROMADDR)GetProcAddress(hInstImageHlp ,
                                                  "SymGetLineFromAddr");
        if ( NULL == m_pfnSymGetLineFromAddr )
        {
            m_pfnSymGetLineFromName = NULL ;
            m_pfnSymGetLineNext     = NULL ;
            m_pfnSymGetLinePrev     = NULL ;
            m_pfnSymMatchFileName   = NULL ;
        }
        else
        {
            m_pfnSymGetLineFromName =
               (PFNSYMGETLINEFROMNAME)GetProcAddress(hInstImageHlp ,
                                                  "SymGetLineFromName");
            m_pfnSymGetLineNext     =
               (PFNSYMGETLINENEXT)GetProcAddress ( hInstImageHlp  ,
                                                   "SymGetLineNext" ) ;
            m_pfnSymGetLinePrev     =
               (PFNSYMGETLINEPREV)GetProcAddress ( hInstImageHlp  ,
                                                   "SymGetLinePrev"  ) ;
            m_pfnSymMatchFileName   =
               (PFNSYMMATCHFILENAME)GetProcAddress (hInstImageHlp ,
                                                    "SymMatchFileName");
        }
#endif  // SYMENG_EXTRAWORK
    }

    virtual ~CSymbolEngine ( void )
    {
    }

/*----------------------------------------------------------------------
                  Public Helper Information Functions
----------------------------------------------------------------------*/
public      :

    BOOL CanDoSourceLines ( void )
    {
#ifdef SYMENG_EXTRAWORK
        return ( NULL != m_pfnSymGetLineFromAddr ) ;
#else
        return ( TRUE ) ;
#endif  // SYMENG_EXTRAWORK
    }

    // Returns the file version string of IMAGEHLP.DLL being used.
    // To convert the return values into something readable:
    // wsprintf ( szVer                  ,
    //            _T ( "%d.%02d.%d.%d" ) ,
    //            HIWORD ( dwMS )        ,
    //            LOWORD ( dwMS )        ,
    //            HIWORD ( dwLS )        ,
    //            LOWORD ( dwLS )         ) ;
    // szVer will contain a string like: 5.00.1878.1
    BOOL GetImageHlpVersion ( DWORD & dwMS , DWORD & dwLS )
    {
        return( GetInMemoryFileVersion ( "IMAGEHLP.DLL" , dwMS , dwLS));
    }

    // Does the same thing for the PDB reading DLLs.
    BOOL GetPDBReaderVersion ( DWORD & dwMS , DWORD & dwLS )
    {
        // First try MSDBI.DLL.
        if ( TRUE == GetInMemoryFileVersion ( "MSDBI.DLL" ,
                                              dwMS        ,
                                              dwLS          ) )
        {
            return ( TRUE ) ;
        }
        // MSDBI.DLL is not in memory so try MSPDB50.DLL.
        return ( GetInMemoryFileVersion ( "MSPDB50.DLL" , dwMS , dwLS));
    }

    // The worker function used by the previous two functions.
    BOOL GetInMemoryFileVersion ( LPCTSTR szFile ,
                                  DWORD & dwMS   ,
                                  DWORD & dwLS    )
    {
        HMODULE hInstIH = GetModuleHandle ( szFile ) ;

        // Get the full filename of the loaded version.
        TCHAR szImageHlp[ MAX_PATH ] ;
        GetModuleFileName ( hInstIH , szImageHlp , MAX_PATH ) ;

        dwMS = 0 ;
        dwLS = 0 ;

        // Get the version info size.
        DWORD dwVerInfoHandle ;
        DWORD dwVerSize       ;

        dwVerSize = GetFileVersionInfoSize ( szImageHlp       ,
                                             &dwVerInfoHandle  ) ;
        if ( 0 == dwVerSize )
        {
            return ( FALSE ) ;
        }

        // Got the version size, now get the version info.
        LPVOID lpData = (LPVOID)new TCHAR [ dwVerSize ] ;
        if ( FALSE == GetFileVersionInfo ( szImageHlp       ,
                                           dwVerInfoHandle  ,
                                           dwVerSize        ,
                                           lpData            ) )
        {
            delete [] lpData ;
            return ( FALSE ) ;
        }

        VS_FIXEDFILEINFO * lpVerInfo ;
        UINT uiLen ;
        BOOL bRet = VerQueryValue ( lpData              ,
                                    _T ( "\\" )         ,
                                    (LPVOID*)&lpVerInfo ,
                                    &uiLen               ) ;
        if ( TRUE == bRet )
        {
            dwMS = lpVerInfo->dwFileVersionMS ;
            dwLS = lpVerInfo->dwFileVersionLS ;
        }

        delete [] lpData ;

        return ( bRet ) ;
    }

/*----------------------------------------------------------------------
                   Public Initialization and Cleanup
----------------------------------------------------------------------*/
public      :

    BOOL SymInitialize ( IN HANDLE   hProcess       ,
                         IN LPSTR    UserSearchPath ,
                         IN BOOL     fInvadeProcess  )
    {
        m_hProcess = hProcess ;
        return ( ::SymInitialize ( hProcess       ,
                                   UserSearchPath ,
                                   fInvadeProcess  ) ) ;
    }

    BOOL SymCleanup ( void )
    {
        return ( ::SymCleanup ( m_hProcess ) ) ;
    }

/*----------------------------------------------------------------------
                       Public Module Manipulation
----------------------------------------------------------------------*/
public      :

    BOOL SymEnumerateModules ( IN PSYM_ENUMMODULES_CALLBACK
                                                    EnumModulesCallback,
                               IN PVOID             UserContext )
    {
        return ( ::SymEnumerateModules ( m_hProcess           ,
                                         EnumModulesCallback  ,
                                         UserContext           ) ) ;
    }

    BOOL SymLoadModule ( IN  HANDLE hFile       ,
                         IN  PSTR   ImageName   ,
                         IN  PSTR   ModuleName  ,
                         IN  DWORD  BaseOfDll   ,
                         IN  DWORD  SizeOfDll    )
    {
        return ( ::SymLoadModule ( m_hProcess   ,
                                   hFile        ,
                                   ImageName    ,
                                   ModuleName   ,
                                   BaseOfDll    ,
                                   SizeOfDll     ) ) ;
    }

    BOOL EnumerateLoadedModules ( IN PENUMLOADED_MODULES_CALLBACK
                                              EnumLoadedModulesCallback,
                                  IN PVOID         UserContext       )
    {
        return ( ::EnumerateLoadedModules ( m_hProcess                ,
                                            EnumLoadedModulesCallback ,
                                            UserContext              ));
    }

    BOOL SymUnloadModule ( IN  DWORD BaseOfDll )
    {
        return ( ::SymUnloadModule ( m_hProcess , BaseOfDll ) ) ;
    }

    BOOL SymGetModuleInfo ( IN  DWORD            dwAddr     ,
                            OUT PIMAGEHLP_MODULE ModuleInfo  )
    {
        return ( ::SymGetModuleInfo ( m_hProcess    ,
                                      dwAddr        ,
                                      ModuleInfo     ) ) ;
    }

    DWORD SymGetModuleBase ( IN DWORD dwAddr )
    {
        return ( ::SymGetModuleBase ( m_hProcess , dwAddr ) ) ;
    }

/*----------------------------------------------------------------------
                       Public Symbol Manipulation
----------------------------------------------------------------------*/
public      :

    BOOL SymEnumerateSymbols (IN DWORD                        BaseOfDll,
                              IN PSYM_ENUMSYMBOLS_CALLBACK
                                                    EnumSymbolsCallback,
                              IN PVOID                     UserContext )
    {
        return ( ::SymEnumerateSymbols ( m_hProcess          ,
                                         BaseOfDll           ,
                                         EnumSymbolsCallback ,
                                         UserContext          ) ) ;
    }

    BOOL SymGetSymFromAddr ( IN  DWORD               dwAddr          ,
                             OUT PDWORD              pdwDisplacement ,
                             OUT PIMAGEHLP_SYMBOL    Symbol           )
    {
        return ( ::SymGetSymFromAddr ( m_hProcess       ,
                                       dwAddr           ,
                                       pdwDisplacement  ,
                                       Symbol            ) ) ;
    }

    BOOL SymGetSymFromName ( IN  LPSTR            Name   ,
                             OUT PIMAGEHLP_SYMBOL Symbol  )
    {
        return ( ::SymGetSymFromName ( m_hProcess ,
                                       Name       ,
                                       Symbol      ) ) ;
    }

    BOOL SymGetSymNext ( IN OUT PIMAGEHLP_SYMBOL Symbol )
    {
        return ( ::SymGetSymNext ( m_hProcess , Symbol ) ) ;
    }

    BOOL SymGetSymPrev ( IN OUT PIMAGEHLP_SYMBOL Symbol )
    {
        return ( :: SymGetSymPrev ( m_hProcess , Symbol ) ) ;
    }

/*----------------------------------------------------------------------
                    Public Source Line Manipulation
----------------------------------------------------------------------*/
public      :

    BOOL SymGetLineFromAddr ( IN  DWORD          dwAddr          ,
                              OUT PDWORD         pdwDisplacement ,
                              OUT PIMAGEHLP_LINE Line             )
    {
        // Holds the function pointer.
        PFNSYMGETLINEFROMADDR pfnSGLFA ;

#ifdef SYMENG_EXTRAWORK
        if ( NULL == m_pfnSymGetLineFromAddr )
        {
            return ( FALSE ) ;
        }
        else
        {
            pfnSGLFA = m_pfnSymGetLineFromAddr ;
        }
#else
        // Just grab it directly.
        pfnSGLFA = ::SymGetLineFromAddr ;
#endif  // SYMENG_EXTRAWORK

#ifdef DO_NOT_WORK_AROUND_SRCLINE_BUG
        // Just return whatever the main function returned.
        return ( pfnSGLFA ( m_hProcess      ,
                            dwAddr          ,
                            pdwDisplacement ,
                            Line             ) ) ;

#else
        // The problem is that the symbol engine only finds those source
        //  line addresses (after the first lookup) that fall exactly on
        //  a zero displacement.  I will walk backwards 100 bytes to
        //  find the line and return the proper displacement.
        DWORD dwTempDis = 0 ;
        while ( FALSE == pfnSGLFA ( m_hProcess          ,
                                    dwAddr - dwTempDis  ,
                                    pdwDisplacement     ,
                                    Line                 ) )
        {
            dwTempDis += 1 ;
            if ( 100 == dwTempDis )
            {
                return ( FALSE ) ;
            }
        }
        // It was found and the source line information is correct so
        //  change the displacement if it was looked up multiple times.
        if ( 0 != dwTempDis )
        {
            *pdwDisplacement = dwTempDis ;
        }
        return ( TRUE ) ;
#endif // DO_NOT_WORK_AROUND_SRCLINE_BUG
    }

    BOOL SymGetLineFromName ( IN     LPSTR          ModuleName      ,
                              IN     LPSTR          FileName        ,
                              IN     DWORD          dwLineNumber    ,
                              OUT    PLONG          plDisplacement  ,
                              IN OUT PIMAGEHLP_LINE Line             )
    {
#ifdef SYMENG_EXTRAWORK
        if ( NULL == m_pfnSymGetLineFromName )
        {
            return ( FALSE ) ;
        }
        return ( m_pfnSymGetLineFromName ( m_hProcess       ,
                                           ModuleName       ,
                                           FileName         ,
                                           dwLineNumber     ,
                                           plDisplacement   ,
                                           Line              ) ) ;
#else
        return ( ::SymGetLineFromName ( m_hProcess       ,
                                        ModuleName       ,
                                        FileName         ,
                                        dwLineNumber     ,
                                        plDisplacement   ,
                                        Line              ) ) ;
#endif  // SYMENG_EXTRAWORK
    }

    BOOL SymGetLineNext ( IN OUT PIMAGEHLP_LINE Line )
    {
#ifdef SYMENG_EXTRAWORK
        if ( NULL == m_pfnSymGetLineNext )
        {
            return ( FALSE ) ;
        }
        return ( m_pfnSymGetLineNext ( m_hProcess , Line ) ) ;
#else
        return ( ::SymGetLineNext ( m_hProcess , Line ) ) ;
#endif  // SYMENG_EXTRAWORK
    }

    BOOL SymGetLinePrev ( IN OUT PIMAGEHLP_LINE Line )
    {
#ifdef SYMENG_EXTRAWORK
        if ( NULL == m_pfnSymGetLinePrev )
        {
            return ( FALSE ) ;
        }
        return ( m_pfnSymGetLinePrev ( m_hProcess , Line ) ) ;
#else
        return ( ::SymGetLinePrev ( m_hProcess , Line ) ) ;
#endif  // SYMENG_EXTRAWORK
    }

    // What is this?
    BOOL SymMatchFileName ( IN  LPSTR   FileName        ,
                            IN  LPSTR   Match           ,
                            OUT LPSTR * FileNameStop    ,
                            OUT LPSTR * MatchStop        )
    {
#ifdef SYMENG_EXTRAWORK
        if ( NULL == m_pfnSymMatchFileName )
        {
            return ( FALSE ) ;
        }
        return ( m_pfnSymMatchFileName ( FileName       ,
                                         Match          ,
                                         FileNameStop   ,
                                         MatchStop       ) ) ;
#else
        return ( ::SymMatchFileName ( FileName       ,
                                      Match          ,
                                      FileNameStop   ,
                                      MatchStop       ) ) ;
#endif  // SYMENG_EXTRAWORK
    }

/*----------------------------------------------------------------------
                          Public Misc Members
----------------------------------------------------------------------*/
public      :

    LPVOID SymFunctionTableAccess ( DWORD AddrBase )
    {
        return ( :: SymFunctionTableAccess ( m_hProcess , AddrBase ) ) ;
    }

    BOOL SymGetSearchPath ( OUT LPSTR SearchPath        ,
                            IN  DWORD SearchPathLength   )
    {
        return ( :: SymGetSearchPath ( m_hProcess       ,
                                       SearchPath       ,
                                       SearchPathLength  ) ) ;
    }

    BOOL SymSetSearchPath ( IN LPSTR SearchPath )
    {
        return ( :: SymSetSearchPath ( m_hProcess , SearchPath ) ) ;
    }

    BOOL SymRegisterCallback ( IN PSYMBOL_REGISTERED_CALLBACK
                                                       CallbackFunction,
                               IN PVOID                UserContext    )
    {
        return ( ::SymRegisterCallback ( m_hProcess         ,
                                         CallbackFunction   ,
                                         UserContext         ) ) ;
    }


/*----------------------------------------------------------------------
                         Protected Data Members
----------------------------------------------------------------------*/
protected   :
    // The unique value that will be used for this instance of the
    //  symbol engine.  Note that this does not have to be an actual
    //  process value, just a unique value.
    HANDLE      m_hProcess      ;

#ifdef SYMENG_EXTRAWORK
    // The function pointers to the new symbol engine source and line
    //  functions.
    PFNSYMGETLINEFROMADDR   m_pfnSymGetLineFromAddr ;
    PFNSYMGETLINEFROMNAME   m_pfnSymGetLineFromName ;
    PFNSYMGETLINENEXT       m_pfnSymGetLineNext     ;
    PFNSYMGETLINEPREV       m_pfnSymGetLinePrev     ;
    PFNSYMMATCHFILENAME     m_pfnSymMatchFileName   ;
#endif  // SYMENG_EXTRAWORK

} ;

#endif  // __cplusplus
/*//////////////////////////////////////////////////////////////////////
                                  END
                         C++ Only Declarations
//////////////////////////////////////////////////////////////////////*/

#endif  // _BUGSLAYERUTIL_H


