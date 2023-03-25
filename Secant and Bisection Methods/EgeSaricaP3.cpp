#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iomanip>
#include <cmath> 
#include<stdlib.h>
using namespace std;

//Function to calculate f(x)
double fx (double row[], double x0, int m) {

	int k=m-4;
	double temp0=0;

	for (int i=0;i<m-3;i++) {
		
		temp0= temp0 + row[i]*pow(x0,k);
		k--;
	}
	
	return temp0;
}
//Function for secant method
double secant (double row[],int m) {

	double k2;
	int s=1;
	double k0=row[m-3];
	double k1=row[m-2];
	double f0;
	double f1;
	double f2;
	double e=row[m-1];
	//calculations must be done until f(x) is smaller than tolerance value.
	do{
		f0=fx(row,k0,m);
		f1=fx(row,k1,m);
		if (f0==f1)
		cout << "Error, check x0 and x1\n";
		//calculation starts
		k2= k1 - (k1 - k0) * f1/(f1-f0);
		f2=fx(row,k2,m);
		
		k0 = k1;
		  f0 = f1;
		  k1 = k2;
		  f1 = f2;

		  s = s + 1;
		
		
		
	}while(fabs(f2)>e);
	
	cout << "\nNumber of secant iteration is: " << s<<"\n";
	return k2;
	
}

//Function for bisection method
double bisection (double row[], int m) {
	double k2;
	int s=1;
	double k0=row[m-3];
	double k1=row[m-2];
	double f0;
	double f1;
	double f2;
	double e=row[m-1];
	f0=fx(row,k0,m);
	f1=fx(row,k1,m);
		//calculations must be done until f(x) is smaller than tolerance value.
		 do 
	 {
			//calculation starts
		  k2 = (k0 + k1)/2;
		  f2 = fx(row,k2,m);

		 

		  if( f0 * f2 < 0)
		  {
			   k1 = k2;
		  }
		  else
		  {
			   k0 = k2;
		  }
		  s = s + 1;
	 }while(fabs(f2)>e);
	
	cout<<"\n\nNumber of bisection iteration is: " << s;
	return k2;
}

//Function for hybrid method
double hybrid (double row[],int m){
	double k2;
	int s=1;
	double k0=row[m-3];
	double k1=row[m-2];
	double f0;
	double f1;
	double f2;
	double e=row[m-1];
	f0=fx(row,k0,m);
	f1=fx(row,k1,m);
	//We apply 2 steps of bisection, then move on to secant method
	//This is done by making condition s<3, then giving current values to secant function
	 do 
	 {

		  k2 = (k0 + k1)/2;
		  f2 = fx(row,k2,m);

		 

		  if( f0 * f2 < 0)
		  {
			   k1 = k2;
		  }
		  else
		  {
			   k0 = k2;
		  }
		  s = s + 1;
	 }while(s<3);
	 //2 steps of bisection method is applied, now we give these values to secant method function
	 row[m-3]=k0;
	 row[m-2]=k1;
	 double ress=secant(row,m);

	return ress;
	
}



int main( int argc, char* argv[] )
{
	
	//First, we find the number of arguments entered
  int n=0;
  int i;
  //argv[0] is the name of file
    for (i = 1; i < argc; ++i) {
    	n++;
 
	}

        
    //We create dynamic memory and store the inputs here
    double *Coef;  
	Coef = new double [n]; 
	
	for (i=0;i<n;i++) {
		Coef[i] =  atof (argv[i+1]);
	
	}
	
    double x0 = Coef[n-3];
	double x1 = Coef[n-2];
	double tole = Coef[n-1];
	double f=fx(Coef,x1, n); 
	if (x0>x1) {
		cout << "x0 cannot be bigger than x1, please enter guesses as x1>x0\n";
	} else {
	//This is for calculating x with secant method
    double res=secant(Coef,n);
    cout << "Secant method result is: " << res;
    //This is for calculating x with bisection method
    double res2=bisection(Coef,n);
    cout << "\nBisection method result is " << res2<<"\n";
    //This is for calculating x with hybrid method
    double hres=hybrid(Coef,n);
    cout << "Total number of iteration is 2 more than the secant iteration. 2 iteration has done by bisection method\n";
	cout << "Hybrid method result is :" << hres <<"\n";   
	}

  
    return 0;
}
