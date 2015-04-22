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

char * factor(char *f){

	int n = atoi(f);
	char * str = (char *)malloc(MAX_SIZE); 

	//CHECK IF n IS AN INTEGER

	// Print the number of 2s that divide n
	while (n%2 == 0){
		sprintf(str, "%d\n", 2);
		//printf("%d\n", 2);
		n = n/2;
	}
 
	// n must be odd at this point.  So we can skip one element (Note i = i +2)
	int i;
	for (i = 3; i <= sqrt(n); i = i+2){
		// While i divides n, print i and divide n
		while (n%i == 0){
			sprintf(str, "%d\n", i);
			// printf("%d\n", i);
			n = n/i;
		}
	}
 
	// This condition is to handle the case whien n is a prime number
	// greater than 2
	if (n > 2)
		sprintf(str, "%d\n", n);
		// printf ("%d\n", n);

	return str;
}

//TODO fix this 
//prints 0 1 2 3... should print 0 1 1 2 3 5
char * fib(char * f){

	double lim = atof(f);

	int x = 0;
	int y = 1;
	int z = 0; 
	int count = 3; //by the time count is incremented the first 3 nums of seq will be printed
	char * str = (char *)malloc(MAX_SIZE); 

	//check to see if lim is an integer
	if(roundf(lim) == lim){


		
	} else {
		printf("lim is: %f.\t", lim); //testing
		// printf("Argument must be an integer.\n");
		return "Argument must be an integer.\n";	
	}

	//print 0 and 1 to start sequence
	printf("%d\n", x);
	printf("%d\n", y);

	while(count <= lim){
		
		z = x + y;

		sprintf(str,"%d\n",z);
		// printf("%d\n", z);

		if(count % 2 == 0){
			y = z;
		} else {
			x = z;
		}

		count++;
	}
	return str;
}

char * add(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	sprintf(f, "%.2f\n", (x+y));
	// printf("%.2f\n", (x + y));
	return f;
}

char * subtract(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	sprintf(f, "%.2f\n", (x - y));
	// printf("%.2f\n", (x - y));
	return f;
}

char * multiply(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	sprintf(f, "%.2f\n", (x * y));
	// printf("%.2f\n", (x * y));
	return f;
}

char * divide(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * f = (char *)malloc(MAX_SIZE); 

	if(b == 0){
		// printf("Cannot divide by 0.\n");
		return "Cannot divide by 0.\n";
	}

	sprintf(f, "%.2f\n", (x / y));
	// printf("%.2f\n", (x / y));
	return f;
}

char * exponent(char *a, char *b){

	double x = atof(a);
	double y = atof(b);
	char * str = (char *)malloc(MAX_SIZE); 

	sprintf(str, "%f\n", pow(x,y));
	// printf("%.2f\n", pow(x,y));

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

// int main(void){
// 	// factor("223092870");
// 	fib("10");
// 	return 0;
// }
