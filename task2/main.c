#include <stdio.h>

#define first_variable_int 5
#define first_variable_long 5L
#define first_variable_long_long 5LL
#define first_variable_double 5.0
#define first_variable_float 5.0F
#define first_variable_long_double 5.0L
#define first_variable_char "x"

int main(void)
{
	const int second_variable_int = 5;
	const long int second_variable_long = 5;
	const long long int second_variable_long_long = 5;
	const double second_variable_double = 5.0;
	const float second_variable_float = 5.0;
	const long double second_variable_long_double = 5.0;
	const char second_variable_char = 'x';

	typedef enum  {
		third_int = 5,
		third_long_int = 5L,
		third_long_long = 5LL,
		third_double
	}third_variable;

	printf("\nvalue %zu\n", sizeof(first_variable_int));
	printf("value %zu\n", sizeof(first_variable_long));
	printf("value %zu\n", sizeof(first_variable_long_long));
	printf("value %zu\n", sizeof(first_variable_double));
	printf("value %zu\n", sizeof(first_variable_float));
	printf("value %zu\n", sizeof(first_variable_long_double));
	printf("value %zu\n", sizeof(first_variable_char));	

	printf("\nvalue %zu\n", sizeof(second_variable_int));
	printf("value %zu\n", sizeof(second_variable_long));
	printf("value %zu\n", sizeof(second_variable_long_long));
	printf("value %zu\n", sizeof(second_variable_double));
	printf("value %zu\n", sizeof(second_variable_float));
	printf("value %zu\n", sizeof(second_variable_long_double));
	printf("value %zu\n", sizeof(second_variable_char));

	printf("\nvalue %zu\n", sizeof(third_variable));
	printf("value %zu\n", sizeof(third_variable));
	printf("value %zu\n", sizeof(third_variable));
	printf("value %zu\n", sizeof(third_variable));
	
	 printf("\nvalue %zu\n", sizeof(5));
	 printf("value %zu\n", sizeof(5L));
	 printf("value %zu\n", sizeof(5LL));
	 printf("value %zu\n", sizeof(5.0));
	 printf("value %zu\n", sizeof(5.0F));
	 printf("value %zu\n", sizeof(5.0L));
	 printf("value %zu\n", sizeof("x"));
	
	 return 0;
}