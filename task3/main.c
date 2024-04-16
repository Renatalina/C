#include <stdio.h>

int set_bit(unsigned char first, unsigned char mask)
{
	return first | mask;
}

void check_bit(unsigned char first, unsigned char mask)
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

int clear_bit(unsigned char first, unsigned char mask)
{
	return first & mask;
}

int toggle_bit(unsigned char first, unsigned char mask) 
{
	return first ^ mask;
}

//Write a function that determines whether the transmitted integer parameter is even and odd
void check_odd_or_even(int var)
{
	if (var % 2)
		printf("The digital is odd");
	else
		printf("The digital is even");
}

int main(void)
{
	 unsigned char var = 5;
	 unsigned char mask = 4;

	 check_bit(var, mask);

	 int set = set_bit(var, mask);
	 printf("set bit %d\n", set);

	 int clear = clear_bit(var, mask);
	 printf("clear bit %d\n", clear);

	 int toggle = toggle_bit(var, mask);
	 printf("Toggle bit %d\n", toggle);	

	 int check_digital;
	 int count = scanf("%d", &check_digital);
	 check_odd_or_even(check_digital);

	 return 0;
}