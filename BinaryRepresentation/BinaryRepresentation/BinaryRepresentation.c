﻿#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

void binarySum(bool binaryFirstNumber[], bool binarySecondNumber[], bool binarySumArray[]) {
    bool theAdditionalTerm = 0;
    for (int i = 31; i >= 0; --i) {
        bool oneAndZero = (binaryFirstNumber[i] && !binarySecondNumber[i]) || (!binaryFirstNumber[i] && binarySecondNumber[i]);
        if (!binaryFirstNumber[i] && !binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 0;
                binarySumArray[i] = 1;
            } else {
                binarySumArray[i] = 0;
            }
        }
        if (binaryFirstNumber[i] && binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 1;
            } else {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            }
        }
        if (oneAndZero) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            } else {
                binarySumArray[i] = 1;
            }
        }
    }
}

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
    bool binarySumArray[32] = { 0 };

    bool errorCode = 0;

    errorCode = userInput(&firstNumber, &secondNumber);

    setlocale(LC_ALL, "Rus");

    getBinaryNumber(firstNumber, binaryFirstNumber);
    getBinaryNumber(secondNumber, binarySecondNumber);
    binarySum(binaryFirstNumber, binarySecondNumber, binarySumArray);

    printf("Двоичное представление первого числа в дополнительном коде:\n");
    printBoolArray(binaryFirstNumber, 32);
    printf("\nДвоичное представление второго числа в дополнительном коде:\n");
    printBoolArray(binarySecondNumber, 32);
    printf("\nДвоичная сумма в дополнительном коде:\n");
    printBoolArray(binarySumArray, 32);

    return errorCode;
}