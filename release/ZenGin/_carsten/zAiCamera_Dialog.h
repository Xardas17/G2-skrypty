//class zCAICamera
//{

	static void		GlobalDialogCamCleanUp	();

	// dialog camera
	void			InitDialogCam		();
	void			StartupDialogCam	();
	zBOOL			DialogPresetIsValid	(zCCSCamera *preset);
	void			StartDialogCam		(const zBOOL firstTime = TRUE);
	void			ReleaseDialogCam	();
	void			ReleaseLastDialogCam();
	zCCSCamera*		PickPreset			(const zSTRING name,const zCArray<zCCSCamera*>&list);

	// dialog kamera
	static zCArray<zCCSCamera*>	dialogCamList;

	float					dialogCamDuration;
	int						numOUsSpoken;
	int						numDialogCamTakes;
	int						lastNumDialogCamTakes;
	int						lastDialogCamSide;				// 0: right, 1: left
	int						firstSpeakerWasPC;
	zCCSCamera*				dialogCam;
	zSTRING					lastPresetName;
//}
