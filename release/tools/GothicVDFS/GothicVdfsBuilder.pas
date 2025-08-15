unit GothicVdfsBuilder;

interface

uses
  Windows, Messages, CommCtrl, CommDlg,
  VdfsDef, GothicVdfsGlob, GothicVdfsUtil, GothicVdfsViewer;

function SelectModFilename(Dlg: HWND; Filename: PChar): Boolean;

function ReadModScript(Dlg: HWND; Filename: PChar): Boolean;
function SaveModScript(Dlg: HWND; Filename: PChar): Boolean;

function BuildMod(Dlg: HWND; Filename: PChar): Boolean;

implementation

function SelectModFilename(Dlg: HWND; Filename: PChar): Boolean;
begin
  Result := False;
  if (Filename <> nil) or GetSaveFileName(BuilderOfn) then
  begin
    if Filename <> nil then
      lstrcpy(BuilderNameBuff, Filename);
    OptionsWriteString(OptionsBuilderFilename, BuilderNameBuff);
    lstrcpy(BuilderFilename, BuilderNameBuff);
    SendMessage(GetDlgItem(Dlg, IDC_EDITFILE), WM_SETTEXT, 0, LPARAM(@BuilderFilename[0]));
    Result := True;
  end;
end;

function MapAndCutMaskToButtonState(Line: PChar): Integer;
var
  Len: Integer;
begin
  Result := BST_UNCHECKED;
  if (Line <> nil) then
  begin
    Len := lstrlen(Line);
    if (Len > Length(RecursiveSuffix)) and
      (lstrcmpi(PChar(@Line[Len - Length(RecursiveSuffix)]), RecursiveSuffix) = 0) then
    begin
      Line[Len - Length(RecursiveSuffix)] := #0;
      Result := BST_CHECKED;
    end;
  end;
end;

const
  Win9xSucks = 32767;  // ;)

procedure ListViewLoadFromSection(List: HWND; Section: PChar);
var
  Curr: PChar;
  Item: TLVItem;
begin
  SendMessage(List, LVM_DELETEALLITEMS, 0, 0);
  if Section <> nil then
  begin
    ZeroMemory(@Item, SizeOf(TLVItem));
    Item.mask := LVIF_TEXT or LVIF_PARAM;
    Curr := Section;
    while Curr[0] <> #0 do
    begin
      Item.pszText := Curr;
      Curr := PChar(@Curr[lstrlen(Curr) + 1]);
      Item.lParam := MapAndCutMaskToButtonState(Item.pszText);
      SendMessage(List, LVM_INSERTITEM, 0, LPARAM(@Item));
      Inc(Item.iItem);
    end;
  end;
end;

procedure ListViewSaveToSection(List: HWND; Section: PChar; Size: ULONG = Win9xSucks);
var
  Curr: PChar;
  Item: TLVItem;
  Text: array [0..MAX_PATH + Length(RecursiveSuffix)] of Char;
  Len: ULONG;
begin
  if (Section <> nil) and (Size >= 2) then
  begin
    ZeroMemory(Section, Size);
    ZeroMemory(@Item, SizeOf(TLVItem));
    Item.mask := LVIF_TEXT or LVIF_PARAM;
    Item.pszText := Text;
    Item.cchTextMax := MAX_PATH + 1;
    Curr := Section;
    while BOOL(SendMessage(List, LVM_GETITEM, 0, LPARAM(@Item))) do
    begin
      if Item.lParam = BST_CHECKED then
        lstrcat(Text, RecursiveSuffix);
      Len := ULONG(lstrlen(Text));
      if not(ULONG(Section) + Size - 1 >= ULONG(Curr) + Len) then
        Break
      else
      begin
        lstrcpy(Curr, Text);
        Curr[Len] := #13;
        Curr[Len + 1] := #10;
        Curr := PChar(@Curr[Len + 2]);
      end;
      Inc(Item.iItem);
    end;
  end;
end;

function ReadModScript(Dlg: HWND; Filename: PChar): Boolean;
var
  Comment: TVdfsComment;
  Current: PChar;
  StrPos: Integer;
  Buffer: array [0..MAX_PATH] of Char;
  Section: PChar;
begin
  Result := False;
  if (Filename <> nil) or GetOpenFileName(OpenScriptOfn) then
  begin
    if Filename <> nil then
      lstrcpy(ScriptNameBuff, Filename);
    OptionsWriteString(OptionsBuilderScriptname, ScriptNameBuff);
    BuilderHeader.Comment[0] := #0;
    GetPrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyComment, '',
      Comment, SizeOf(TVdfsComment), ScriptNameBuff);
    Current := @Comment[0];
    repeat
      StrPos := Pos(VdfsMgrParamLine, string(Current));
      if StrPos > 0 then
      begin
        Current[StrPos - 1] := #0;
        lstrcat(BuilderHeader.Comment, Current);
        lstrcat(BuilderHeader.Comment, #13#10);
        Inc(Current, StrPos + Length(VdfsMgrParamLine) - 1);
      end;
    until StrPos <= 0;
    lstrcat(BuilderHeader.Comment, Current);
    SetDlgItemText(Dlg, IDC_EDITTEXT, @BuilderHeader.Comment[0]);
    GetPrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyBaseDir, '',
      Buffer, SizeOf(Buffer), ScriptNameBuff);
    lstrcpy(BuilderRoot, Buffer);
    SetDlgItemText(Dlg, IDC_EDITROOT, Buffer);
    GetPrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyVDFName, '',
      Buffer, SizeOf(Buffer), ScriptNameBuff);
    lstrcpy(BuilderFilename, Buffer);
    lstrcpy(BuilderNameBuff, Buffer);
    SetDlgItemText(Dlg, IDC_EDITFILE, Buffer);
    Section := GetMemory(Win9xSucks + 1);
    if Section <> nil then
    begin
      GetPrivateProfileSection(VdfsMgrScriptSegFiles, Section, Win9xSucks, ScriptNameBuff);
      ListViewLoadFromSection(GetDlgItem(Dlg, IDC_LISTFILES), Section);
      GetPrivateProfileSection(VdfsMgrScriptSegExclude, Section, Win9xSucks, ScriptNameBuff);
      ListViewLoadFromSection(GetDlgItem(Dlg, IDC_LISTEX), Section);
      GetPrivateProfileSection(VdfsMgrScriptSegInclude, Section, Win9xSucks, ScriptNameBuff);
      ListViewLoadFromSection(GetDlgItem(Dlg, IDC_LISTIN), Section);
      FreeMemory(Section);
    end;
    Result := True;
  end;
