#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for strtol()
#include <errno.h>  // for errno

void sum(void)
{
	char numbers[100];

	printf("Please, enter the stuck of numbers: \n");
	fgets(numbers, 100, stdin);

	int sum = 0, middle_sum = 0;

	int is_negative_num = 0;

	for (int x = 0; x < 100; x++) {

		int digital = (int)numbers[x] - 48;

		if (digital == -38) {
			sum += middle_sum;
			break;
		}
		else if (digital == -16) {
			sum += middle_sum;
			middle_sum = 0;
			is_negative_num = 0;
			continue;
		}

		if ((x != 0) && ((int)numbers[x - 1] - 48) != -16) {
			middle_sum *= 10;
		}

		if (digital == -3) {
			is_negative_num = 1;
		}
		else if (is_negative_num) {
			middle_sum -= digital;
		}
		else {
			middle_sum += digital;
		}
	}
	printf("Sum the whole numbers is : %d\n", sum);

	return;
}

void use_lib_sum(void) {

	char str[100];
	const char s[2] = " ";
	char* token;	
	int sum = 0;

	printf("Please, enter the stuck of numbers: \n");
	fgets(str, 100, stdin);

	token = strtok(str, s);

	while (token != NULL) {
		sum += atoi(token);
		token = strtok(NULL, s);
	}
	
	printf("Sum the whole numbers is : %d\n", sum);
	return;
}