#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1024

/* math operations */
char * factor(char *);
char * fib(char *);
char * add(char *, char *);
char * subtract(char *, char *);
char * multiply(char *, char *);
char * divide(char *, char *);
char * exponent(char *, char *);

/* helpers */
int isPrime(int n);

//A function to print all prime factors of a given number n
char * factor(char * f){
	double test = atof(f);
	char * str = (char *)malloc(MAX_SIZE); 

	//check if positive number
	if(test < 0){
		sprintf(str, "%d\n", -1);
		test = fabs(test);
	}

	//CHECK IF n IS AN INTEGER
	if(ceilf(test) != test){
		printf("Factor must take an int.\n");
		free(str);
		return NULL;
	}

	int n = (int)test;
    // Print the number of 2s that divide n
	while (n%2 == 0){
		sprintf(str, "%d\n", 2);
		n = n/2;
	}
 
	// n must be odd at this point.  So we can skip one element (Note i = i +2)
	for (int i = 3; i <= sqrt(n); i = i+2){
	// While i divides n, print i and divide n
		while (n%i == 0){
			sprintf(str, "%d\n", i);
			n = n/i;
		}	
	}
 
	// This condition is to handle the case whien n is a prime number
	// greater than 2
	if (n > 2)
	sprintf(str, "%d\n", n);

	return str;
}

char * fib(char * n) {

	int first = 0, second = 1, next, c;
 	double lim = atof(n);

	//CHECK IF n IS AN INTEGER
	if( (ceilf(lim) != lim) || (lim <= 0) ){
		printf("Factor must take a positive int int.\n");
		return NULL;
	}

	char * str = (char *)malloc(MAX_SIZE);  

	for ( c = 1 ; c < lim+1 ; c++ ){
		if ( c <= 1 ){
			next = c;
      	} else {
			next = first + second;
			first = second;
			second = next;
		}
		sprintf(str,"%d\n",next);
   }

   return str; 
}

char * add(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	sprintf(f, "%g\n", (x+y));
	return f;
}

char * subtract(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	sprintf(f, "%g\n", (x - y));
	return f;
}

char * multiply(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	sprintf(f, "%g\n", (x * y));
	return f;
}

char * divide(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	if(y == 0){
		printf("Cannot divide by 0.\n");
		return NULL;
	}

	sprintf(f, "%g\n", (x / y));
	return f;
}

char * exponent(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * str = (char *)malloc(MAX_SIZE); 

	sprintf(str, "%g\n", pow(x,y));

	return str;
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
