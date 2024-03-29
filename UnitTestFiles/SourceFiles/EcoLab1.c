/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include <stdio.h>
#include <time.h>

#include "IEcoCalculatorX.h"
#include "IdEcoCalculatorA.h"

int int_cmp(const void *a, const void *b) {
    const int *pa = (const int *) a;
    const int *pb = (const int *) b;
    return *pa - *pb;
}

int char_cmp(const void *a, const void *b) {
    const char *pa = (const char *) a;
    const char *pb = (const char *) b;
    return *pa - *pb;
}

int decrease_int_cmp(const void *a, const void *b) {
    const int *pa = a;
    const int *pb = b;
    return *pb - *pa;
}

int string_cmp(const void *a, const void *b) {
    const char **pa = (const char **) a;
    const char **pb = (const char **) b;
    return len(*pa) - len(*pb);
}

int len(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown *pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1 *pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1 *pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1 *pIMem = 0;
    int size = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1 *pIEcoLab1 = 0;
    /* Указатель на интерфейс X */
    IEcoCalculatorX* pIX = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **) &pISys);
        if (result != 0 && pISys == 0) {
            /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **) &pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorA, (IEcoUnknown *) GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1,
                                          (void **) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void **) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**)(&pIX));
    if (result != 0 || pIX == 0) {
        printf("IID_IEcoCalculatorX not Found!\n");
        goto Release;
    }
    printf("Successfully IEcoCalculatorX initialized: %p\n", &pIX);
    printf("IEcoCalculatorX: Addition: 3 + 5 = %d\n", pIX->pVTbl->Addition(pIX, 3, 5));

    setlocale(LC_ALL, "Russian");

    // int array unit tests
    printf("Int array test:\n");
    printf("\nShell sort shell step\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestShellSortShellStepIntArray(size, pIEcoLab1);
    }

    printf("\nShell sort hibbard step\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestShellSortHibbardStepIntArray(size, pIEcoLab1);
    }

    printf("\nShell sort knuth step\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestShellSortKnuthStepIntArray(size, pIEcoLab1);
    }

    printf("\nQSort\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestQSortIntArray(size, pIEcoLab1);
    }

    // char array unit tests
    printf("Char array test:\n");
    printf("\nShell sort shell step\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestShellSortShellStepCharArray(size, pIEcoLab1);
    }

    printf("\nShell sort hibbard step\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestShellSortHibbardStepCharArray(size, pIEcoLab1);
    }

    printf("\nShell sort knuth step\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestShellSortKnuthStepCharArray(size, pIEcoLab1);
    }

    printf("\nQSort\n");
    for (size = 1000000; size <= 10000000; size += 1000000) {
        unitTestQSortCharArray(size, pIEcoLab1);
    }

    // String array unit tests
    printf("String array test:\n");
    printf("\nShell sort shell step\n");
    for (size = 1000; size <= 10000; size += 1000) {
        unitTestShellSortShellStepStringArray(size, pIEcoLab1);
    }

    printf("\nShell sort hibbard step\n");
    for (size = 1000; size <= 10000; size += 1000) {
        unitTestShellSortHibbardStepStringArray(size, pIEcoLab1);
    }

    printf("\nShell sort knuth step\n");
    for (size = 1000; size <= 10000; size += 1000) {
        unitTestShellSortKnuthStepStringArray(size, pIEcoLab1);
    }

    printf("\nQSort\n");
    for (size = 1000; size <= 10000; size += 1000) {
        unitTestQSortStringArray(size, pIEcoLab1);
    }

    Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

// unit tests int array

void unitTestShellSortHibbardStepIntArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    int *intArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    intArr = (int *) malloc(arraySize * sizeof(int));
    randomFillIntArray(intArr, arraySize);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortHibbardStep(pIEcoLab1, intArr, arraySize, sizeof(int), int_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

void unitTestShellSortShellStepIntArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    int *intArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    intArr = (int *) malloc(arraySize * sizeof(int));
    randomFillIntArray(intArr, arraySize);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortShellStep(pIEcoLab1, intArr, arraySize, sizeof(int), int_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

void unitTestShellSortKnuthStepIntArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    int *intArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    intArr = (int *) malloc(arraySize * sizeof(int));
    randomFillIntArray(intArr, arraySize);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortKnuthStep(pIEcoLab1, intArr, arraySize, sizeof(int), int_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

void unitTestQSortIntArray(int arraySize) {
    int *intArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    intArr = (int *) malloc(arraySize * sizeof(int));
    randomFillIntArray(intArr, arraySize);

    // Начало замера времени
    start = clock();
    qsort(intArr, arraySize, sizeof(int), int_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

// unit tests Char array

void unitTestShellSortHibbardStepCharArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    char *charArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    charArr = (char *) malloc(arraySize * sizeof(char));
    randomFillCharArray(charArr, arraySize);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortHibbardStep(pIEcoLab1, charArr, arraySize, sizeof(char), char_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

void unitTestShellSortShellStepCharArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    char *charArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    charArr = (char *) malloc(arraySize * sizeof(char));
    randomFillCharArray(charArr, arraySize);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortShellStep(pIEcoLab1, charArr, arraySize, sizeof(char), int_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

void unitTestShellSortKnuthStepCharArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    char *charArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    charArr = (char *) malloc(arraySize * sizeof(char));
    randomFillCharArray(charArr, arraySize);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortKnuthStep(pIEcoLab1, charArr, arraySize, sizeof(char), int_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

void unitTestQSortCharArray(int arraySize) {
    char *charArr;
    clock_t start, end;
    double cpu_time_used;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    charArr = (char *) malloc(arraySize * sizeof(char));
    randomFillCharArray(charArr, arraySize);

    // Начало замера времени
    start = clock();
    qsort(charArr, arraySize, sizeof(char), int_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}

// unit tests String array

void unitTestShellSortHibbardStepStringArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    char **stringArr;
    clock_t start, end;
    double cpu_time_used;
    int i = 0;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    stringArr = (char **) malloc(arraySize * sizeof(char *));
    randomFillStringArray(stringArr, arraySize, arraySize*2);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortHibbardStep(pIEcoLab1, stringArr, arraySize, sizeof(char *), string_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);

    for (i = 0; i < arraySize; i++) {
        free(stringArr[i]);
    }
}

void unitTestShellSortShellStepStringArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    char **stringArr;
    clock_t start, end;
    double cpu_time_used;
    int i = 0;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    stringArr = (char **) malloc(arraySize * sizeof(char *));
    randomFillStringArray(stringArr, arraySize, arraySize*2);
    
    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortShellStep(pIEcoLab1, stringArr, arraySize, sizeof(char *), string_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);

    for (i = 0; i < arraySize; i++) {
        free(stringArr[i]);
    }
    free(stringArr);
}

void unitTestShellSortKnuthStepStringArray(int arraySize, IEcoLab1 *pIEcoLab1) {
    char **stringArr;
    clock_t start, end;
    double cpu_time_used;
    int i = 0;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    stringArr = (char **) malloc(arraySize * sizeof(char *));
    randomFillStringArray(stringArr, arraySize, arraySize*2);

    // Начало замера времени
    start = clock();
    pIEcoLab1->pVTbl->ShellSortKnuthStep(pIEcoLab1, stringArr, arraySize, sizeof(char *), string_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);

    for (i = 0; i < arraySize; i++) {
        free(stringArr[i]);
    }
}

void unitTestQSortStringArray(int arraySize) {
    char **stringArr;
    clock_t start, end;
    double cpu_time_used;
    int i = 0;

    // Инициализация генератора случайных чисел
    srand(time(0));
    // Заполнение массивa рандомной информацией
    stringArr = (char **) malloc(arraySize * sizeof(char *));
    randomFillStringArray(stringArr, arraySize, arraySize*2);

    // Начало замера времени
    start = clock();
    qsort(stringArr, arraySize, sizeof(char *), string_cmp);
    // Конец замера времени
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);

    for (i = 0; i < arraySize; i++) {
        free(stringArr[i]);
    }
}

void printIntArray(int *arr, int size) {
    int i = 0;
    printf("Array: [ ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void printCharArray(char *arr, int size) {
    int i = 0;
    printf("Array: [ ");
    for (i = 0; i < size; i++) {
        printf("%c ", arr[i]);
    }
    printf("]\n");
}

void printStringArray(char **arr, int size) {
    int i = 0;
    printf("Array: [ ");
    for (i = 0; i < size; i++) {
        printf("'%s' ", arr[i]);
    }
    printf("]\n");
}

int generateRandomNumberRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

int generateRandomNumber() {
    return rand();
}

char generateRandomChar() {
    char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int length = strlen(chars);

    int randomIndex = rand() % length;

    return chars[randomIndex];
}

void randomFillIntArray(int *arr, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        arr[i] = generateRandomNumber();
    }
}

void randomFillCharArray(char *arr, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        arr[i] = generateRandomChar();
    }
}

char *generateRandomString(int size) {
    // Выделяем память для строки + 1 на символ окончания строки '\0'
    char *randomString = (char *) malloc((size + 1) * sizeof(char));
    for (int i = 0; i < size; i++) {
        randomString[i] = generateRandomChar();
    }
    // Добавляем символ окончания строки
    randomString[size] = '\0';
    return randomString;
}

void randomFillStringArray(char **arr, int size, int maxStringSize) {
    int i = 0;
    for (i = 0; i < size; i++) {
        arr[i] = generateRandomString(generateRandomNumberRange(1, maxStringSize));
    }
}