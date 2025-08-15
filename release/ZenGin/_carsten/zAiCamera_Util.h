/****************************************************************
*
* Camera Artificial Intelligence
* File          : zAICamera_Util.h (AI)
#* Projekt       : Gothic
* Autor         : Carsten Edenfeld
*
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations:
*****************************************************************
- missing features:
*****************************************************************
- comments:  
****************************************************************/


//class zCAICamera
//{
public:
	// console editing
	void			ParameterChanged	();
	zBOOL			Console_EvalFunc	(const zSTRING &s, zSTRING &msg);
	
	int				raysCasted;

protected:

	// math
	zPOINT3&		CalcAziElevRange	(const float &aziDeg,const float &elevDeg,const float &rng, const zMAT4 &trafoObjToWorld);
	zTBSphere3D		CalcMinimumBSphere	(zCArray<zPOINT3>&targetList);
	float			Distance			(zPOINT3 & p1, zPOINT3 & p2) { return (p1-p2).Length(); }
	zBOOL			NearlyEqual			(const zPOINT3 &p1,const zPOINT3 &p2, const float &eps = 1.0F);

	// misc
	zBOOL			CheckUnderWaterFX	();

	// debug
	void			InitHelperVobs		();
	void			DeleteHelperVobs	();
	void			ShowDebug			();
	void			DrawClipLine		(const zPOINT3 &a,const zPOINT3 &b,const zCOLOR color = GFX_WHITE );

	zBOOL					underWater;
	zBOOL					inCutsceneMode;
							
	// debug krempel
	zSTRING					debugS;  
	zBOOL					showPath;
	zCVob*					focusVob; 
	zCVob*					ctrlDot[MAX_CTRL_VOBS];


//}


