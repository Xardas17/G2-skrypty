
#include "zengine.h"

#include "ZDisk.h"
#include "zParser.h"

#include "spcCScriptWizard.h"

#include "zCCSPlayer.h"



zSTRING spcCScriptWizard :: constructTokenFirst()
{
	if (thisFile.Search(".D")==-1) return zSTRING("DEFAULT");
	int z=1;
	zSTRING stepStr = thisFile.PickWord(z,"\\","\\");
	while (stepStr.Search(".D")==-1)
	{ 
		z++; 
		stepStr += zSTRING("_")+thisFile.PickWord(z,"\\","\\");
	}
	return zSTRING("OU_")+stepStr.PickWord(1,".",".");
}
zSTRING spcCScriptWizard :: constructToken()
{
	return preToken;
}

spcCScriptWizard :: spcCScriptWizard()
	: thisFile(""), usedID(), preToken()
{ }
spcCScriptWizard :: spcCScriptWizard(const zSTRING & fileName)
	: thisFile(fileName), usedID()
{ 
	thisFile.Upper();
	preToken = constructTokenFirst();
}
spcCScriptWizard :: ~spcCScriptWizard()
{
	zoptions->ChangeDir(DIR_SCRIPTS);
	zFILE* tf = zfactory->CreateZFile(zSTRING("System\\_intern\\Token.d"));
	if (tf->Exists()) 
	{
		tf->Open();
		tf->Append();
	}
	else tf->Create();
	for (int i=0; i<usedID.GetNumInList(); i++)
		if (usedID[i]>=0)
		tf->Write(	zSTRING("CONST INT ")+
					constructToken()+zSTRING("_")+zSTRING(usedID[i])+
					zSTRING(" = ")+zSTRING(usedID[i])+zSTRING(";\r\n")); // AutoToken
		else
		tf->Write(	zSTRING("CONST INT ")+
					constructToken()+
					zSTRING(" = ")+zSTRING(-usedID[i])+zSTRING(";\r\n")); // UserToken
	tf->Close();
	delete tf;
}

zSTRING spcCScriptWizard :: NewToken(int tokID)
{
	if (thisFile=="") return thisFile;
	usedID.Insert(tokID);
	return constructToken()+zSTRING("_")+zSTRING(tokID);
}

void spcCScriptWizard :: NewToken(int tokID, zSTRING & tokName)
{
	preToken = tokName;
	usedID.Insert(-tokID);
}

// *********************************
// Standard Voice Modul Manager
// *********************************

spcCSVMManager :: spcCSVMManager ()
: sv_module(NULL), svm_max(0), svm_iterator(0), ou_iterator(0)
{
	// 1. Get Number of Modules
	zCPar_Symbol* sym = parser.GetSymbol("SVM_MODULES");
	if (sym) {
		sym -> GetValue (svm_max);
		// 2. Create empty Modules
		sv_module = new spcCSVM[svm_max];
		// 3. Init these Modules
		for (int i=0; i<svm_max; i++) {
			sv_module[i].InitByScript(i);
		}
	} else
		zerr.Warning("A:Spacer: No Voice-Modules found.");	
}

spcCSVMManager :: ~spcCSVMManager ()
{
	if (sv_module!=0) delete[] sv_module;
}

zSTRING	spcCSVMManager :: getFirstOU()
{
	if (sv_module==0) return zSTRING("_ITER_END");
	svm_iterator=0;
	ou_iterator=0;
	return sv_module[0].getOU(0);
}
zSTRING spcCSVMManager :: getNextOU()
{
	if (sv_module==0) return zSTRING("_ITER_END");
	ou_iterator++;
	if (ou_iterator==sv_module[svm_iterator].getNumber())
	{
		ou_iterator=0;
		svm_iterator++;
		if (svm_iterator==svm_max) return zSTRING("_ITER_END");
	}
	return sv_module[svm_iterator].getOU(ou_iterator);
}

// *********************************
// Standard Voice Modul
// *********************************

spcCSVM :: spcCSVM ()
: entry(NULL), number(0)
{}

spcCSVM :: ~spcCSVM ()
{
	if (entry!=0) delete[] entry;
}

void spcCSVM :: InitByScript ( int i )
{
	zSTRING name	= "SVM_"+zSTRING(i);
	int index		= parser.GetIndex(name);
	if (index>=0) {
		// 1.Getting the class Size
		classindex = parser.GetIndex("C_SVM");
		if (classindex>=0) {
			zCPar_Symbol* sym = parser.GetSymbol(classindex);
			number	= sym -> ele;
			entry	= new zSTRING[number];
			parser.CreateInstance(index,entry);
		} else
			zerr.Warning("A:Spacer:Voide Module Class (C_SVM) not found.");

	} else
		zerr.Warning("A:Spacer:Voice Module not found :"+name);
}

int	spcCSVM :: getNumber()
{
	return number;
}
zSTRING	spcCSVM :: getOU(int n)
{
	if (entry!=0)
		return entry[n];
	else return zSTRING("");
}
