unit VdfsDef;

{$ALIGN ON}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface

uses
  Windows;

type
  PVdfsComment = ^TVdfsComment;
  TVdfsComment = array [0..$FF] of Char;

const
  VdfsFillByte: Char = #26;

type
  PVdfsVersion = ^TVdfsVersion;
  TVdfsVersion = array [0..$0F] of Char;

const
  VdfsVersionText : TVdfsVersion = 'PSVDSC_V2.00'#13#10#13#10;
  VdfsVersionText2: TVdfsVersion = 'PSVDSC_V2.00'#10#13#10#13;

type
  PVdfsParams = ^TVdfsParams;
  TVdfsParams = record
    EntryCount : ULONG;
    FileCount  : ULONG;
    TimeStamp  : ULONG;
    DataSize   : ULONG;
    TableOffset: ULONG;
    EntrySize  : ULONG;
  end;

type
  PVdfsEntry = ^TVdfsEntry;
  TVdfsEntry = record
    Name  : array [0..$3F] of Char;
    Offset: ULONG;
    Size  : ULONG;
    Flags : ULONG;
    Attrib: ULONG;
  end;

const
  // TVdfsEntry.Flags
  VDFS_FILE_DIRECTORY = $80000000;
  VDFS_FILE_LASTENTRY = $40000000;
  // TVdfsEntry.Attrib
  VDFS_FILE_ATTRIBUTE_MASK =
  (
    FILE_ATTRIBUTE_READONLY or
    FILE_ATTRIBUTE_HIDDEN   or
    FILE_ATTRIBUTE_SYSTEM   or
    FILE_ATTRIBUTE_ARCHIVE
  );

type
  PVdfsTable = ^TVdfsTable;
  TVdfsTable = array [0..0] of TVdfsEntry;

type
  PVdfsHeader = ^TVdfsHeader;
  TVdfsHeader = record
    Comment: TVdfsComment;
    Version: TVdfsVersion;
    Params : TVdfsParams;
  end;

implementation

end.
