#include <stdio.h>
#include <stdlib.h>
#include <time.h>


union Data {
    int i;
    char c;
};

int main ( void) {
union Data data; // объявляем переменную типа Data
data.i = 10; // храним целое число
printf("%d", data.i);
data.c = 'a'; // храним символ, значение i затирается
printf("%c", data.c);
printf("%c", data.i);

return 0;
}