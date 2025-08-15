unit ZTEX;

{*******************************************************}
{                                                       }
{       ZenGin TEXture (ZTEX) structures and constants  }
{                                                       }
{       Copyright (c) 2001, Nico Bendlin                }
{                                                       }
{*******************************************************}

{$ALIGN ON}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface

uses
  Windows;

type
  PZTEXFileHeader = ^TZTEXFileHeader;
  TZTEXFileHeader = record
    Magic   : ULONG;  // ZenGinTexMagic
    Spare   : ULONG;  // 0
    Format  : ULONG;  // ZTEX_TF_*
    Width   : ULONG;  // Width of image (pixel)
    Height  : ULONG;  // Height of image (pixel)
    Maps    : ULONG;  // Count of maps in texture
    Width2  : ULONG;  // Width2 (special meaning, for inst: source width)
    Height2 : ULONG;  // Height2 (special meaning, for inst: source Height)
    KeyColor: ULONG;  // (usage unknown, could be 'transparent' color)
  end;

const
  ZenGinTexMagic = ULONG($5845545A);  // 'ZTEX'

const
  ZTEX_TF_UNKNOWN = 0;   // for error cases only
  ZTEX_TF_RGB4444 = 6;
  ZTEX_TF_RGB1555 = 7;   // not used (only an assertion)
  ZTEX_TF_RGB565  = 8;
  ZTEX_TF_RGB8888 = 9;   // not used (only an assertion)
  ZTEX_TF_DXT1    = 10;
  ZTEX_TF_DXT1A   = 11;  // not used (only an assertion)
  ZTEX_TF_DXT3    = 12;
  ZTEX_TF_DXT5    = 13;  // not used (only an assertion)

implementation

end.
 