 
#include <zVob.h>
#include "zVobMisc.h"

// Trigger-Klasse
// Dieses Object kann eine Cutscene triggern, wenn seine BBox betreten wird

class oCCSTrigger : public zCTrigger
{
	zCLASS_DECLARATION	(oCCSTrigger)
public:
	oCCSTrigger() : zCTrigger() {};
	oCCSTrigger( zSTRING name ) : zCTrigger() { SetVobName(name.Upper()); };

	virtual void		TriggerTarget			(zCVob* vobInstigator);
	virtual void		UntriggerTarget			(zCVob* vobInstigator);


protected:
	virtual void Archive(zCArchiver &arc);
	virtual void Unarchive(zCArchiver &arc);

};