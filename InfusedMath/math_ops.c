#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* math operations */
void factor(char *a, char *b);
void fib(char *f);
void add(char *a, char *b);
void subtract(char *a, char *b);
void multiply(char *a, char *b);
void divide(char *a, char *b);
void exponent(char *a, char *b);

/* helpers */
int isPrime(int n);

void factor(char *a, char *b){

}

void fib(char * f){

	double lim = atof(f);

	//check to see if lim is an integer
	if(roundf(lim) == lim){
		
	} else {
		printf("lim is: %f.\t", lim); //testing
		printf("Argument must be an integer.\n");
		return;	
	}
}

void add(char *a, char *b){

	double x = atof(a);
	double y = atof(b);

	printf("%.2f\n", (x + y));

}

void subtract(char *a, char *b){

	double x = atof(a);
	double y = atof(b);

	printf("%.2f\n", (x - y));
}

void multiply(char *a, char *b){

	double x = atof(a);
	double y = atof(b);

	printf("%.2f\n", (x * y));

}

void divide(char *a, char *b){

	double x = atof(a);
	double y = atof(b);

	if(b == 0){
		printf("Cannot divide by 0.\n");
		return;
	}

	printf("%.2f\n", (x / y));

}

void exponent(char *a, char *b){

	double x = atof(a);
	double y = atof(b);

	printf("%.2f\n", pow(x,y));

}

/* returns 1 if argument is prime and 0 otherwise */
int is_prime(int num){
	if(num <= 1)
		return 0;

	if(num == 2)
		return 1;

	int lim = sqrt(num)+1;
	
	int i;
	for(i = 2; i <= lim; i++){
		if(num % i == 0){
			return 0;
		}
	}
	return 1;
}

// int main(void){

// 	fib("5.777");

// 	return 0;
// }
