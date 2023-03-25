#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iomanip>
#include <cmath> 
using namespace std;

//function to calculate infinity norm of 2x2 matrix
//infinity norm of a matrix is maximum absolute value sum of rows
//multipying norm of A and A inverse gives us condition number of matrix A
float normINF (float **matt) {
	float norm;
	float x = matt[0][0];
	float y = matt[0][1];
	float z = matt[1][0];
	float w = matt[1][1];
	float r1 = abs(x)+abs(y);
	float r2 = abs(z)+abs(w);
	//infinity norm of matrix A is the maximum one of absolute row sums
	if (r1>r2) {
		norm = r1;  
	}else {
		norm = r2;
	}
	return norm;
}
//similar to infinity norm, for one norm we should compute absolute value sum of columns
float normONE (float **matt) {
	float normOne;
	float a = matt[0][0];
	float b = matt[0][1];
	float c = matt[1][0];
	float d = matt[1][1];
	float c1 = abs(a)+abs(c);
	float c2 = abs(b)+abs(d);
	//one norm of matrix A is the maximum one of absolute column sums
	if (c1>c2) {
		normOne = c1;  
	}else {
		normOne = c2;
	}
	return normOne;
}

// function to calculate determinant
float determinant(float **a, int dim) {
float det = 0;
float** submatrix = new float*[dim];  // for cofactor matrix, we create submatrix
for (int i = 0; i < dim; ++i)
submatrix[i] = new float[dim];

if (dim == 1)
    return a[0][0];   // determinant of 1x1 matrix is just element 1x1
else if (dim == 2)
    return ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1])); // determinant of 2x2 matrix is ad-bc
else {
    for (int x = 0; x < dim; x++) {
    int subi = 0;
    for (int i = 1; i < dim; i++) {
    int subj = 0;
    for (int j = 0; j < dim; j++) {
    if (j == x)
    continue;
    submatrix[subi][subj] = a[i][j];  //creating our cofactor matrix.
    subj++;
    }
    subi++;
    }
    det = det + (pow(-1, x) * a[0][x] * determinant(submatrix, dim - 1));
    }
    }

    for (int i = 0; i < dim; ++i)
    delete [] submatrix[i];
    delete [] submatrix;

    return det;
}

int main( int argc, char *argv[] )  {
	
	ifstream f1 (argv[1]); //reading A.txt
	ifstream f2 (argv[2]); //reading b.txt
	// to calculate dimension of matrix A:
	string line;
	int n=0;
	while ( getline (f1,line) )
    {
      
      n++; 
    }
	
	f1.clear(); // clear bad state 
	f1.seekg( 0 ); // to read A.txt from beginning in the following lines
	// storing A in dynamic memory
	float **M_A;  
	M_A = new float *[n+1];  //M_A will be the memory that has nxn+1 size to store Augmented matrix 
	if(f1.is_open())
	{
		for(int j=0;j<n;j++) {
			M_A[j]=new float [n];      //n row of M_A now has columns size of n
			for(int i=0;i<n;i++) {
				f1 >> M_A[j][i];      //storing matrix A in M_A
			}
		}
	}
	f1.close();
	//print matrix A
	for(int i=0;i<n;i++){
		if (i !=0){
			cout << "\n";
		}
		for(int j=0;j<n;j++){
			cout << "matrix A is: "<< M_A[i][j]<<" ";
		}
	}
	
	//we will calculate condition numbers if dimension of A is 2
	//condition number is equal to norm of matrix A multiplied by norm of inverse of A
	//Inverse of 2x2 matrix is: (1/determinant)*[d -b;-c a]
	
	float ** invA;
		invA= new float *[2];
		invA[0]= new float[2];
		invA[1]= new float[2];
	if (n == 2) {
		float d = determinant (M_A, n);
		
		invA[0][0]=M_A[1][1]/d;
		invA[0][1]= M_A[0][1]/(-1*d);
		invA[1][0]= M_A[1][0]/(-1*d);
		invA[1][1]= M_A[0][0]/d;
		float condi1 = normINF(M_A);
		float condi2= normINF (invA);
		cout << "condition number of infinity is: " << condi1*condi2 << " \n"; //printing condition number of infinity
		float condo1 =normONE(M_A);
		float condo2 =normONE(invA);
		cout << "condition number of one is:" << condo1*condo2 ;       //printing condition number of one
		
	}

	f2.is_open();
	M_A[n]=new float[n];    //adding one column for vector b
	if(f2.is_open()){
		for(int k=0;k<n;k++){
		
			f2 >> M_A[k][n];             //add B to Augmented Matrix
		}
		
	}
	f2.close();
	/*cout << "Augmented matrix is:\n";
	for (int r=0;r<n;r++){
		cout << "\n";
		for(int c=0;c<n+1;c++){
			cout  << M_A[r][c]<<" ";   //print Augmented Matrix
		}
	}*/
	
	// If matrix A is singular, we cannot find unique solution. We should print error message and quit calculating
	// simple if else statement would do this. Det =0 means singular matrix
	// to consider machine precision, we can set condition of being singular to having absolute value of determinant smaller than 0.0000001
	// Else matrix is nonsingular, first we should find upper triangular matrix
	if( abs(determinant (M_A,n)) < 0.0000001)
		cout << "Matrix A is singular, cannot find unique solution";
	else{
		float ratio;
	int a=0;
	int b=0;
	int c=0;
	for(a=0;a<n-1;a++) {
		for(b=a+1;b<n;b++) {
			ratio= M_A[b][a]/M_A[a][a]; //ratio of pivot to element of following row
			
			for(c=0;c<n+1;c++) {
				M_A[b][c] -=M_A[a][c]*ratio; //by multiplication and substraction, we apply gauss elimination and make elements of following rows zero.
											 //after for loops, our upper triangular matrix is set.
			}
		}
	}
	/*
	for(int x=0;x<n;x++) {
		cout << "\n";
		for(int y=0;y<n+1;y++) {
			cout <<setw(15)<<setprecision(6)<< M_A[x][y]<< " ";  //printing upper triangular matrix
		}
	}
	*/
	
	//now we calculate solutions from upper triangular matrix by using backward substitution
	float s;
	float x[n];
	int i=0;
	int j=0;
	cout << "\nSolution is: \n";
	for(i=n-1; i>=0; i--)
	{
		s=0;
		for(j=i+1; j<n; j++)
		s += M_A[i][j]*x[j];
		x[i]=(M_A[i][n]-s)/M_A[i][i];
		
	}
	for(int g=0;g<n;g++) {
		cout<< x[g] << " \n";  //printing solutions
	}
	// let's write solution to x.txt file
	ofstream f3;
	f3.open("x.txt");
	for(i=0;i<n;i++) {
		f3 << x[i] <<" \n";
	}
	f3.close();
		
		
	}

return 0;



}
