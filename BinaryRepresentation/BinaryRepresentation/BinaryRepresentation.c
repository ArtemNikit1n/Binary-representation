#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

void printBoolArray(bool boolArray[], int boolArrayLength) {
    for (int i = 0; i < boolArrayLength; ++i) {
        printf("%d", boolArray[i]);
    }
}

void getBinaryNumber(int decimalNumber, bool binaryNumber[]) {
    for (int i = 0; i < 32; ++i) {
        if ((decimalNumber) & (1 << i)) {
            binaryNumber[31 - i] = 1;
        } else {
            binaryNumber[31 - i] = 0;
        }
    }
}

bool userInput(int *firstNumber, int *secondNumber) {
    char strFirstNumber[10];
    char strSecondNumber[10];
    char* endptrFirstNumber = NULL;
    char* endptrSecondNumber = NULL;
    bool errorCode = 0;

    setlocale(LC_ALL, "Rus");

    printf("Введите первое число:\n");
    scanf("%s", strFirstNumber);
    *firstNumber = (int)strtol(strFirstNumber, &endptrFirstNumber, 10);

    printf("Введите второе число:\n");
    scanf("%s", strSecondNumber);
    *secondNumber = (int)strtol(strSecondNumber, &endptrSecondNumber, 10);

    if (*endptrFirstNumber != '\0' || *endptrSecondNumber != '\0') {
        printf("Ошибка ввода");
        errorCode = 1;
        return errorCode;
    }

    return errorCode;
}

int main(void) {
    int firstNumber = -1;
    int secondNumber = -1;
    bool binaryFirstNumber[32] = { 0 };
    bool binarySecondNumber[32] = { 0 };

    bool errorCode = 0;

    errorCode = userInput(&firstNumber, &secondNumber);

    setlocale(LC_ALL, "Rus");

    getBinaryNumber(firstNumber, binaryFirstNumber);
    getBinaryNumber(secondNumber, binarySecondNumber);

    printf("Двоичное представление первого числа в дополнительном коде:\n");
    printBoolArray(binaryFirstNumber, 32);
    printf("\nДвоичное представление второго числа в дополнительном коде:\n");
    printBoolArray(binarySecondNumber, 32);

    //printf("Двоичная сумма в дополнительном коде:\n");
    //printTheBinaryNumber(secondNumber + firstNumber);
    //printf("Двоичная сумма:\n");

    return errorCode;
}