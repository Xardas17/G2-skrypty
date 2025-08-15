
#ifndef _SPCCSCRIPTWIZARD_H_
#define _SPCCSCRIPTWIZARD_H_

#include "Zstring.h"
#include "zcontainer.h"

class spcCScriptWizard {
private:
	zSTRING thisFile;
	zSTRING preToken;

	zCArray<int> usedID;

	zSTRING constructTokenFirst	();
	zSTRING constructToken		();

public:
	spcCScriptWizard	();
	// Dieser Konstruktor hat als Nebeneffekt, daﬂ das Verzeichnis (zcfg) ge‰ndert wird
	spcCScriptWizard	(const zSTRING & fileName);
	// Der Destructor ‰ndert die Token.D
	~spcCScriptWizard	();

	zSTRING NewToken	(int tokID);  // Token automatisch erzeugen
	void	NewToken	(int tokID, zSTRING & tokName); // Token angeben (nur einmal pro Instanz)
	int		GetTokenID	(const zSTRING &tokName);

};

class spcCSVM 
{
public:
	spcCSVM						();
	~spcCSVM					();

	void		InitByScript	( int i );
	//int			GetOU			( const zSTRING& id );
	int			getNumber	();
	zSTRING		getOU		(int n);

private:
	int			number;
	int			classindex;
	zSTRING*	entry;
};

class spcCSVMManager 
{
public :
	spcCSVMManager		();
	~spcCSVMManager		();

	//int			GetOU	( const zSTRING& name, int voicenr );
	zSTRING	getFirstOU	();
	zSTRING getNextOU	();

private :
	int			svm_max;
	int			svm_iterator;
	int			ou_iterator;

	spcCSVM*	sv_module;
};

#endif