/******************************************************************************** 
 
     $Workfile:: zEigen.cpp           $                $Date:: 15.08.00 23:54   $
     $Revision:: 6                    $             $Modtime:: 7.08.00 17:21    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/zengin_work/_Dieter/zEigen.cpp $
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 5     21.07.00 14:28 Hildebrandt
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
/// @version $Revision: 6 $ ($Modtime: 7.08.00 17:21 $)


#include <fstream.h>
#include <math.h>

#include <zEigen.h>
#include <zCore.h>

//===========================================================================

// error handling
int zCMgcEigenD::verbose = 0;
unsigned zCMgcEigenD::error = 0;
const unsigned zCMgcEigenD::invalid_size      = 0x00000001;
const unsigned zCMgcEigenD::allocation_failed = 0x00000002;
const unsigned zCMgcEigenD::ql_exceeded       = 0x00000004;
const char* zCMgcEigenD::message[3] = {
	"invalid matrix size",
	"allocation failed",
	"QL algorithm - exceeded maximum iterations"
};

//---------------------------------------------------------------------------

zCMgcEigenD::
zCMgcEigenD (int _size)
{
	if ( (size = _size) <= 1 ) {
		Report(invalid_size);
		return;
	}
	if ( (mat = zNEW(double*) [size]) == 0 ) {
		Report(allocation_failed);
		return;
	}
	for (int d = 0; d < size; d++)
		if ( (mat[d] = zNEW(double) [size]) == 0 ) {
			Report(allocation_failed);
			return;
		}
	if ( (diag = zNEW(double) [size]) == 0 ) {
		Report(allocation_failed);
		return;
	}
	if ( (subd = zNEW(double) [size]) == 0 ) {
		Report(allocation_failed);
		return;
	}
}
//---------------------------------------------------------------------------
zCMgcEigenD::
~zCMgcEigenD ()
{
	delete[] subd;
	delete[] diag;
	for (int d = 0; d < size; d++)
		delete[] mat[d];
	delete[] mat;
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
Tridiagonal2 (double** mat, double* diag, double* subd)
{
	// matrix is already tridiagonal

	diag[0] = mat[0][0];
	diag[1] = mat[1][1];
	subd[0] = mat[0][1];
	subd[1] = 0;
	mat[0][0] = 1;  mat[0][1] = 0;
	mat[1][0] = 0;  mat[1][1] = 1;
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
Tridiagonal3 (double** mat, double* diag, double* subd)
{
	double a = mat[0][0], b = mat[0][1], c = mat[0][2],
						 d = mat[1][1], e = mat[1][2],
										f = mat[2][2];

	diag[0] = a;
	subd[2] = 0;
	if ( c != 0 ) {
		double ell = sqrt(b*b+c*c);
		b /= ell;
		c /= ell;
		double q = 2*b*e+c*(f-d);
		diag[1] = d+c*q;
		diag[2] = f-c*q;
		subd[0] = ell;
		subd[1] = e-b*q;
		mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0;
		mat[1][0] = 0; mat[1][1] = b; mat[1][2] = c;
		mat[2][0] = 0; mat[2][1] = c; mat[2][2] = -b;
	}
	else {
		diag[1] = d;
		diag[2] = f;
		subd[0] = b;
		subd[1] = e;
		mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0;
		mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0;
		mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1;
	}
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
Tridiagonal4 (double** mat, double* diag, double* subd)
{
	// save matrix M
	double
	a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
				   e = mat[1][1], f = mat[1][2], g = mat[1][3],
								  h = mat[2][2], i = mat[2][3],
												 j = mat[3][3];

	diag[0] = a;
	subd[3] = 0;

	mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0;
	mat[1][0] = 0;
	mat[2][0] = 0;
	mat[3][0] = 0;

	if ( c != 0 || d != 0 ) {
		double q11, q12, q13;
		double q21, q22, q23;
		double q31, q32, q33;

		// build column Q1
		double len = sqrt(b*b+c*c+d*d);
		q11 = b/len;
		q21 = c/len;
		q31 = d/len;

		subd[0] = len;

		// compute S*Q1
		double v0 = e*q11+f*q21+g*q31;
		double v1 = f*q11+h*q21+i*q31;
		double v2 = g*q11+i*q21+j*q31;

		diag[1] = q11*v0+q21*v1+q31*v2;

       	// build column Q3 = Q1x(S*Q1)
		q13 = q21*v2-q31*v1;
		q23 = q31*v0-q11*v2;
		q33 = q11*v1-q21*v0;
		len = sqrt(q13*q13+q23*q23+q33*q33);
		if ( len > 0 ) {
			q13 /= len;
			q23 /= len;
			q33 /= len;

			// build column Q2 = Q3xQ1
			q12 = q23*q31-q33*q21;
			q22 = q33*q11-q13*q31;
			q32 = q13*q21-q23*q11;

			v0 = q12*e+q22*f+q32*g;
			v1 = q12*f+q22*h+q32*i;
			v2 = q12*g+q22*i+q32*j;
			subd[1] = q11*v0+q21*v1+q31*v2;
			diag[2] = q12*v0+q22*v1+q32*v2;
			subd[2] = q13*v0+q23*v1+q33*v2;

			v0 = q13*e+q23*f+q33*g;
			v1 = q13*f+q23*h+q33*i;
			v2 = q13*g+q23*i+q33*j;
			diag[3] = q13*v0+q23*v1+q33*v2;
		}
		else {  // S*Q1 parallel to Q1, choose any valid Q2 and Q3
			subd[1] = 0;

			len = q21*q21+q31*q31;
			if ( len > 0 ) {
				double tmp = q11-1;
				q12 = -q21;
				q22 = 1+tmp*q21*q21/len;
                q32 = tmp*q21*q31/len;

				q13 = -q31;
				q23 = q32;
				q33 = 1+tmp*q31*q31/len;

				v0 = q12*e+q22*f+q32*g;
				v1 = q12*f+q22*h+q32*i;
				v2 = q12*g+q22*i+q32*j;
				diag[2] = q12*v0+q22*v1+q32*v2;
				subd[2] = q13*v0+q23*v1+q33*v2;

				v0 = q13*e+q23*f+q33*g;
				v1 = q13*f+q23*h+q33*i;
				v2 = q13*g+q23*i+q33*j;
				diag[3] = q13*v0+q23*v1+q33*v2;
			}
			else {  // Q1 = (+-1,0,0)
				q12 = 0; q22 = 1; q32 = 0;
				q13 = 0; q23 = 0; q33 = 1;

				diag[2] = h;
				diag[3] = j;
				subd[2] = i;
			}
		}

		mat[1][1] = q11; mat[1][2] = q12; mat[1][3] = q13;
		mat[2][1] = q21; mat[2][2] = q22; mat[2][3] = q23;
		mat[3][1] = q31; mat[3][2] = q32; mat[3][3] = q33;
	}
	else {
		diag[1] = e;
		subd[0] = b;
		mat[1][1] = 1;
		mat[2][1] = 0;
		mat[3][1] = 0; 

		if ( g != 0 ) {
			double ell = sqrt(f*f+g*g);
			f /= ell;
			g /= ell;
			double Q = 2*f*i+g*(j-h);

			diag[2] = h+g*Q;
			diag[3] = j-g*Q;
			subd[1] = ell;
			subd[2] = i-f*Q;
			mat[1][2] = 0;  mat[1][3] = 0;
			mat[2][2] = f;  mat[2][3] = g;
			mat[3][2] = g;  mat[3][3] = -f;
		}
		else {
			diag[2] = h;
			diag[3] = j;
			subd[1] = f;
			subd[2] = i;
			mat[1][2] = 0;  mat[1][3] = 0;
			mat[2][2] = 1;  mat[2][3] = 0;
			mat[3][2] = 0;  mat[3][3] = 1;
		}
	}
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
TridiagonalN (int n, double** mat, double* diag, double* subd)
{
	int i, j, k, ell;

	for (i = n-1, ell = n-2; i >= 1; i--, ell--) {
		double h = 0, scale = 0;

		if ( ell > 0 ) {
			for (k = 0; k <= ell; k++)
				scale += fabs(mat[i][k]);
			if ( scale == 0 )
				subd[i] = mat[i][ell];
			else {
				for (k = 0; k <= ell; k++) {
					mat[i][k] /= scale;
					h += mat[i][k]*mat[i][k];
				}
				double f = mat[i][ell];
				double g = ( f > 0 ? -sqrt(h) : sqrt(h) );
				subd[i] = scale*g;
				h -= f*g;
				mat[i][ell] = f-g;
				f = 0;
				for (j = 0; j <= ell; j++) {
					mat[j][i] = mat[i][j]/h;
					g = 0;
					for (k = 0; k <= j; k++)
						g += mat[j][k]*mat[i][k];
					for (k = j+1; k <= ell; k++)
						g += mat[k][j]*mat[i][k];
					subd[j] = g/h;
					f += subd[j]*mat[i][j];
				}
				double hh = f/(h+h);
				for (j = 0; j <= ell; j++) {
					f = mat[i][j];
					subd[j] = g = subd[j] - hh*f;
					for (k = 0; k <= j; k++)
						mat[j][k] -= f*subd[k]+g*mat[i][k];
				}
            }
		}
		else
			subd[i] = mat[i][ell];

		diag[i] = h;
	}

	diag[0] = subd[0] = 0;
	for (i = 0, ell = -1; i <= n-1; i++, ell++) {
		if ( diag[i] ) {
			for (j = 0; j <= ell; j++) {
				double sum = 0;
				for (k = 0; k <= ell; k++)
					sum += mat[i][k]*mat[k][j];
				for (k = 0; k <= ell; k++)
					mat[k][j] -= sum*mat[k][i];
			}
		}
		diag[i] = mat[i][i];
		mat[i][i] = 1;
		for (j = 0; j <= ell; j++)
			mat[j][i] = mat[i][j] = 0;
	}

	// re-ordering if zCMgcEigenD::QLAlgorithm is used subsequently
	for (i = 1, ell = 0; i < n; i++, ell++)
		subd[ell] = subd[i];
	subd[n-1] = 0;
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
QLAlgorithm (int n, double* diag, double* subd, double** mat)
{
	const int eigen_maxiter = 30;

	for (int ell = 0; ell < n; ell++) {
		int iter;
		for (iter = 0; iter < eigen_maxiter; iter++) {
			int m;
			for (m = ell; m <= n-2; m++) {
				double dd = fabs(diag[m])+fabs(diag[m+1]);
				if ( (double)(fabs(subd[m])+dd) == dd )
					break;
			}
			if ( m == ell )
				break;

			double g = (diag[ell+1]-diag[ell])/(2*subd[ell]);
			double r = sqrt(g*g+1);
			if ( g < 0 )
				g = diag[m]-diag[ell]+subd[ell]/(g-r);
			else
				g = diag[m]-diag[ell]+subd[ell]/(g+r);
			double s = 1, c = 1, p = 0;
			for (int i = m-1; i >= ell; i--) {
				double f = s*subd[i], b = c*subd[i];
				if ( fabs(f) >= fabs(g) ) {
					c = g/f;
					r = sqrt(c*c+1);
					subd[i+1] = f*r;
					c *= (s = 1/r);
				}
				else {
					s = f/g;
					r = sqrt(s*s+1);
					subd[i+1] = g*r;
					s *= (c = 1/r);
				}
				g = diag[i+1]-p;
				r = (diag[i]-g)*s+2*b*c;
				p = s*r;
				diag[i+1] = g+p;
				g = c*r-b;

				for (int k = 0; k < n; k++) {
					f = mat[k][i+1];
					mat[k][i+1] = s*mat[k][i]+c*f;
					mat[k][i] = c*mat[k][i]-s*f;
				}
			}
			diag[ell] -= p;
			subd[ell] = g;
			subd[m] = 0;
		}
		if ( iter == eigen_maxiter ) {
			Report(ql_exceeded);
			return;
		}
	}
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
DecreasingSort (int n, double* eigval, double** eigvec)
{
	// sort eigenvalues in decreasing order, e[0] >= ... >= e[n-1]
	for (int i = 0, k; i <= n-2; i++) {
		// locate maximum eigenvalue
		double max = eigval[k=i];
		int j;
		for (j = i+1; j < n; j++)
			if ( eigval[j] > max )
				max = eigval[k=j];

		if ( k != i ) {
			// swap eigenvalues
			eigval[k] = eigval[i];
			eigval[i] = max;

			// swap eigenvectors
			for (j = 0; j < n; j++) {
				double tmp = eigvec[j][i];
				eigvec[j][i] = eigvec[j][k];
				eigvec[j][k] = tmp;
			}
		}
	}
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
IncreasingSort (int n, double* eigval, double** eigvec)
{
	// sort eigenvalues in increasing order, e[0] <= ... <= e[n-1]
	for (int i = 0, k; i <= n-2; i++) {
		// locate minimum eigenvalue
		double min = eigval[k=i];
        int j;
		for (j = i+1; j < n; j++)
			if ( eigval[j] < min )
				min = eigval[k=j];

		if ( k != i ) {
			// swap eigenvalues
			eigval[k] = eigval[i];
			eigval[i] = min;

			// swap eigenvectors
			for (j = 0; j < n; j++) {
				double tmp = eigvec[j][i];
				eigvec[j][i] = eigvec[j][k];
				eigvec[j][k] = tmp;
			}
		}
	}
}
//---------------------------------------------------------------------------
zCMgcEigenD& zCMgcEigenD::
Matrix (double** inmat)
{
	for (int row = 0; row < size; row++)
		for (int col = 0; col < size; col++)
			mat[row][col] = inmat[row][col];
	return *this;
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
EigenStuff2 ()
{
	Tridiagonal2(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
EigenStuff3 ()
{
	Tridiagonal3(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
EigenStuff4 ()
{
	Tridiagonal4(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
EigenStuffN ()
{
	TridiagonalN(size,mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
EigenStuff ()
{
	switch ( size ) {
		case 2 : Tridiagonal2(mat,diag,subd);       break;
		case 3 : Tridiagonal3(mat,diag,subd);       break;
		case 4 : Tridiagonal4(mat,diag,subd);       break;
		default: TridiagonalN(size,mat,diag,subd);  break;
	}
	QLAlgorithm(size,diag,subd,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
DecrSortEigenStuff2 ()
{
	Tridiagonal2(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	DecreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
DecrSortEigenStuff3 ()
{
	Tridiagonal3(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	DecreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
DecrSortEigenStuff4 ()
{
	Tridiagonal4(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	DecreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
DecrSortEigenStuffN ()
{
	TridiagonalN(size,mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	DecreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
DecrSortEigenStuff ()
{
	switch ( size ) {
		case 2 : Tridiagonal2(mat,diag,subd);       break;
		case 3 : Tridiagonal3(mat,diag,subd);       break;
		case 4 : Tridiagonal4(mat,diag,subd);       break;
		default: TridiagonalN(size,mat,diag,subd);  break;
	}
	QLAlgorithm(size,diag,subd,mat);
	DecreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
IncrSortEigenStuff2 ()
{
	Tridiagonal2(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	IncreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
IncrSortEigenStuff3 ()
{
	Tridiagonal3(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	IncreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
IncrSortEigenStuff4 ()
{
	Tridiagonal4(mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	IncreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
IncrSortEigenStuffN ()
{
	TridiagonalN(size,mat,diag,subd);
	QLAlgorithm(size,diag,subd,mat);
	IncreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
IncrSortEigenStuff ()
{
	switch ( size ) {
		case 2 : Tridiagonal2(mat,diag,subd);       break;
		case 3 : Tridiagonal3(mat,diag,subd);       break;
		case 4 : Tridiagonal4(mat,diag,subd);       break;
		default: TridiagonalN(size,mat,diag,subd);  break;
	}
	QLAlgorithm(size,diag,subd,mat);
	IncreasingSort(size,diag,mat);
}
//---------------------------------------------------------------------------
int zCMgcEigenD::
Number (unsigned single_error)
{
	int result;
	for (result = -1; single_error; single_error >>= 1)
		result++;
	return result;
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
Report (unsigned single_error)
{
	if ( zCMgcEigenD::verbose )
		cout << "zCMgcEigenD: " << message[Number(single_error)] << endl;
	else
		ofstream("eigen.err",ios::out|ios::app)
			 << "zCMgcEigenD: " << message[Number(single_error)] << endl;

	error |= single_error;
}
//---------------------------------------------------------------------------
void zCMgcEigenD::
Report (ostream& ostr)
{
	for (unsigned single_error = 1; single_error; single_error <<= 1)
		if ( error & single_error )
			ostr << "zCMgcEigenD: " << message[Number(single_error)] << endl;

	error = 0;
}
//===========================================================================
