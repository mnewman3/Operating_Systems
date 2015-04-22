#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* math operations */
void factor(char *);
void fib(char *);
void add(char *a, char *b);
void subtract(char *a, char *b);
void multiply(char *a, char *b);
void divide(char *a, char *b);
void exponent(char *a, char *b);

/* helpers */
int isPrime(int n);

void factor(char *f){

	int n = atoi(f);

	//CHECK IF n IS AN INTEGER

	// Print the number of 2s that divide n
	while (n%2 == 0){
		printf("%d\n", 2);
		n = n/2;
	}
 
	// n must be odd at this point.  So we can skip one element (Note i = i +2)
	for (int i = 3; i <= sqrt(n); i = i+2){
		// While i divides n, print i and divide n
		while (n%i == 0){
			printf("%d\n", i);
			n = n/i;
		}
	}
 
	// This condition is to handle the case whien n is a prime number
	// greater than 2
	if (n > 2)
		printf ("%d\n", n);
}

void fib(char * f){

	double lim = atof(f);

	int x = 0;
	int y = 1;
	int z = 0; 

	int count = 0;

	while(count < lim){
		printf("%d + %d = %d\n",x,y, z);

		z = x + y;

		if( count % 2 == 0 ){
			x = z;
		} else {
			y = z;
		}

		count++;
	}

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

	for(int i = 2; i <= lim; i++){
		if(num % i == 0){
			return 0;
		}
	}
	return 1;
}

int main(void){
	factor("223092870");
}
