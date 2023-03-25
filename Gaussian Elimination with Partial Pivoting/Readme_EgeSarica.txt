This program aims to solve Ax=b by using Gauss elimination and backward substitution.

If you are using Dev-C++, by clicking Execute=>Parameters, you can give .txt files as inputs to program.
The program will take these command line arguments, read them and store the matrix and vector
in dynamically allocated memory.

Before starting calculation, the program will check whether the matrix A is singular or not by controling its determinant.
Function called determinant makes the calculation, taking matrix A and its dimension as inputs.
If determinant of a matrix is zero, this means that matrix is zero. Considiring machine precision, if absolue value of determinant is
smaller than 0.0000001, program will detect that matrix A is singular and print an error message, skipping the calculation of Ax=b.

If the matrix is 2x2, the program will compute and print the condition numbers of 1 and infinity. This process is done by using functions named normINF and normOne.
For example, A=[1.000 1.000;1.000 1.001] and b1=[2.000;2.000] and b2=[2.000;2.001]
In this case, we see the condition numbers are much bigger than 1. So, a very small change in b, just incrementing one element by 0.001 causes a lot more change in solution.
Solution of Ax=b1 is [2 0] yet solution of Ax=b2 is [1 1]. A change of 0.001 caused this whole change.

After these steps, the program finally begins Gauss elimination process. Gauss elimination is done by determining pivots and making elements which are in the same column with pivot zero.
Of course after making the element zero, we should multiply the rest of the row with corresponding elements ratio and substract for proper calculation steps.
After elimination is completed properly, we have our upper triangular matrix. In upper triangular matrix, elements under pivots are zero and this makes calculation very easy.
In upper triangular matrix, the final pivot, pivot n, gives us the solution xn easily. Pivot is the scalar of xn and pivot n*xn equals to the element at the nxn+1.
From now on, we can compute full solution using backward substitution. We know the value of xn, we have scalar of x n-1 at n-1 pivot position and sum of them are equal to n-1xn+1 th element.
Backward substitution process goes on like this and gives us the full solution of Ax=b.

Then, the solution of Ax=b is printed on screen. Also you can find solution at x.txt file.