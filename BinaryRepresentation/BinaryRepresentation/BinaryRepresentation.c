#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>

#define _CRT_SECURE_NO_WARNINGS

bool comparingTwoArrays(bool firstArray[], bool secondArray[], bool arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        if (firstArray[i] != secondArray[i]) {
            return false;
        }
    }
    return true;
}

void printBoolArray(bool boolArray[], int boolArrayLength) {
    for (int i = 0; i < boolArrayLength; ++i) {
        printf("%d", boolArray[i]);
    }
}

int exponentiationLogTime(int baseOfDegree, int exponent) {
    int result = 1;

    if (exponent == 0) {
        return result;
    }
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= baseOfDegree;
        }
        exponent /= 2;
        baseOfDegree *= baseOfDegree;
    }

    return result;
}

void binarySum(bool binaryFirstNumber[], bool binarySecondNumber[], bool binarySumArray[]) {
    bool theAdditionalTerm = 0;
    for (int i = 31; i >= 0; --i) {
        bool oneAndZero = (binaryFirstNumber[i] && !binarySecondNumber[i]) || (!binaryFirstNumber[i] && binarySecondNumber[i]);
        if (!binaryFirstNumber[i] && !binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 0;
                binarySumArray[i] = 1;
            } 
            else {
                binarySumArray[i] = 0;
            }
        }
        if (binaryFirstNumber[i] && binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 1;
            }
            else {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            }
        }
        if (oneAndZero) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            }
            else {
                binarySumArray[i] = 1;
            }
        }
    }
}

int conversionToDecimal(bool binaryNumber[]) {
    if (binaryNumber[0]) {
        int decimalNumber = -1;

        bool minusOne[32] = { 1 };
        binarySum(binaryNumber, minusOne, binaryNumber);
        for (int i = 1; i < 32; ++i) {
            decimalNumber -= !binaryNumber[i] * exponentiationLogTime(2, 31 - i);
        }
        return decimalNumber;
    } else {
        int decimalNumber = 0;

        for (int i = 1; i < 32; ++i) {
            decimalNumber += binaryNumber[i] * exponentiationLogTime(2, 31 - i);
        }
        return decimalNumber;
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
    char strFirstNumber[100];
    char strSecondNumber[100];
    char* endptrFirstNumber = NULL;
    char* endptrSecondNumber = NULL;
    bool errorCode = false;
    errno = 0;

    setlocale(LC_ALL, "Rus");

    printf("Введите первое число:\n");
    scanf("%s", strFirstNumber); 
    *firstNumber = (int)strtol(strFirstNumber, &endptrFirstNumber, 10);

    printf("Введите второе число:\n");
    scanf("%s", strSecondNumber);
    *secondNumber = (int)strtol(strSecondNumber, &endptrSecondNumber, 10);

    if (errno == ERANGE) {
        printf("Ошибка ввода");
        errorCode = true;
        return errorCode;
    }

    if (*endptrFirstNumber != '\0' || *endptrSecondNumber != '\0') {
        printf("Ошибка ввода");
        errorCode = true;
        return errorCode;
    }

    return errorCode;
}

bool testGetBinaryNumber() {
    int positiveNumber = 2048;
    int negativeNumber = -1025;
    bool positiveNumberArray[32] = { 0 };
    positiveNumberArray[20] = 1;
    bool negativeNumberArray[32] = { 1 };
    negativeNumberArray[21] = 0;
    bool theResultIsForThePositive[32] = { 0 };
    bool theResultIsForTheNegative[32] = { 0 };
    getBinaryNumber(positiveNumber, theResultIsForThePositive);
    getBinaryNumber(negativeNumber, theResultIsForTheNegative);

    return comparingTwoArrays(positiveNumberArray, theResultIsForThePositive, 32) && comparingTwoArrays(negativeNumberArray, theResultIsForTheNegative, 32);
}

int main(void) {
    int firstNumber = -1;
    int secondNumber = -1;
    int decimalSumNumber = -1;
    bool binaryFirstNumber[32] = { 0 };
    bool binarySecondNumber[32] = { 0 };
    bool binarySumArray[32] = { 0 };

    bool errorCode = false;

    setlocale(LC_ALL, "Rus");

    if (!testGetBinaryNumber()) {
        printf("Тест getBinaryNumber не пройден");
        errorCode = true;
        return errorCode;
    }

    errorCode = userInput(&firstNumber, &secondNumber);
    if (errorCode) {
        return errorCode;
    }
    //if ((firstNumber > INT_MAX - secondNumber) || (firstNumber + secondNumber < INT_MIN)) {
    //    printf("Переполнение стека");
    //    errorCode = true;
    //    return errorCode;
    //}

    getBinaryNumber(firstNumber, binaryFirstNumber);
    getBinaryNumber(secondNumber, binarySecondNumber);
    binarySum(binaryFirstNumber, binarySecondNumber, binarySumArray);

    printf("Двоичное представление первого числа в дополнительном коде:\n");
    printBoolArray(binaryFirstNumber, 32);
    printf("\nДвоичное представление второго числа в дополнительном коде:\n");
    printBoolArray(binarySecondNumber, 32);
    printf("\nДвоичная сумма:\n");
    printBoolArray(binarySumArray, 32);
    decimalSumNumber = conversionToDecimal(binarySumArray);
    printf("\nДесятичная сумма:\n%d", decimalSumNumber);



    return errorCode;
}