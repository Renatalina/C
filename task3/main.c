#include <stdio.h>

int set_bits(unsigned char first, unsigned char mask)
{
	return first | mask;
}

void check_bits(unsigned char first, unsigned char mask)
{
	if ((first & mask) == mask)
	{
		printf("Bit 2 is on\n");
	}
	else
	{
		printf("Bit 2 is off\n");
	}
}

int clear_bits(unsigned char first, unsigned char mask)
{
	return first & mask;
}

int toggle_bits(unsigned char first, unsigned char mask) 
{
	return first ^ mask;
}

//Write a function that determines whether the transmitted integer parameter is even and odd
void check_odd_or_even(int var)
{
	if (var & 1)
		printf("The digital is odd");
	else
		printf("The digital is even");
}

int main(void)
{
	 unsigned char var = 5;
	 unsigned char mask = 4;

	 check_bits(var, mask);

	 int set = set_bits(var, mask);
	 printf("set bit %d\n", set);

	 int clear = clear_bits(var, mask);
	 printf("clear bit %d\n", clear);

	 int toggle = toggle_bits(var, mask);
	 printf("Toggle bit %d\n", toggle);	

	 int check_digital;
	 int count = scanf("%d", &check_digital);
	 check_odd_or_even(check_digital);

	 return 0;
}