end;

function SaveModScript(Dlg: HWND; Filename: PChar): Boolean;
var
  Comment: TVdfsComment;
  Current: PChar;
  StrPos: Integer;
  Buffer: PChar;
  Section: PChar;
  FileHandle: THandle;
  Written: DWORD;
begin
  Result := False;
  if (Filename <> nil) or GetSaveFileName(SaveScriptOfn) then
  begin
    if Filename <> nil then
      lstrcpy(ScriptNameBuff, Filename);
    OptionsWriteString(OptionsBuilderScriptname, ScriptNameBuff);
    Buffer := GetMemory(4096);
    if Buffer <> nil then
    begin
      Buffer[0] := #0;
      GetDlgItemText(Dlg, IDC_EDITTEXT, Comment, SizeOf(TVdfsComment));
      Current := @Comment[0];
      repeat
        StrPos := Pos(#13#10, string(Current));
        if StrPos > 0 then
        begin
          Current[StrPos - 1] := #0;
          lstrcat(Buffer, Current);
          lstrcat(Buffer, VdfsMgrParamLine);
          Inc(Current, StrPos + 1);
        end;
      until StrPos <= 0;
      lstrcat(Buffer, Current);
      FileHandle := CreateFile(ScriptNameBuff, GENERIC_WRITE, 0, nil,
        CREATE_ALWAYS, 0, 0);
      if FileHandle = INVALID_HANDLE_VALUE then
        MessageBox(Dlg, 'Cannot Open File for Write Access!', nil, 0)
      else
      begin
        // BEGINVDF/Comment
        WriteFile(FileHandle, PChar('[' + VdfsMgrScriptSegGlobal + ']'#13#10 +
          VdfsMgrScriptKeyComment + '=')^, Length(VdfsMgrScriptSegGlobal) +
          Length(VdfsMgrScriptKeyComment) + 5, Written, nil);
        WriteFile(FileHandle, Buffer^, lstrlen(Buffer), Written, nil);
        // BaseDir
        WriteFile(FileHandle, PChar(#13#10 + VdfsMgrScriptKeyBaseDir + '=')^,
          Length(VdfsMgrScriptKeyBaseDir) + 3, Written, nil);
        WriteFile(FileHandle, BuilderRoot, lstrlen(BuilderRoot), Written, nil);
        // VDFName
        WriteFile(FileHandle, PChar(#13#10 + VdfsMgrScriptKeyVDFName + '=')^,
          Length(VdfsMgrScriptKeyVDFName) + 3, Written, nil);
        WriteFile(FileHandle, BuilderFilename, lstrlen(BuilderFilename), Written, nil);
        Section := GetMemory(Win9xSucks + 1);
        if Section <> nil then
        begin
          // FILES
          ListViewSaveToSection(GetDlgItem(Dlg, IDC_LISTFILES), Section);
          WriteFile(FileHandle, PChar(#13#10'[' + VdfsMgrScriptSegFiles + ']'#13#10)^,
            Length(VdfsMgrScriptSegFiles) + 6, Written, nil);
          WriteFile(FileHandle, Section^, lstrlen(Section), Written, nil);
          // EXCLUDE
          ListViewSaveToSection(GetDlgItem(Dlg, IDC_LISTEX), Section);
          WriteFile(FileHandle, PChar('[' + VdfsMgrScriptSegExclude + ']'#13#10)^,
            Length(VdfsMgrScriptSegExclude) + 4, Written, nil);
          WriteFile(FileHandle, Section^, lstrlen(Section), Written, nil);
          // INCLUDE
          ListViewSaveToSection(GetDlgItem(Dlg, IDC_LISTIN), Section);
          WriteFile(FileHandle, PChar('[' + VdfsMgrScriptSegInclude + ']'#13#10)^,
            Length(VdfsMgrScriptSegInclude) + 4, Written, nil);
          WriteFile(FileHandle, Section^, lstrlen(Section), Written, nil);
          // ENDVDF
          WriteFile(FileHandle, PChar('[' + VdfsMgrScriptSegEndTag + ']'#13#10)^,
            Length(VdfsMgrScriptSegEndTag) + 4, Written, nil);
          Result := True;
(** )
      WritePrivateProfileSection(VdfsMgrScriptSegGlobal, '', ScriptNameBuff);
      if not WritePrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyComment,
        Buffer, ScriptNameBuff) then
        MessageBox(Dlg, 'Cannot write to file!', nil, 0)
      else
      begin
        WritePrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyBaseDir,
          BuilderRoot, ScriptNameBuff);
        WritePrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyVDFName,
          BuilderFilename, ScriptNameBuff);
        Section := GetMemory(Win9xSucks + 1);
        if Section <> nil then
        begin
          ListViewSaveToSection(GetDlgItem(Dlg, IDC_LISTFILES), Section);
          WritePrivateProfileSection(VdfsMgrScriptSegFiles, nil, ScriptNameBuff);
          WritePrivateProfileSection(VdfsMgrScriptSegFiles, Section, ScriptNameBuff);
          ListViewSaveToSection(GetDlgItem(Dlg, IDC_LISTEX), Section);
          WritePrivateProfileSection(VdfsMgrScriptSegExclude, nil, ScriptNameBuff);
          WritePrivateProfileSection(VdfsMgrScriptSegExclude, Section, ScriptNameBuff);
          ListViewSaveToSection(GetDlgItem(Dlg, IDC_LISTIN), Section);
          WritePrivateProfileSection(VdfsMgrScriptSegInclude, nil, ScriptNameBuff);
          WritePrivateProfileSection(VdfsMgrScriptSegInclude, Section, ScriptNameBuff);
          Section[0] := #0;
          WritePrivateProfileSection(VdfsMgrScriptSegEndTag, nil, ScriptNameBuff);
          WritePrivateProfileSection(VdfsMgrScriptSegEndTag, Section, ScriptNameBuff);
          Result := True;
          FreeMemory(Section);
        end;
      end;
(**)
          FreeMemory(Section);
        end;
        CloseHandle(FileHandle);
      end;
      FreeMemory(Buffer);
    end;
  end;
end;

{------------------------------------------------------------------------------}
{ parsing }

type
  PSearchMaskEntry = ^TSearchMaskEntry;
  TSearchMaskEntry = record
    MaskBuffer: PChar;
    Recursive: LongBool;
  end;

type
  PSearchMask = ^TSearchMask;
  TSearchMask = record
    Count: ULONG;
    Mask: array [0..0] of TSearchMaskEntry;
  end;

type
  PSearchMasks = ^TSearchMasks;
  TSearchMasks = record
    Files  : PSearchMask;
    Exclude: PSearchMask;
    Include: PSearchMask;
  end;

function SplitMask(Text: PChar): PChar;
var
  Size: Integer;
  Mask: PChar;
  PPos: PChar;
  PEnd: PChar;
  Part: PChar;
begin
  Result := nil;
  if (Text <> nil) and (lstrlen(Text) > 0) then
  begin
    Size := 2 * lstrlen(Text) + 2;
    Part := GetMemory(Size);
    Mask := GetMemory(Size);
    ZeroMemory(Mask, Size);
    Result := Mask;
    PPos := Text;
    while PPos[0] <> #0 do
    begin
      PEnd := PPos;
      while not(PEnd[0] in [#0, '*']) do
        Inc(PEnd);
      lstrcpyn(Part, PPos, ULONG(PEnd) - ULONG(PPos) + 1);
      if lstrlen(Part) > 0 then
        lstrcpy(Mask, Part)
      else if (PPos[0] = '*') then
      begin
        Mask[0] := PPos[0];
        Mask[1] := #0;
        Inc(PEnd);
      end;
      Mask := PChar(@Mask[lstrlen(Mask) + 1]);
      PPos := PEnd;
    end;
    FreeMemory(Part);
  end;
end;

procedure ReadFileMasks(Dlg: HWND; var Masks: TSearchMasks);
var
  LV: HWND;
  Item: TLVItem;
  Text: array [0..MAX_PATH] of Char;
  Count: ULONG;
begin
  LV := GetDlgItem(Dlg, IDC_LISTFILES);
  if LV <> 0 then
  begin
    ZeroMemory(@Item, SizeOf(TLVItem));
    Item.mask := LVIF_TEXT or LVIF_PARAM;
    Item.pszText := @Text[0];
    Item.cchTextMax := SizeOf(Text);
    while BOOL(SendMessage(LV, LVM_GETITEM, 0, LPARAM(@Item))) do
    begin
      Count := 0;
      if Masks.Files <> nil then
        Count := Masks.Files.Count;
      Inc(Count);
      if Masks.Files = nil then
        Masks.Files := GetMemory(Count * SizeOf(TSearchMaskEntry)  + SizeOf(DWORD))
      else
        Masks.Files := ReallocMemory(Masks.Files, Count * SizeOf(TSearchMaskEntry)  + SizeOf(DWORD));
      Masks.Files.Count := Count;
      Masks.Files.Mask[Count - 1].MaskBuffer := SplitMask(Text);
      Masks.Files.Mask[Count - 1].Recursive := (Item.lParam and BST_CHECKED = BST_CHECKED);
      if (Masks.Files.Mask[Count - 1].MaskBuffer = nil) then
        Dec(Masks.Files.Count);
      Inc(Item.iItem);
    end;
  end;
  LV := GetDlgItem(Dlg, IDC_LISTEX);
  if LV <> 0 then
  begin
    ZeroMemory(@Item, SizeOf(TLVItem));
    Item.mask := LVIF_TEXT or LVIF_PARAM;
    Item.pszText := @Text[0];
    Item.cchTextMax := SizeOf(Text);
    while BOOL(SendMessage(LV, LVM_GETITEM, 0, LPARAM(@Item))) do
    begin
      Count := 0;
      if Masks.Exclude <> nil then
        Count := Masks.Exclude.Count;
      Inc(Count);
      if Masks.Exclude = nil then
        Masks.Exclude := GetMemory(Count * SizeOf(TSearchMaskEntry)  + SizeOf(DWORD))
      else
        Masks.Exclude := ReallocMemory(Masks.Exclude, Count * SizeOf(TSearchMaskEntry) + SizeOf(DWORD));
      Masks.Exclude.Count := Count;
      Masks.Exclude.Mask[Count - 1].MaskBuffer := SplitMask(Text);
      Masks.Exclude.Mask[Count - 1].Recursive := (Item.lParam and BST_CHECKED = BST_CHECKED);
      if (Masks.Exclude.Mask[Count - 1].MaskBuffer = nil) then
        Dec(Masks.Exclude.Count);
      Inc(Item.iItem);
    end;
  end;
  LV := GetDlgItem(Dlg, IDC_LISTIN);
  if LV <> 0 then
  begin
    ZeroMemory(@Item, SizeOf(TLVItem));
    Item.mask := LVIF_TEXT or LVIF_PARAM;
    Item.pszText := @Text[0];
    Item.cchTextMax := SizeOf(Text);
    while BOOL(SendMessage(LV, LVM_GETITEM, 0, LPARAM(@Item))) do
    begin
      Count := 0;
      if Masks.Include <> nil then
        Count := Masks.Include.Count;
      Inc(Count);
      if Masks.Include = nil then
        Masks.Include := GetMemory(Count * SizeOf(TSearchMaskEntry)  + SizeOf(DWORD))
      else
        Masks.Include := ReallocMemory(Masks.Include, Count * SizeOf(TSearchMaskEntry)  + SizeOf(DWORD));
      Masks.Include.Count := Count;
      Masks.Include.Mask[Count - 1].MaskBuffer := SplitMask(Text);
      Masks.Include.Mask[Count - 1].Recursive := (Item.lParam and BST_CHECKED = BST_CHECKED);
      if (Masks.Include.Mask[Count - 1].MaskBuffer = nil) then
        Dec(Masks.Include.Count);
      Inc(Item.iItem);
    end;
  end;
end;

procedure FreeFileMasks(var Masks: TSearchMasks);
var
  Loop: ULONG;
begin
  if Masks.Files <> nil then
  begin
    for Loop := 0 to Masks.Files.Count - 1 do
      FreeMemory(Masks.Files.Mask[Loop].MaskBuffer);
    FreeMemory(Masks.Files);
    Masks.Files := nil;
  end;
  if Masks.Exclude <> nil then
  begin
    for Loop := 0 to Masks.Exclude.Count - 1 do
      FreeMemory(Masks.Exclude.Mask[Loop].MaskBuffer);
    FreeMemory(Masks.Exclude);
    Masks.Exclude := nil;
  end;
  if Masks.Include <> nil then
  begin
    for Loop := 0 to Masks.Include.Count - 1 do
      FreeMemory(Masks.Include.Mask[Loop].MaskBuffer);
    FreeMemory(Masks.Include);
    Masks.Include := nil;
  end;
end;

function IsFileInMask(Filename: PChar; const Mask: TSearchMask): Boolean;
var
  Name: array [0..MAX_PATH] of Char;
  NamePos: PChar;
  MaskIdx: Integer;
  MaskPos: PChar;
  JumpOver: Boolean;
  Matched: Boolean;
  NextPos: Integer;
  Slash: Boolean;
  Buffer: array [0..MAX_PATH] of Char;
  Loop: Integer;
begin
  Result := False;
  if Filename <> nil then
  begin
    lstrcpy(Name, Filename);
    CharUpper(Name);
    for MaskIdx := 0 to Mask.Count - 1 do
    begin
      NamePos := @Name[0];
      MaskPos := Mask.Mask[MaskIdx].MaskBuffer;
      Matched := False;
      JumpOver := Mask.Mask[MaskIdx].Recursive;
      while (MaskPos[0] <> #0) do
      begin
        if (MaskPos[0] = '*') then
        begin
          JumpOver := True;
          Matched := True;
          Inc(MaskPos, 2);
        end;
        if (MaskPos[0] <> #0) then
        begin
          CharUpper(MaskPos);
          if JumpOver then
          begin
            NextPos := Pos(MaskPos, NamePos);
            if (NextPos > 0) then
            begin
              if not Mask.Mask[MaskIdx].Recursive then
              begin
                Slash := False;
                for Loop := 0 to NextPos - 2 do
                begin
                  if (NamePos[0] = '\') then
                  begin
                    Slash := True;
                    Break;
                  end;
                  Inc(NamePos);
                end;
                Inc(NamePos, lstrlen(MaskPos));
                if Slash then
                begin
                  Matched := False;
                  Break;
                end;
              end
              else
                Inc(NamePos, lstrlen(MaskPos) + NextPos - 1);
              Matched := True;
            end
            else
            begin
              Matched := False;
              Break;
            end;
            JumpOver := False;
          end
          else
          begin
            lstrcpyn(Buffer, NamePos, lstrlen(MaskPos) + 1);
            if (lstrcmp(Buffer, MaskPos) = 0) then
            begin
              Matched := True;
              Inc(NamePos, lstrlen(MaskPos));
            end;
          end;
          MaskPos := PChar(@MaskPos[lstrlen(MaskPos) + 1]);
        end
        else if not Mask.Mask[MaskIdx].Recursive then
          Matched := (Pos('\', NamePos) = 0);
      end;
      Result := Matched and (MaskPos[0] = #0);
      if Result then
        Break;
    end;
  end;
end;

function IsFileInMasks(Filename: PChar; const Masks: TSearchMasks): Boolean;
begin
  Result := False;
  if Masks.Include <> nil then
    Result := IsFileInMask(Filename, Masks.Include^);
  if (not Result) and (Masks.Files <> nil) then
    if IsFileInMask(Filename, Masks.Files^) then
      if Masks.Exclude <> nil then
        Result := not IsFileInMask(Filename, Masks.Exclude^)
      else
        Result := True;
end;

{------------------------------------------------------------------------------}

const
  VdfsMaxEntryLen = $40;

type
  PFileEntry = ^TFileEntry;
  TFileEntry = record
    Size: ULONG;
    Name: array [0..VdfsMaxEntryLen] of Char;
    Attr: ULONG;
  end;

type
  PFileList = ^TFileList;
  TFileList = array [0..0] of TFileEntry;

type
  PDirList = ^TDirList;
  PDirEntry = ^TDirEntry;
  TDirEntry = record
    Name: array [0..VdfsMaxEntryLen] of Char;
    Attr: ULONG;
    DirCount: ULONG;
    Dirs: PDirList;
    FileCount: ULONG;
    Files: PFileList;
  end;
  TDirList = array [0..0] of TDirEntry;

procedure FreeDirEntry(var List: TDirEntry);
var
  Loop: ULONG;
begin
  if List.Dirs <> nil then
  begin
    for Loop := 1 to List.DirCount do
      FreeDirEntry(List.Dirs[Loop - 1]);
    List.DirCount := 0;
    FreeMemory(List.Dirs);
    List.Dirs := nil;
  end;
  if List.Files <> nil then
  begin
    List.FileCount := 0;
    FreeMemory(List.Files);
    List.Files := nil;
  end;
end;

function _StrComp(Str1, Str2: PChar): Integer; assembler;
asm
        PUSH    EDI
        PUSH    ESI
        MOV     EDI,EDX
        MOV     ESI,EAX
        MOV     ECX,0FFFFFFFFH
        XOR     EAX,EAX
        REPNE   SCASB
        NOT     ECX
        MOV     EDI,EDX
        XOR     EDX,EDX
        REPE    CMPSB
        MOV     AL,[ESI-1]
        MOV     DL,[EDI-1]
        SUB     EAX,EDX
        POP     ESI
        POP     EDI
end;

procedure SortFileList(var List: TDirEntry);
var
  Loop: ULONG;
  Sorted: Boolean;
  TempDir: TDirEntry;
  TempFile: TFileEntry;
begin
  if List.Dirs <> nil then
  begin
    for Loop := 1 to List.DirCount do
      SortFileList(List.Dirs[Loop - 1]);
    repeat
      Sorted := True;
      for Loop := 2 to List.DirCount do
        if _StrComp(List.Dirs[Loop - 2].Name, List.Dirs[Loop - 1].Name) > 0 then
        begin
          Sorted := False;
          TempDir := List.Dirs[Loop - 2];
          List.Dirs[Loop - 2] := List.Dirs[Loop - 1];
          List.Dirs[Loop - 1] := TempDir;
        end;
    until Sorted;
  end;
  if List.Files <> nil then
  begin
    repeat
      Sorted := True;
      for Loop := 2 to List.FileCount do
        if _StrComp(List.Files[Loop - 2].Name, List.Files[Loop - 1].Name) > 0 then
        begin
          Sorted := False;
          TempFile := List.Files[Loop - 2];
          List.Files[Loop - 2] := List.Files[Loop - 1];
          List.Files[Loop - 1] := TempFile;
        end;
    until Sorted;
  end;
end;

function FileListDataSize(const List: TDirEntry; var EntryCount: ULONG): ULONG;
var
  Loop: ULONG;
begin
  Result := 0;
  if List.Dirs <> nil then
  begin
    Inc(EntryCount, List.DirCount);
    for Loop := 1 to List.DirCount do
      Inc(Result, FileListDataSize(List.Dirs[Loop - 1], EntryCount));
  end;
  if List.Files <> nil then
  begin
    Inc(EntryCount, List.FileCount);
    for Loop := 1 to List.FileCount do
      Inc(Result, List.Files[Loop - 1].Size);
  end;
end;

function SearchFiles(Root, Path: PChar; const Masks: TSearchMasks; var List: TDirEntry): ULONG;
var
  Filename: array [0..MAX_PATH] of Char;
  SubPath: array [0..MAX_PATH] of Char;
  FindFile: THandle;
  FindData: TWin32FindData;
  ErrMsg: PChar;
  FileCount: ULONG;
  Loop: ULONG;
  Found: Boolean;
begin
  Result := 0;
  MakeFullPath(Root, Path, '*.*', Filename);
  FindFile := FindFirstFile(Filename, FindData);
  if FindFile <> INVALID_HANDLE_VALUE then
  begin
    repeat
      if (lstrcmp(FindData.cFileName, '.') <> 0) and (lstrcmp(FindData.cFileName, '..') <> 0) then
      begin
        if (FindData.dwFileAttributes and FILE_ATTRIBUTE_DIRECTORY = FILE_ATTRIBUTE_DIRECTORY) then
        begin
          if lstrlen(FindData.cFileName) >= VdfsMaxEntryLen then
          begin
            ErrMsg := GetMemory(4096);
            lstrcpy(ErrMsg, 'Directory name: "');
            lstrcat(ErrMsg, FindData.cFileName);
            lstrcat(ErrMsg, '" is too long! (skipped)');
            MessageBox(0, ErrMsg, nil, 0);
            FreeMemory(ErrMsg);
          end
          else
          begin
            SubPath[0] := #0;
            if Path <> nil then
              lstrcpy(SubPath, Path);
            AppendBackSlash(SubPath);
            lstrcat(SubPath, FindData.cFileName);
            if List.Dirs = nil then
              List.Dirs := GetMemory((List.DirCount + 1) * SizeOf(TDirEntry))
            else
              List.Dirs := ReallocMemory(List.Dirs, (List.DirCount + 1) * SizeOf(TDirEntry));
            if List.Dirs <> nil then
            begin
              ZeroMemory(@List.Dirs[List.DirCount], SizeOf(TDirEntry));
              if BuilderSortLits then
                CharUpper(FindData.cFileName);
              lstrcpy(List.Dirs[List.DirCount].Name, FindData.cFileName);
              List.Dirs[List.DirCount].Attr := (FindData.dwFileAttributes and VDFS_FILE_ATTRIBUTE_MASK);
              FileCount := SearchFiles(Root, SubPath, Masks, List.Dirs[List.DirCount]);
              if FileCount = 0 then
                FreeDirEntry(List.Dirs[List.DirCount])
              else
              begin
                Inc(List.DirCount);
                Inc(Result, FileCount);
              end;
            end;
          end;
        end
        else
        begin
          MakeFullPath(nil, Path, FindData.cFileName, Filename);
          if IsFileInMasks(Filename, Masks) then
          begin
            if lstrlen(FindData.cFileName) >= VdfsMaxEntryLen then
            begin
              ErrMsg := GetMemory(4096);
              lstrcpy(ErrMsg, 'Filename: "');
              lstrcat(ErrMsg, FindData.cFileName);
              lstrcat(ErrMsg, '" is too long! (skipped)');
              MessageBox(0, ErrMsg, nil, 0);
              FreeMemory(ErrMsg);
            end
            else
            begin
              Found := False;
              if (List.Name[0] = #0) and (List.Files <> nil) then
                for Loop := 1 to List.FileCount do
                  if lstrcmpi(List.Files[List.FileCount].Name, FindData.cFileName) = 0 then
                  begin
                    Found := True;
                    Break;
                  end;
              if not Found then
              begin
                if List.Files = nil then
                  List.Files := GetMemory((List.FileCount + 1) * SizeOf(TFileEntry))
                else
                  List.Files := ReallocMemory(List.Files, (List.FileCount  + 1) * SizeOf(TFileEntry));
                if List.Files <> nil then
                begin
                  List.Files[List.FileCount].Size := FindData.nFileSizeLow;
                  if BuilderSortLits then
                    CharUpper(FindData.cFileName);
                  lstrcpy(List.Files[List.FileCount].Name, FindData.cFileName);
                  List.Files[List.FileCount].Attr := (FindData.dwFileAttributes and VDFS_FILE_ATTRIBUTE_MASK);
                  Inc(List.FileCount);
                  Inc(Result);
                end;
              end;
            end;
          end;
        end;
      end;
    until not FindNextFile(FindFile, FindData);
    FindClose(FindFile);
  end;
end;

function AppendDataFromDisk(Dlg: HWND; ModFile: THandle; Root, Path, Name: PChar; Size: ULONG): Boolean;
const
  BlockSize = 4096;
var
  Filename: array [0..MAX_PATH] of Char;
  Block: array [0..BlockSize] of Byte;
  Blocks: ULONG;
  Loop: ULONG;
  DataFile: THandle;
  ToWrite: DWORD;
  Written: DWORD;
begin
  Result := False;
  {*} SetStatusText(PChar('Processing: ' + string(Name) + '...'), modeBuilder);
  MakeFullPath(Root, Path, Name, Filename);
  DataFile := CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ, nil,
     OPEN_EXISTING, 0, 0);
  if DataFile = INVALID_HANDLE_VALUE then
    MessageBox(Dlg, 'Cannot open/read file!', Filename, 0)
  else
  begin
    Blocks := Size div BlockSize;
    Loop := 0;
    repeat
      if Loop < Blocks then
        ToWrite := BlockSize
      else
        ToWrite := Size mod BlockSize;
      if ToWrite > 0 then
      begin
        if not ReadFile(DataFile, Block, ToWrite, Written, nil) or (Written <> ToWrite) then
        begin
          MessageBox(Dlg, 'Cannot read data from data file!', Filename, 0);
          Break;
        end;
        if not WriteFile(ModFile, Block, ToWrite, Written, nil) or (Written <> ToWrite) then
        begin
          MessageBox(Dlg, 'Cannot write data to volume!', Filename, 0);
          Break;
        end;
        IncProgress(Dlg, modeBuilder, ToWrite);
      end;
      Inc(Loop);
      ProcessMessages(Dlg);
    until Loop > Blocks;
    Result := True;
    CloseHandle(DataFile);
  end;
end;

function ReadFilesFromList(Dlg: HWND; ModFile: THandle; const List: TDirEntry; Table: PVdfsTable;
  Root, Path: PChar; var Index: ULONG; var DataPos: ULONG): Boolean;
var
  Idx: ULONG;
  Loop: ULONG;
  SubPath: array [0..MAX_PATH] of Char;
begin
  Result := True;
  Idx := Index;
  Inc(Index, List.DirCount + List.FileCount);
  for Loop := 1 to List.DirCount do
  begin
    FillChar(Table[Idx], VdfsMaxEntryLen, ' ');
    lstrcpy(Table[Idx].Name, List.Dirs[Loop - 1].Name);
    if BuilderAllUpper then
      CharUpper(Table[Idx].Name);
    Table[Idx].Name[lstrlen(Table[Idx].Name)] := ' ';
    Table[Idx].Offset := Index;
    Table[Idx].Size := 0;
    Table[Idx].Flags := VDFS_FILE_DIRECTORY;
    if (List.FileCount = 0) and (Loop = List.DirCount) then
      Table[Idx].Flags := Table[Idx].Flags or VDFS_FILE_LASTENTRY;
    Table[Idx].Attrib := List.Dirs[Loop - 1].Attr;
    SubPath[0] := #0;
    if Path <> nil then
      lstrcpy(SubPath, Path);
    AppendBackSlash(SubPath);
    lstrcat(SubPath, List.Dirs[Loop - 1].Name);
    if not ReadFilesFromList(Dlg, ModFile, List.Dirs[Loop - 1], Table, Root, SubPath, Index,
      DataPos) then
    begin
      Result := False;
      Break;
    end;
    Inc(Idx);
  end;
  for Loop := 1 to List.FileCount do
  begin
    FillChar(Table[Idx], VdfsMaxEntryLen, ' ');
    lstrcpy(Table[Idx].Name, List.Files[Loop - 1].Name);
    if BuilderAllUpper then
      CharUpper(Table[Idx].Name);
    Table[Idx].Name[lstrlen(Table[Idx].Name)] := ' ';
    Table[Idx].Offset := DataPos;
    Table[Idx].Size := List.Files[Loop - 1].Size;
    Table[Idx].Flags := 0;
    if (Loop = List.FileCount) then
      Table[Idx].Flags := Table[Idx].Flags or VDFS_FILE_LASTENTRY;
    Table[Idx].Attrib := List.Files[Loop - 1].Attr;
    if not AppendDataFromDisk(Dlg, ModFile, Root, Path,
      List.Files[Loop - 1].Name, List.Files[Loop - 1].Size) then
    begin
      Result := False;
      Exit;
    end;
    Inc(DataPos, Table[Idx].Size);
    Inc(Idx);
  end;
end;

{------------------------------------------------------------------------------}

function InfoBuildInitDialog(Dlg: HWND; Text: PChar): BOOL; forward;
{$IFDEF USECOLORS}
function InfoBuildCtlColor(Dlg: HWND; Msg: UINT; WParam: HDC): HBRUSH; forward;
{$ENDIF}
function InfoBuildCommand(Dlg: HWND; NotifyCode, ID: Word; Ctl: HWND): BOOL; forward;

function InfoBuildDlgProc(Dlg: HWND; Msg: UINT; WParam: WPARAM; LParam: LPARAM): BOOL; stdcall;
begin
  case Msg of
    WM_INITDIALOG:
      begin
        Result := InfoBuildInitDialog(Dlg, PChar(LParam));
        if ViewerWorkInProgress then
          EnableDlgItem(Dlg, IDYES, False);
      end;
    WM_CLOSE:
      Result := EndDialog(Dlg, 0);
{$IFDEF USECOLORS}
    WM_CTLCOLORMSGBOX..WM_CTLCOLORSTATIC:
      Result := BOOL(InfoBuildCtlColor(Dlg, Msg, HDC(WParam)));
{$ENDIF}
    WM_COMMAND:
      Result := InfoBuildCommand(Dlg, HiWord(WParam), LoWord(WParam), HWND(LParam));
  else
    Result := False;
  end;
end;

function InfoBuildInitDialog(Dlg: HWND; Text: PChar): BOOL;
begin
  Result := False;
  SetFocus(GetDlgItem(Dlg, IDOK));
  SendMessage(Dlg, WM_SETICON, ICON_BIG, LPARAM(LoadIcon(HInstance, IDI_MAINICON)));
  SetRicheditProp(Dlg, IDC_EDITBINFO, True);
  SetDlgItemText(Dlg, IDC_EDITBINFO, Text);
end;

{$IFDEF USECOLORS}
function InfoBuildCtlColor(Dlg: HWND; Msg: UINT; WParam: HDC): HBRUSH;
begin
  SetTextColor(WParam, DialogTextColor);
  SetBkColor(WParam, DialogBackColor);
  if DialogBrush = 0 then
    DialogBrush := CreateBrushIndirect(DialogLogBrush);
  Result := DialogBrush;
end;
{$ENDIF}

function InfoBuildCommand(Dlg: HWND; NotifyCode, ID: Word; Ctl: HWND): BOOL;
begin
  Result := BOOL(0);
  if (Ctl <> 0) and (NotifyCode = BN_CLICKED) then
    EndDialog(Dlg, ID)
  else
    Result := BOOL(1);
end;

{------------------------------------------------------------------------------}

function BuildMod(Dlg: HWND; Filename: PChar): Boolean;
const
  Weekdays: array [0..6] of PChar =
    ('Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat');
  Month: array [1..12] of PChar =
    ('Jan', 'Feb', 'Mar' ,'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec');
var
  ModFile: THandle;
  Header: TVdfsHeader;
  SystemTime: TSystemTime;
  FileTime: TFileTime;
  TempTime: TFileTime;
  FatDate: Word;
  FatTime: Word;
  Comment: array [0..4096] of Char;
  DatePos: Integer;
  CharPos: PChar;
  DateVal: array [0..6] of ULONG;
  FileMasks: TSearchMasks;
  FileList: TDirEntry;
  Written: ULONG;
  Table: PVdfsTable;
  TableSize: ULONG;
  Index: ULONG;
  DataPos: ULONG;
  BuildInfo: PChar;
begin
  Result := False;
  if Filename <> nil then
  begin
    lstrcpy(BuilderFilename, Filename);
    lstrcpy(BuilderNameBuff, Filename);
    SetDlgItemText(Dlg, IDC_EDITFILE, Filename);
  end;
  if (lstrlen(BuilderFilename) = 0) and not SelectModFilename(Dlg, nil) then
    Exit;
  // reset Viewer if the output is opened
  if lstrcmpi(ViewerFilename, BuilderFilename) = 0 then
    ResetViewer(Dlg);
  {*} SetStatusText('Building volume header...', modeBuilder);
  ZeroMemory(@Header, SizeOf(TVdfsHeader));
  Header.Version := VdfsVersionText2;
  Header.Params.TableOffset := SizeOf(TVdfsHeader);
  Header.Params.EntrySize := SizeOf(TVdfsEntry);
  ReadTime(Dlg, SystemTime);
  if SystemTimeToFileTime(SystemTime, FileTime) then
  begin
    if IsDlgButtonChecked(Dlg, IDC_CHECKUTC) = BST_UNCHECKED then
    begin
      if LocalFileTimeToFileTime(FileTime, TempTime) then
        FileTime := TempTime;
    end;
    FileTimeToSystemTime(FileTime, SystemTime);
    if FileTimeToDosDateTime(FileTime, FatDate, FatTime) then
      Header.Params.TimeStamp := FatDate shl 16 or FatTime;
  end;
  if Header.Params.TimeStamp = 0 then
    MessageBox(Dlg, 'Invalid timestamp!', nil, 0)
  else
  begin
    DateVal[0] := ULONG(Weekdays[SystemTime.wDayOfWeek]);
    DateVal[1] := SystemTime.wDay;
    DateVal[2] := ULONG(Month[SystemTime.wMonth]);
    DateVal[3] := SystemTime.wYear;
    DateVal[4] := SystemTime.wHour;
    DateVal[5] := SystemTime.wMinute;
    DateVal[6] := SystemTime.wSecond;
    CharPos := @Header.Comment[0];
    GetDlgItemText(Dlg, IDC_EDITTEXT, CharPos, SizeOf(TVdfsComment));
    Comment[0] := #0;
    DatePos := Pos(VdfsMgrParamDate, CharPos);
    while DatePos > 0 do
    begin
      lstrcpyn(Comment, CharPos, DatePos);
      wvsprintf(@Comment[lstrlen(Comment)], '%s, %2.2d %s %4.4d %2.2d:%2.2d:%2.2d GMT', PChar(@DateVal[0]));
      Inc(CharPos, DatePos + Length(VdfsMgrParamDate) - 1);
      DatePos := Pos(VdfsMgrParamDate, CharPos);
    end;
    lstrcat(Comment, CharPos);
    lstrcpyn(Header.Comment, Comment, SizeOf(TVdfsComment));
    CharPos := @Header.Comment[lstrlen(Header.Comment)];
    while (CharPos[0] = #0) and
      (ULONG(CharPos) <= ULONG(@Header.Comment[High(TVdfsComment)])) do
    begin
      CharPos[0] := VdfsFillByte;
      Inc(CharPos);
    end;
    {*} SetStatusText('Searching for files in root diretory...', modeBuilder);
    ZeroMemory(@FileMasks, SizeOf(TSearchMasks));
    ProcessMessages(Dlg);
    ReadFileMasks(Dlg, FileMasks);
    ZeroMemory(@FileList, SizeOf(TDirEntry));
    Header.Params.FileCount := SearchFiles(BuilderRoot, nil, FileMasks, FileList);
    if Header.Params.FileCount = 0 then
      MessageBox(Dlg, 'No matching files found.', nil, 0)
    else
    begin
      if BuilderSortLits then
      begin
        {*} SetStatusText('Sorting directory/file entries...', modeBuilder);
        SortFileList(FileList);
      end;
      Header.Params.DataSize := FileListDataSize(FileList, Header.Params.EntryCount);
      InitProgress(Dlg, Header.Params.DataSize, modeBuilder);
      {*} SetStatusText('Preparing volume entry table...', modeBuilder);
      TableSize := Header.Params.EntryCount * SizeOf(TVdfsEntry);
      Table := GetMemory(TableSize);
      if Table = nil then
        MessageBox(Dlg, 'Not enough memory for file table!', nil, 0)
      else
      begin
        ZeroMemory(Table, TableSize);
        {*} SetStatusText('Creating VDFS file...', modeBuilder);
        ModFile := CreateFile(BuilderFilename, GENERIC_WRITE, FILE_SHARE_READ, nil,
          CREATE_ALWAYS, 0, 0);
        if ModFile = INVALID_HANDLE_VALUE then
          MessageBox(Dlg, 'Cannot create/open file for write access!', nil, 0)
        else
        begin
          {*} SetStatusText('Writing volume header...', modeBuilder);
          if not (WriteFile(ModFile, Header, SizeOf(TVdfsHeader), Written, nil) and
            (Written = SizeOf(TVdfsHeader))) then
            MessageBox(Dlg, 'Cannot write volume header to file!', nil, 0)
          else
          begin
            {*} SetStatusText('Writing volume entry table (init)...', modeBuilder);
            if not (WriteFile(ModFile, Table^, TableSize, Written, nil) and
                  (Written = TableSize)) then
              MessageBox(Dlg, 'Cannot write initial file table!', nil, 0)
            else
            begin
              {*} SetStatusText('Adding entries to volume...', modeBuilder);
              Index := 0;
              DataPos := Header.Params.TableOffset + TableSize;
              if not ReadFilesFromList(Dlg, ModFile, FileList, Table, BuilderRoot, nil, Index, DataPos) then
                // MessageBox(Dlg, 'Error on building/writing volume!', nil, 0)
              else
              begin
                {*} SetStatusText('Writing volume entry table (finish)...', modeBuilder);
                if SetFilePointer(ModFile, Header.Params.TableOffset, nil, FILE_BEGIN) = 0 then
                  MessageBox(Dlg, 'Cannot set file pointer for file table fixup!', nil, 0)
                else if not (WriteFile(ModFile, Table^, TableSize, Written, nil) and
                  (Written = TableSize)) then
                  MessageBox(Dlg, 'Cannot fixup file table!', nil, 0)
                else
                  Result := True;
              end;
            end;
          end;
          {*} SetStatusText('Writing volume entry table (finish)...', modeBuilder);
          CloseHandle(ModFile);
        end;
      end;
      InitProgress(Dlg, Header.Params.DataSize, modeBuilder);
    end;
    FreeFileMasks(FileMasks);
  end;
  {*} SetStatusText(nil, modeBuilder);
  if Result and (Filename = nil) then
  begin
    BuildInfo := GetMemory(4096);
    lstrcpy(BuildInfo, 'Filename: ');
    lstrcat(BuildInfo, BuilderFilename);
    lstrcat(BuildInfo, #13#10'Directories: ');
    IntToStrGrp(Header.Params.EntryCount - Header.Params.FileCount,
      PChar(@BuildInfo[lstrlen(BuildInfo)]));
    lstrcat(BuildInfo, #13#10'Files: ');
    IntToStrGrp(Header.Params.FileCount,
      PChar(@BuildInfo[lstrlen(BuildInfo)]));
    lstrcat(BuildInfo, #13#10'Size: ');
    IntToStrGrp(Header.Params.DataSize,
      PChar(@BuildInfo[lstrlen(BuildInfo)]));
    lstrcat(BuildInfo, #13#10#13#10);
    Header.Version[0] := #0;
    lstrcat(BuildInfo, Header.Comment);
    CharPos := PChar(@BuildInfo[lstrlen(BuildInfo) - 1]);
    while CharPos[0] = VdfsFillByte do
    begin
      CharPos[0] := #0;
      Dec(CharPos);
    end;
    if DialogBoxParam(HInstance, IDD_INFOBUILD, Dlg, @InfoBuildDlgProc, LPARAM(BuildInfo)) = IDYES then
    begin
      SwitchMode(Dlg, modeViewer);
      OpenVdfs(Dlg, BuilderFilename);
    end;
    FreeMemory(BuildInfo);
  end;
end;

end.
