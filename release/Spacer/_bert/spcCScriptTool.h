
//  Tool for editing Scripts

#include "zDisk.h"
#include "zSTRING.h"

class spcCScriptTool {
private:
	zFILE* script;
	zSTRING scriptBuffer;
	int lineCount;
	int lineNum;

public:
	spcCScriptTool	();
	spcCScriptTool	( const zSTRING & fileName );
	~spcCScriptTool	();

	zSTRING	ChangeLineGet	(int lineN);
	zBOOL	ChangeLineGoto	( zSTRING & line );
	zBOOL	ChangeLinePut	( zSTRING & line );

};