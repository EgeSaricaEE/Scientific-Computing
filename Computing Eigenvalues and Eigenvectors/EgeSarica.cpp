#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iomanip>
#include <cmath> 
using namespace std;
int main( int argc, char *argv[] )  {
	ifstream f1 (argv[1]); //reading A.txt
	ifstream f2 (argv[2]); //reading Tolerance.txt
	if(argc !=4){
			cout<<"Error, check input files";
			return 0;
		}
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
	M_A = new float *[n+1];  
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
	float Acopy[n][n];
	//print matrix A
	//cout << "Matrix A is: \n";
	for(int i=0;i<n;i++){
		if (i !=0){
		//	cout << "\n";
		}
		for(int j=0;j<n;j++){
			Acopy[i][j]=M_A[i][j];
			//cout << M_A[i][j]<<" ";
		}
	}
	float tolerance;
if(f2.is_open()){
	f2 >> tolerance;
	f2.close();
}
	//NORMALIZED POWER ITERATION
	float xcopy[n];
	float temp, lambda_new, lambda_old;
	 int i,j, step=1;
	float x[n],x_new[n];
	 for(i=0;i<n;i++)
	 {
		  
		  x[i]=1;
		  xcopy[i]=x[i];
	 }
	lambda_old = 1;
	up:
	 for(i=0;i<n;i++)
	 {
		  temp = 0.0;
		  for(j=0;j<n;j++)
		  {
		   	temp = temp + M_A[i][j]*x[j];
		  }
		  x_new[i] = temp;
	 }
	 // Replacing x by x_new
	 for(i=0;i<n;i++)
	 {
	  	x[i] = x_new[i];
	 }
	 // Finding largest value from x
	 if(x[1]<0){
	 	lambda_new = fabs(x[1])*-1;
	 }else { lambda_new = fabs(x[1]);
	 }
	 for(i=1;i<n;i++)
	 {
		  if(fabs(x[i])>fabs(lambda_new))
		  {
		  	if(x[i]<0){
		  		lambda_new = fabs(x[i])*-1;
			  } else {
			  	lambda_new = fabs(x[i]);
			  }  	
		  }
	 }
	 // Normalization
	 for(i=0;i<n;i++)
	 {
	  	x[i] = x[i]/lambda_new;
	 }
	//Tolerance
	 if(fabs(lambda_new-lambda_old)>tolerance)
	 {
		  lambda_old=lambda_new;
		  step++;
		  goto up;
	 }
	float eiva;
	float eive[n];
	eiva=lambda_new;
	for(i=0;i<n;i++) {
		eive[i]=x[i];
	}
	cout << "Final computed eigenvalue is: " << eiva << "\n";
	cout << "Final computed eigenvector is:\n[";
	for (i=0;i<n-1;i++) {
			cout <<  eive[i] << " \n" ;
	}
	cout << eive[n-1]<<"]";
	//DEFLATION PART
	
	//for deflation, we will use eigenvalue and eigenvector of A those we computed above
	//We will create a matrix B, which is equal to A - (eigenvector)*(first row of A)/(one nonzero element of eigenvector)
	//Then, we will compute eigenvalue of B. This will be the second eigenvalue of original matrix A
	int k=1;
	/*
	for (i=0;i<n;i++) {
		if(eive[i] < 0.00000000001) {
			k=i+1;
		}
	}*/
	float B[n][n], C[n][n];
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			C[i][j]=eive[i]*Acopy[1][j]/eive[k];
			
		}
	}
//	cout << "Matrix B is: \n";
	for(i=0;i<n;i++) {
	//	cout <<"\n";
		for(j=0;j<n;j++) {
			B[i][j]=Acopy[i][j] - C[i][j];
	//		cout << B[i][j] << " ";
		}
	}
	//We created matrix B, now we should compute its eigenvalue. This will be the second eigenvalue of matrix A
	//NORMALIZED POWER ITERATION
	float temp2, lambda_new2, lambda_old2;
	int step2=1;
	float x_new2[10];
	lambda_old2 = 1;
	up2:
	 for(i=0;i<n;i++)
	 {
		  temp2 = 0.0;
		  for(j=0;j<n;j++)
		  {
		   	temp2 = temp2 + B[i][j]*xcopy[j];
		  }
		  x_new2[i] = temp2;
	 }
	 // Replacing x by x_new
	 for(i=0;i<n;i++)
	 {
	  	xcopy[i] = x_new2[i];
	 }
	 // Finding largest value from xcopy 
	 if(xcopy[1]<0){
	 	lambda_new2 = fabs(xcopy[1])*-1;
	 }else { lambda_new2 = fabs(xcopy[1]);
	 }
	 for(i=1;i<n;i++)
	 {
		  if(fabs(xcopy[i])>fabs(lambda_new2))
		  {
		  	if(xcopy[i]<0){
		  		lambda_new2 = fabs(xcopy[i])*-1;
			  } else {
			  	lambda_new2 = fabs(xcopy[i]);
			  }
		   	
		  }
	 }
	 // Normalization
	 for(i=0;i<n;i++)
	 {
	  	xcopy[i] = xcopy[i]/lambda_new2;
	 }
	 //Tolerance
	 if(fabs(lambda_new2-lambda_old2)>tolerance)
	 {
		  lambda_old2=lambda_new2;
		  step2++;
		  goto up2;
	 }
	cout << "\nSecond eigenvalue is: " << lambda_new2;	
	ofstream f3 (argv[3]);
	if (f3.is_open()) {
	f3 << "Eigenvalue #1: " << eiva <<" \n";
	for(i=0;i<n;i++) {
		f3 << eive[i] <<" \n";
	}	
	f3 << "Eigenvalue #2: "<< lambda_new2;
	}
	f3.close();
	cout <<"\nOutput file is also generated";
	return 0;
}




