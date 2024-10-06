#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

int main(void) {
    char strFirstNumber[10];
    char strSecondNumber[10];
    char* endptrFirstNumber = NULL;
    char* endptrSecondNumber = NULL;

    int firstNumber = -1;
    int secondNumber = -1;
    bool errorCode = 0;

    setlocale(LC_ALL, "Rus");

    printf("Введите первое число:\n");
    scanf("%s", strFirstNumber);
    firstNumber = (int)strtol(strFirstNumber, &endptrFirstNumber, 10);

    printf("Введите второе число:\n");
    scanf("%s", strSecondNumber); 
    secondNumber = (int)strtol(strSecondNumber, &endptrSecondNumber, 10);

    if (*endptrFirstNumber != '\0' || *endptrSecondNumber != '\0') {
        printf("Ошибка ввода");
        errorCode = 1;
        return errorCode;
    }

    return errorCode;
}