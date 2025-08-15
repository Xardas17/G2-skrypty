

// tool for editing scripts


#include "zengine.h"

#include "spcCScriptTool.h"

spcCScriptTool :: spcCScriptTool()
	: scriptBuffer(), lineCount(0), lineNum(0) 
{
	script = zfactory->CreateZFile("");
}

spcCScriptTool :: spcCScriptTool( const zSTRING & fileName )
: scriptBuffer(), lineCount(0), lineNum(0) 
{
	script = zfactory->CreateZFile(fileName);
	if (script->Exists())
	{
		script->Open();
		zSTRING buf;
		while (!script->Eof())
		{
			lineCount++;
			script->Read(buf);
			if (buf.IsEmpty()) buf = zSTRING(" ");
			scriptBuffer += buf+zSTRING("\n");
		}
		lineNum = lineCount;
		lineCount = 1;
		script->Close();
		script->Create();
	}
}

spcCScriptTool :: ~spcCScriptTool()
{
	if (script) { delete script;script=0; }
	while(lineNum>lineCount)
	{
		script->Write(scriptBuffer.PickWord(lineCount,"\n","\n")+zSTRING("\n"));
		lineCount++;
	}
	script->Write(scriptBuffer.PickWord(lineCount,"\n","\n")+zSTRING("\n"));
	script->Close();
}

zSTRING spcCScriptTool :: ChangeLineGet(int lineN)
{
	if (lineNum==0 || lineNum<lineN) return zSTRING();

	while(lineN>lineCount)
	{
		script->Write(scriptBuffer.PickWord(lineCount,"\n","\n")+zSTRING("\n"));
		lineCount++;
	}
	return scriptBuffer.PickWord(lineN,"\n","\n");
}

zBOOL spcCScriptTool :: ChangeLineGoto( zSTRING & line )
{
	if (lineNum==0) return FALSE;
	zSTRING thisLine = scriptBuffer.PickWord(lineCount,"\n","\n");
	while(thisLine!=line)
	{
		script->Write(thisLine+zSTRING("\n"));
		lineCount++;
		thisLine = scriptBuffer.PickWord(lineCount,"\n","\n");
	}
	return TRUE;
}

zBOOL spcCScriptTool :: ChangeLinePut( zSTRING & line )
{
	if (lineNum==0) return FALSE;
	
	script->Write(line+zSTRING("\n"));
	lineCount++;
	
	return TRUE;
}