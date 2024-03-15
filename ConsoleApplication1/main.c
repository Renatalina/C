#include <stdio.h>
#include <windows.h>


int farengate(void) {
	
	char greetings[] = "Enter a number, which you would like to convert from Fahrenheits to Celsius:";
	int fahrenheits;

	printf("\n%s\n", greetings);
	scanf_s("%d", &fahrenheits);

	float convertToFloat = (fahrenheits - 32)*5;
	float celsius = convertToFloat / 9;

	printf("Its Celsius equivalent is %.3f", celsius);

	return 0;
}

int nameOfFile(int argc, char* argv[]) {

	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	char task1[] = "Task 1: Write a program which converts Fahrenheits to Celsius. The program should ask a user to enter a number in Fahrenheits and print its Celsius equivalent";
	char task2[] = "Task 2: Write a program which prints a name of its binary file.";

	printf("%s\n", task1);
	farengate();

	printf("\n\n\n%s\n", task2);
	nameOfFile(argc, argv);


	printf("\nName from arguments: %s", argv[0]);
		
	return 0;
}