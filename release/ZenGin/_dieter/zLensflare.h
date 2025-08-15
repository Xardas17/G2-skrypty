/******************************************************************************** 
 
     $Workfile:: zLensflare.h         $                $Date:: 20.10.00 0:52    $
     $Revision:: 2                    $             $Modtime:: 20.10.00 0:49    $
        Author:: Hildebrandt                                                    
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   2D lensflare screen effect
   created: 29.5.2000

 * $Log: /current_work/zengin_work/_Dieter/zLensflare.h $
 * 
 * 2     20.10.00 0:52 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revisio: 2 $ ($Modtime: 20.10.00 0:49 $)

// =======================================================================================================================

#ifndef __ZLENSFLARE_H__
#define __ZLENSFLARE_H__

// declarations
class zCMesh;
class zCMaterial;

// ======================================================================================

class zCLensFlareFX : public zCObject {
	zCLASS_DECLARATION	(zCLensFlareFX)
public:
	static void		LoadLensFlareScript		();
	static void		ReleaseLensFlareScript	();
	void			RenderLensFlares		(zPOINT2&	scrLightPos) ;
	void			RenderLensFlares		(zCVob		*sourceVob);
	void			SetAlpha				(int		alpha);
	
protected:								
	virtual			~zCLensFlareFX			();

	// persistance						
	virtual void	Archive					(zCArchiver &arc);
	virtual void	Unarchive				(zCArchiver &arc);
											
private:									
	static zCMesh							*s_lensFlareMesh;
	static zCMesh							*s_coronaMesh;
	static zCMesh							*s_glowMesh;
											
	class zTVobLightLensFlare {
	public:
		zCMaterial							*lensFlareMaterial;
		enum zTFlareType					{ FT_CORONA, FT_GLOW, FT_FLARE 
											} flareType;
		zREAL								size;
		zREAL								alpha;
		zREAL								rangeMin;
		zREAL								rangeMax;
		zREAL								posScale;		// 0 = lightSource, 1 = screenOrigin
		zREAL								fadeScale;
		zTVobLightLensFlare() {
			memset	(this,0,sizeof(*this));
		};
	};
	zCArray<zTVobLightLensFlare>			lensFlareList;
	enum									{ FM_GLOW_ONLY, FM_MIXED, FM_NO_GLOW 
											} flareMix;
	zREAL									fadeScale;
};

#endif