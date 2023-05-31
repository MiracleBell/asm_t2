#include <iostream>
#include <stdio.h>
#include <math.h>


const double TWO_POINT_EPS = 1E-2;
const double FIVE_POINT_EPS = 1E-5;

double myCos(double x, double TWO_POINT_EPS);
void test(double x);
void test(double value, double EPS);
double readDoubleFromCommandLine();


int main(){
	test(1);
	test(-1);
	test(0.5);
	test(1.5);
	test(2);
	test(-2);
	test(5);
	test(-5);
	test(10);	
	test(50);
}


double readDoubleFromCommandLine() {
	double number;
	printf("Enter value: ");
	scanf_s("%lf", &number);
	return number;
}
// sum((-1)^n/(2n)!*x^(2n))

/*double Cos(double x) {
	int i;
	double s = 1, n = 0, a = 1;

	for (i = 1; i <= 10; i++)
	{
		a = -(a*x*x) / ((2 * n + 2)*(2 * n + 1));
		s = s + a;
		n++;
	}

	return s;
}*/


double myCos(double x, double EPS) {
	double result;

	__asm {
		finit
		fldpi
		fadd st(0), st(0)

		fld qword ptr x
		fld1
		fadd; x++
		fdiv qword ptr x
		frndint; округление до ближайшего целого значени€

		fmul st(0), st(1)
		fld qword ptr x
		fsub
		fxch st(2); –езультат на вершине стека
		fstp st(0)
		fstp st(0)

		fmul st(0), st(0)
		fld qword ptr EPS
		fxch st(1)
		fldz
		fld1
		fld1

		LOOP_ITERATION : ; начинает цикл итераций дл€ вычислени€ значени€ косинуса.
					  fchs; мен€ет знак
					  fmul st(0), st(3); перемножим первый и третий эл - т
					  fld1
					  faddp st(3), st(0); сложение двух верхних значений
					  fdiv st(0), st(2); деление верхнего эл - та на знаменатель
					  fld1
					  faddp st(3), st(0)
					  fdiv st(0), st(2)
					  fadd st(1), st(0)
					  fld st(0)
					  fabs
					  fcomp st(5)
					  fstsw ax; значение ax сравниваетс€ с флагами условий
			sahf
			ja LOOP_ITERATION

			fld st(1)
			fstp[result]
	}

	return result;
}


void test(double value) {	
	printf("          TEST\n");
	printf("==========================\n");	
	test(value, TWO_POINT_EPS);
	test(value, FIVE_POINT_EPS);
	printf("\n\n");
}

void test(double value, double EPS) {
	double res = myCos(value, EPS);
	printf("EPS = %f\n", EPS);
	printf("value = %f\n", value);
	printf("Custom function %f\n", res);
	printf("Standard function %f\n", cos(value));
	printf("==========================\n");
}