#include <stdio.h>

//Write a program to calculate power using while & for loop
int power_while(int num, int extent)
{
	int power_num = num;

	while (extent > 1)
	{
		power_num *= num;
		--extent;
	}

	return extent > 0 ? power_num : 0;
}

int power_for(int num, int extent)
{
	if (extent == 1)
		return num;

	else if (extent != 0 && num != 0) 
		for (int x = 1, power_num = num; x <= extent; x++) {
			power_num *= num;

			if (x == extent - 1)
				return power_num;
		} 

	else
		return 0;
}

//Write a program to print the number days in the months using switch statement.
void check_month(int month, int year)
{
	int day = 0;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		day = 31;		
		break;
	case 2:
		day = year % 4 ? 28 : 29;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		day = 30;
	default:
		break;
	}

	day && year >= 0 ? 
		printf("This month has a %d day on the year\n", day) :
		printf("You are mistaken when input the date, Bye! \n");
	return;
}

//Write a program to check uppercase or lowercase alphabets.
void check_literals(char a)
{
	(a <= 'Z' && a >= 'A') || (a >= 'a' && a <= 'z') ?
		a <= 'Z' ?
		printf("%c is Upper case \n", a) :
		printf("%c is lower case \n", a)
		: printf("\n The %c is not a letter\n", a);

	return;
}

int main(void) 
{
	int num, extent;
	printf("Please, enter the digital and extent: \n");
	int check_input = scanf_s("%d %d", &num, &extent);
	if (check_input != 2) {
		printf("Error: Invalid input\n");
	}
	else {
		printf("By 'for' the number: %d, to the power: %d, is equal to: %d \n", num, extent, power_for(num, extent));
		printf("By 'while' the number: %d, to the power: %d, is equal to: %d \n", num, extent, power_while(num, extent));
	}


	char letter;
	printf("Please, enter the letter\n");
	int check_letter = scanf(" %c", &letter);
	if (check_letter != 1) {
		printf("Error: Invalid input\n");
	}
	else {
      check_literals(letter);
	}

	int month, year;
	printf("Please, enter the month and year: \n");
	int check_month_year = scanf_s("%d  %d", &month, &year);
	if (check_month_year != 2) {
		printf("Error: Invalid input\n");
	}
	else {
      check_month(month, year);
	}
	

	return 0;
}