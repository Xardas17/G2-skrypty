// Matritzen Berechnungen 

zMAT4 CalcMatrixFromPoly (zCPolygon *poly)
{
	// Matrix setzen
	zMAT4 mat			= Alg_Identity3D();
	if (!poly) return mat;

	zCVertex*	v1			= 0;
	zCVertex*	v2			= 0;
	zREAL		bestDist	= 0;

	// 2 Vertices rauspicken
	for (int i=0; i<poly->polyNumVert; i++) {
		zCVertex *_v1 = poly->vertex[i];
		zCVertex *_v2 = poly->vertex[(i+1) % poly->polyNumVert];
		if ((_v1->position-_v2->position).Length() > bestDist) {
			v1 = _v1;
			v2 = _v2;
			bestDist=(_v1->position-_v2->position).Length();
		};
	};

	// Matrix berechenen
	zVEC3	right, up, at;
	up		= poly->GetNormal();
	right	= (v2->position - v1->position);
	right.Normalize();
	at		= up ^ right;

	// Matrix setzen
	mat.SetAtVector		(at);
	mat.SetUpVector		(up);
	mat.SetRightVector	(right);
	mat.SetTranslation	(v1->position);

	return mat;
};

zMAT4 CalcMatrixFromVob (zCVob *vob)
{
	// Matrix setzen
	zMAT4 mat			= Alg_Identity3D();
	if (!vob) return mat;

	mat = vob->trafoObjToWorld;

	return mat;
};

zBOOL CalcMatrixDifference (zMAT4& mat1, zMAT4& mat2, zMAT4& res)
{
	res = Alg_Identity3D();

	// Testen, ob Matrizen =FCberhaupt verschieden sind
	zBOOL diff = FALSE;
	if (!mat1.GetAtVector()   .IsEqualEps (mat2.GetAtVector())	 )	diff = TRUE;
	if (!mat1.GetUpVector()   .IsEqualEps (mat2.GetUpVector())	 )	diff = TRUE;
	if (!mat1.GetRightVector().IsEqualEps (mat2.GetRightVector()))	diff = TRUE;
	zREAL trans = (mat2.GetTranslation()-mat1.GetTranslation()).Length();
	if (trans>0.1F)	diff = TRUE;		// 1mm

	if (!diff) {
		// keine Nennenswerte Differenz zw. den beiden Matrizen
		// =3D> alle Vobs UNBERUEHRT lassen !
		return FALSE;
	};

	// Matrix Differenz berechnen
	res = mat2 * mat1.Inverse();
	//res.ResetRotation();
	return TRUE;
/*	{	// Test
		zCPolygon	*poly1 =3D world.GetBspTree()->mesh->polyList[0];
		zCPolygon	*poly2 =3D world.GetBspTree()->mesh->polyList[100];
		zMAT4		mat1, mat2, res;

		mat1 =3D CalcMatrixFromPoly	(poly1);
		mat2 =3D CalcMatrixFromPoly	(poly2);
		CalcMatrixDifference		(mat1, mat2, res);
		zVEC3 v =3D poly1->vertex[0]->position;
		v =3D res * v;
	};*/
};

