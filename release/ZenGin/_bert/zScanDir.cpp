
#include "zcore.h"
#include <direct.h>

#include "Zdisk.h"
#include "zscandir.h"


zCScanDir dirScanner;


////////////////////////////////////////////////////////////
// DirScanner-Callback
////////////////////////////////////////////////////////////


zCScanDirFileHandler::zCScanDirFileHandler()
{
	name = "";
};

zCScanDirFileHandler::~zCScanDirFileHandler()
{
	ClearMessages();
	extList.DeleteList();
};

zBOOL zCScanDirFileHandler::CanHandleFile(zSTRING& filename)
{	
	ClearMessages();

	zFILE_FILE file(filename);

	zBOOL canHandle=FALSE;
	int i=0;
	while (!canHandle && i<extList.GetNumInList())
	{
		if (file.GetExt() == extList.GetSafe(i)) return TRUE;
		i++;
	};

	return canHandle;
};

int	zCScanDirFileHandler::GetNumMessages()
{
	return msgList.GetNumInList();	
}

zSTRING	zCScanDirFileHandler::GetMessage(int nr)
{
	if (nr<0 || nr>=GetNumMessages()) return "";
	return msgList.GetSafe(nr);
};

void zCScanDirFileHandler::RegisterFileType(zSTRING extension)
{
	extension.Upper();
	extList.Insert(extension);
};

void zCScanDirFileHandler::AddMessage(zSTRING msg)
{
	msgList.Insert(msg);
};

void zCScanDirFileHandler::ClearMessages()
{	
	msgList.DeleteList();
}

void zCScanDirFileHandler::SetName(const zSTRING& _name)
{
	name = _name;
};

zSTRING& zCScanDirFileHandler::GetName()
{
	return name;
};


////////////////////////////////////////////////////////////
// DirScanner
////////////////////////////////////////////////////////////

zCScanDir::zCScanDir()
{
};

zCScanDir::~zCScanDir()
{
	cbList.DeleteList();
};

void zCScanDir::RegisterFileHandler(zCScanDirFileHandler* callback, const zSTRING& name)
{
	if (!name.IsEmpty()) callback->SetName(name);
	if (!cbList.IsInList(callback)) cbList.Insert(callback);	
};

static _finddata_t fileinfo;
static char buffer[MAX_PATH];

void zCScanDir::ScanX()
{	
	long find_handle = _findfirst( "*.*", &fileinfo );
	if (find_handle == -1L) return;
	
	do
	{
		// Verzeichnis wechseln
		if ((fileinfo.attrib & _A_SUBDIR) == _A_SUBDIR)
		{	
			if ((fileinfo.name[0]!='.'))
			{					
				if (_chdir(fileinfo.name)==0)
				{
					zERR_MESSAGE(2,zERR_BEGIN,"B: DSCAN: directory: "+zSTRING(fileinfo.name));
					ScanX();
					zERR_MESSAGE(2,zERR_END,"");
					_chdir("..");
				}
			}
		}
		// File checken
		else
		{			
			zSTRING filename(fileinfo.name);
			filename.Upper();
			zERR_MESSAGE(8,zERR_BEGIN,"B: DSCAN: file ... "+filename);

			// Alle FileHandler abchecken			
			zBOOL result = FALSE;
			zCList<zCScanDirFileHandler>* listnode = &cbList;
			while (!result && listnode)
			{				
				// Aktuelles Verzeichnis merken
				getcwd(buffer,MAX_PATH);				
				zFILE::DirectFileAccess(FALSE);				

				result = FALSE;

				// kann der FileHandler was mit dem Filetypen anfangen?
				zCScanDirFileHandler* handler = listnode->GetData();
				if (handler && handler->CanHandleFile(filename))
				{
					zERR_MESSAGE(4,zERR_BEGIN,"B: DSCAN: "+handler->GetName()+" handles "+filename);
					result = handler->HandleFile(filename, buffer, fileinfo);					
					for (int n=0;n<handler->GetNumMessages();n++)
					{
						zERR_MESSAGE(6,0,"B: MSG: "+handler->GetMessage(n));
					};
					zERR_MESSAGE(4,zERR_END,"");

					statHandledFiles++;
				}
				
				// Statistik aktualisieren
				statFoundFiles++;
				if (result) statTouchedFiles++;

				zFILE::DirectFileAccess(TRUE);
				_chdir(buffer);
				listnode = listnode->GetNextInList();
			};

			zERR_MESSAGE(9,zERR_END,"");
		};			
	} while (_findnext( find_handle, &fileinfo)==0);
	
	_findclose( find_handle );	
}


void zCScanDir::Scan(const zSTRING& rootDir)
{		
	if (zFILE::LockDirScan())
	{
		// Aktuelles Verzeichnis merken
		zFILE_FILE path;
		path.SetCurrentDir();

		// Statistikdaten initialisieren
		statFoundFiles = 0;
		statTouchedFiles = 0;	
		statHandledFiles = 0;

		// Zum Root-Verzeichnis wechseln
		zFILE_FILE directory;
		directory.SetPath(rootDir);
		directory.ChangeDir();

		// und los ...
		zERR_MESSAGE(3,0,"B: DSCAN: Scanning directory \""+directory.GetPath()+"\"");
		zFILE::DirectFileAccess(TRUE);
		ScanX();
		zFILE::DirectFileAccess(FALSE);		

		// Statistikdaten ausgeben
		zERR_MESSAGE(3,0,"B: DSCAN: "+zSTRING(statFoundFiles)+" found files.");
		zERR_MESSAGE(3,0,"B: DSCAN: "+zSTRING(statHandledFiles)+" handled files.");
		zERR_MESSAGE(3,0,"B: DSCAN: "+zSTRING(statTouchedFiles)+" touched files.");

		// Zum anfaenglichen Verzeichnis zurueckkehren
		path.ChangeDir();
		zFILE::UnlockDirScan();
	}
};


