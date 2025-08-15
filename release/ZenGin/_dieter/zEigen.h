/******************************************************************************** 
 
     $Workfile:: zEigen.h             $                $Date:: 4.12.00 17:18    $
     $Revision:: 6                    $             $Modtime:: 4.12.00 16:37    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Eigen-Vectors
   created       : ?.?.98

 * $Log: /current_work/zengin_work/_Dieter/zEigen.h $
 * 
 * 6     4.12.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 6 $ ($Modtime: 4.12.00 16:37 $)

#ifndef __ZEIGEN_H__
#define __ZEIGEN_H__

#include <iostream>

class zCMgcEigenD
{
public:
	zCMgcEigenD	(int _size);
	~zCMgcEigenD();

    // set the matrix for eigensolving
	double& Matrix (int row, int col) { return mat[row][col]; }
	zCMgcEigenD& Matrix (double** inmat);

	// get the results of eigensolving
	double Eigenvalue (int d) { return diag[d]; }
	double Eigenvector (int row, int col) { return mat[row][col]; }
	const double* Eigenvalue () { return diag; }
	const double** Eigenvector () { return (const double**) mat; }

	// solve eigensystem
	void EigenStuff2 ();  // uses TriDiagonal2
	void EigenStuff3 ();  // uses TriDiagonal3
	void EigenStuff4 ();  // uses TriDiagonal4
	void EigenStuffN ();  // uses TriDiagonalN
	void EigenStuff  ();  // uses switch statement

	// solve eigensystem, use decreasing sort on eigenvalues
	void DecrSortEigenStuff2 ();
	void DecrSortEigenStuff3 ();
	void DecrSortEigenStuff4 ();
	void DecrSortEigenStuffN ();
	void DecrSortEigenStuff  ();

	// solve eigensystem, use increasing sort on eigenvalues
	void IncrSortEigenStuff2 ();
	void IncrSortEigenStuff3 ();
	void IncrSortEigenStuff4 ();
	void IncrSortEigenStuffN ();
	void IncrSortEigenStuff  ();

	// debugging output?
	double& Tdiag (int i) { return diag[i]; }
	double& Tsubdiag (int i) { return subd[i]; }
	void Reduce () { TridiagonalN(size,mat,diag,subd); }

private:
	int size;
	double** mat;
	double* diag;
	double* subd;

	// Householder reduction to tridiagonal form
	void Tridiagonal2 (double** mat, double* diag, double* subd);
	void Tridiagonal3 (double** mat, double* diag, double* subd);
	void Tridiagonal4 (double** mat, double* diag, double* subd);
	void TridiagonalN (int n, double** mat, double* diag, double* subd);

	// QL algorithm with implicit shifting, applies to tridiagonal matrices
	void QLAlgorithm (int n, double* diag, double* subd, double** mat);

	// sort eigenvalues from largest to smallest
	void DecreasingSort (int n, double* eigval, double** eigvec);

	// sort eigenvalues from smallest to largest
	void IncreasingSort (int n, double* eigval, double** eigvec);

// error handling
public:
	static int verbose;
	static unsigned error;
	static void Report (ostream& ostr);
private:
	static const unsigned invalid_size;
	static const unsigned allocation_failed;
	static const unsigned ql_exceeded;
	static const char* message[3];
	static int Number (unsigned single_error);
	static void Report (unsigned single_error);
};

#endif