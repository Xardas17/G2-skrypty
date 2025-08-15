/******************************************************************************** 
 
     $Workfile:: oSVM.cpp             $                $Date:: 19.09.00 18:19   $
     $Revision:: 9                    $             $Modtime:: 19.09.00 18:18   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oSVM.cpp $
 * 
 * 9     19.09.00 18:19 Speckels
 * 
 * 8     19.09.00 18:08 Speckels
 * 
 * 7     2.08.00 14:25 Wohlers
 * 
 * 6     31.07.00 22:04 Wohlers
 * 
 * 5     21.07.00 15:35 Wohlers
 * 
 * 4     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"
#include "zParser.h"
#include "zCCSPlayer.h"

#include "oSVM.h"
#include "oGame.h"
#include "oCSManager.h"

// *********************************
// Standard Voice Modul Manager
// *********************************

oCSVMManager :: oCSVMManager ()
{
	sv_module	= NULL;
	svm_max		= 0;
	// 1. Get Number of Modules
	zCPar_Symbol* sym = parser.GetSymbol("SVM_MODULES");
	if (sym) {
		sym -> GetValue (svm_max);
		// 2. Create empty Modules
		sv_module = zNEW( oCSVM )[svm_max];
		// 3. Init these Modules
		for (int i=0; i<svm_max; i++) {
			sv_module[i].InitByScript(i);
		}
	} else
		zERR_WARNING("U: SVM:  No Voice-Modules found.");	
}

oCSVMManager :: ~oCSVMManager ()
{
	delete[] sv_module; sv_module = NULL;
}

int oCSVMManager :: GetOU (const zSTRING &name, int voice)
{
	int res = -1;
	if (voice < svm_max) 
	{
		if (name[0]=='$') 
		{
			// Standard Voice Modul Zugriff.
			zSTRING n = name;
			n.Delete(0,1);
			n.Upper();
			n.TrimRight();
			n.TrimLeft();
			res = sv_module[voice].GetOU(n);
			if (res < 0) 
				zERR_WARNING("U: SVM: Output-Unit \""+name+"\" not found (SVM_"+zSTRING(voice)+")");
		} 
		else 
		{
			// Normaler Zugriff direkt über Name
			res = ogame->GetCutsceneManager()->LibValidateOU(zSTRING(name));
			/* Alte ParserVersion mit token.d
			zCPar_Symbol* sym = parser.GetSymbol(name);
			if (sym) sym -> GetValue(res);*/
			if (res < 0) 
				zERR_WARNING("U: SVM: Output-Unit \""+name+"\" not found.");
		}	
	} 
	else 
	{
		zERR_WARNING("U: SVM: Voice-number too high ("+zSTRING(voice)+")");
	}
	return res;
}

// *********************************
// Standard Voice Modul
// *********************************

oCSVM :: oCSVM ()
{
	entry		= NULL;
	number		= 0;
	classindex	= 0;
}

oCSVM :: ~oCSVM ()
{
	delete[] entry;		entry = NULL;
}

void oCSVM :: InitByScript ( int i )
{
	zSTRING name	= "SVM_"+zSTRING(i);
	int index		= parser.GetIndex(name);
	if (index>=0) {
		// 1.Getting the class Size
		classindex = parser.GetIndex("C_SVM");
		if (classindex>=0) {
			zCPar_Symbol* sym = parser.GetSymbol(classindex);
			number	= sym -> ele;
			entry	= zNEW( zSTRING ) [number];
			parser.CreateInstance(index,entry);
		} else
			zERR_WARNING("U: SVM: Voice Module Class (C_SVM) not found.");

	} else
		zERR_WARNING("U: SVM: Voice Module not found :"+name);
}

int oCSVM :: GetOU (const zSTRING &name)
{
	for (int i=0; i<number; i++) {
		// Getting the ClassVarNames
		zCPar_Symbol* var = parser.GetSymbol(classindex + i + 1);
		if (var) {
			zSTRING n = var->name;
			n.Delete("C_SVM.");
			if (n==name) {
				// Die Cutscene-Lib nach dieser OU fragen
				if (ogame->GetCutsceneManager()) {
					if (entry[i].IsEmpty()) return -1;
					return ogame->GetCutsceneManager() -> LibValidateOU(entry[i]);
				} else
					return -1;
				/* Alte Parserversion noch mit Token.d
				// Diese jetzt suchen
				zCPar_Symbol* sym = parser.GetSymbol(res);
				if (sym) {
					// Und schließlich die Nummer ermitteln
					int value;
					sym -> GetValue(value);
					return value;
				}*/
			}
		}
	}
	return -1;
}
