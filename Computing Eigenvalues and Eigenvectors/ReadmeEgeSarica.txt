The main goal of this program is calculating dominant eigenvalue and corresponding eigenvector of matrix A.
Then, using these value, program calculates second eigenvalue of matrix A and writes the results to output file.

This program takes 3 command line arguments as input. First one is A.txt which contains Matrix A.
Second one is tolerance, third one is Out.txt file which is completed by the program.

Matrix A is stored using dynamic memory. Normalized power iteration is used to compute
dominant eigenvalue and corresponding eigenvector. Then, deflation is used to compute
second eigenvalue of A. To find second eigenvalue, a new matrix called B is created.
B=A-(1/up)*u*at
u is the eigenvector that computed before. up is one nonzero element of that eigenvector.
at is simply the first row of matrix A.
Then, we calculate the eigenvalue of B and that eigenvalue is the second eigenvalue of
original matrix A.

Finally; dominant eigenvalue, corresponding eigenvector and second eigenvalue of matrix A are written to
Out.txt file. 

To run the program, similar input can be given as:

A.txt Tolerance.txt Out.txt as input in cmd screen.

A.txt:
3.14 1.59 2.65 3.58
9.79 3.23 8.46 2.64
3.38 3.27 9.50 2.88
4.19 7.16 9.39 9.37

Tolerance:
0.000001

Output of this input is:
Final computed eigenvalue is: 20.488
Final computed eigenvector is: 
[0.348061
0.622149
0.554319
1]
Second eigenvalue is: 3.91405

