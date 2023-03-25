This program finds approximate solution of f(x)=0 with 3 methods: Secant, Bisection and Hybrid.
First, secant method is applied and x value and number of iteration is printed.
Then, bisection method is applied and x value and number of iteration is printed.
Lastly, hybrid method is applied and x value and number of iteration is printed.
In hybrid method, 2 steps of bisection is done first. Then these values are used in secant method to complete the solution.

To run the program, give the coefficients of f, initial guesses: x0, x1 and tolerance value.
First, program will calculate f(x0) and f(x1) according to the input coefficients.
Then, 3 different algorithm will be used to compute f(x)=0. The working principle of methods are straight-forward.

Bisection method: All that really
matters is that the function values differ in sign at the two points. We evaluate
the function at the midpoint m = a + (b - a)=2 = 2 and and that f(m) has the
opposite sign from f(a), so we retain the first half of the initial interval by setting
b = m. We then repeat the process until the bracketing interval isolates the root of
the equation as accurately as desired.*

Secant method: We evaluate the function at each of two starting guesses, x0 and x1, and
take the next approximate solution to be the zero of the straight line fitting the
two function values. We then repeat the process using this new value and the more
recent of our two previous values, so only one new function evaluation is needed per
iteration.**

*Michael T. Heath, Scientific Computing An Introductory Survey, Revised Second Edition1
**Michael T. Heath, Scientific Computing An Introductory Survey, Revised Second Edition