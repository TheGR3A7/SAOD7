#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

//В файле записаны фамилии студентов и их анкетные данные, включающие номера паспорта и зачетной книжки.Организовать два
//индексных файла для быстрого поиска информации по любому из этих номеров.

struct Student {
    char name[50];
    char passportNumber[20];
    char studentID[20];
};

// Структура для хранения индекса по номеру паспорта
struct PassportIndex {
    char passportNumber[20];
    int index;
};

// Структура для хранения индекса по номеру зачетной книжки
struct StudentIDIndex {
    char studentID[20];
    int index;
};

// Функция для последовательного поиска по номеру паспорта
int sequentialSearchByPassport(Student students[], int n, char passportNumber[])
{
    for (int i = 0; i < n; ++i) 
    {
        if (strcmp(students[i].passportNumber, passportNumber) == 0) 
            return i; // Найдено совпадение, возвращаем индекс
    }
    return -1; // Совпадение не найдено
}

// Функция для последовательного поиска по номеру зачетной книжки
int sequentialSearchByStudentID(Student students[], int n, char studentID[]) 
{
    for (int i = 0; i < n; ++i) 
    {
        if (strcmp(students[i].studentID, studentID) == 0)
            return i; // Найдено совпадение, возвращаем индекс
    }
    return -1; // Совпадение не найдено
}

// Функция для создания индексного файла для номера паспорта
void createPassportIndex(struct Student students[], int n) 
{
    FILE* passportIndexFile = fopen("passport_index.txt", "w");

    if (passportIndexFile == NULL)
    {
        printf("Ошибка при создании индексного файла для номеров паспортов.\n");
        exit(1);
    }

    for (int i = 0; i < n; ++i)
        fprintf(passportIndexFile, "%s %d\n", students[i].passportNumber, i);

    fclose(passportIndexFile);
}

// Функция для создания индексного файла для номера зачетной книжки
void createStudentIDIndex(Student students[], int n) 
{
    FILE* studentIDIndexFile = fopen("student_id_index.txt", "w");

    if (studentIDIndexFile == NULL) 
    {
        printf("Ошибка при создании индексного файла для номеров зачетных книжек.\n");
        exit(1);
    }

    for (int i = 0; i < n; ++i)
        fprintf(studentIDIndexFile, "%s %d\n", students[i].studentID, i);

    fclose(studentIDIndexFile);
}

// Функция для быстрого поиска по номеру паспорта с использованием индексного файла
int searchByPassportWithIndex(char passportNumber[], Student students[], int n)
{
    FILE* passportIndexFile = fopen("passport_index.txt", "r");

    if (passportIndexFile == NULL) 
    {
        printf("Ошибка при открытии индексного файла для номеров паспортов.\n");
        exit(1);
    }

    char currentPassport[20];
    int currentIndex;
    bool found = 0;

    while (fscanf(passportIndexFile, "%s %d", currentPassport, &currentIndex) != EOF) 
    {
        if (strcmp(currentPassport, passportNumber) == 0) 
        {
            found = 1;
            fclose(passportIndexFile);
            printf("Студент найден (быстрый поиск по номеру паспорта):\n");
            printf("Индекс: %d\n", currentIndex);
            printf("Имя: %s\n", students[currentIndex].name);
            printf("Номер паспорта: %s\n", students[currentIndex].passportNumber);
            printf("Номер зачетной книжки: %s\n", students[currentIndex].studentID);
            break;
        }
    }

    fclose(passportIndexFile);

    if (!found)
    {
        printf("Студент не найден (быстрый поиск по номеру паспорта)\n");
        // Если не найден, используем последовательный поиск
        int sequentialResult = sequentialSearchByPassport(students, n, passportNumber);
        if (sequentialResult != -1) {
            printf("Студент найден (последовательный поиск по номеру паспорта):\n");
            printf("Индекс: %d\n", sequentialResult);
            printf("Имя: %s\n", students[sequentialResult].name);
            printf("Номер паспорта: %s\n", students[sequentialResult].passportNumber);
            printf("Номер зачетной книжки: %s\n", students[sequentialResult].studentID);
        }
        else {
            printf("Студент не найден (последовательный поиск по номеру паспорта)\n");
        }
    }

    return -1;
}

// Функция для быстрого поиска по номеру зачетной книжки с использованием индексного файла
int searchByStudentIDWithIndex(char studentID[], Student students[], int n)
{
    FILE* studentIDIndexFile = fopen("student_id_index.txt", "r");

    if (studentIDIndexFile == NULL) 
    {
        printf("Ошибка при открытии индексного файла для номеров зачетных книжек.\n");
        exit(1);
    }

    char currentStudentID[15];
    int currentIndex;

    bool found = 0;

    while (fscanf(studentIDIndexFile, "%s %d", currentStudentID, &currentIndex) != EOF)
    {
        if (strcmp(currentStudentID, studentID) == 0)
        {
            found = 1;
            fclose(studentIDIndexFile);
            printf("Студент найден (быстрый поиск по номеру зачетной книжки):\n");
            printf("Индекс: %d\n", currentIndex);
            printf("Имя: %s\n", students[currentIndex].name);
            printf("Номер паспорта: %s\n", students[currentIndex].passportNumber);
            printf("Номер зачетной книжки: %s\n", students[currentIndex].studentID);
            return currentIndex; // Найдено совпадение, возвращаем индекс из индексного файла
        }
    }

    fclose(studentIDIndexFile);

    if (!found)
    {
        printf("Студент не найден (быстрый поиск по номеру зачетной книжки)\n");
        // Если не найден, используем последовательный поиск
        int sequentialResult = sequentialSearchByPassport(students, n, studentID);
        if (sequentialResult != -1) {
            printf("Студент найден (последовательный поиск по номеру паспорта):\n");
            printf("Индекс: %d\n", sequentialResult);
            printf("Имя: %s\n", students[sequentialResult].name);
            printf("Номер паспорта: %s\n", students[sequentialResult].passportNumber);
            printf("Номер зачетной книжки: %s\n", students[sequentialResult].studentID);
        }
        else {
            printf("Студент не найден (последовательный поиск по номеру паспорта)\n");
        }
        
    }

    return -1; // Совпадение не найдено

}

int main() 
{
    system("chcp 1251");

    FILE* inputFile = fopen("students_data.txt", "r");

    if (inputFile == NULL)
    {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n);

    Student* students = (Student*)malloc(n * sizeof(Student));

    for (int i = 0; i < n; ++i) 
        fscanf(inputFile, "%s %s %s", students[i].name, students[i].passportNumber, students[i].studentID);

    fclose(inputFile);

    // Создаем индексные файлы
    createPassportIndex(students, n);
    createStudentIDIndex(students, n);

    char searchPassportNumber[20];
    printf("Введите номер паспорта для поиска: ");
    scanf("%s", searchPassportNumber);

    // Используем индексный файл для быстрого поиска
    int indexResult = searchByPassportWithIndex(searchPassportNumber, students, n);

    char searchStudentID[15];
    printf("Введите номер зачетной книжки для поиска: ");
    scanf("%s", searchStudentID);

    // Используем индексный файл для быстрого поиска
    int indexResultID = searchByStudentIDWithIndex(searchStudentID, students, n);

    free(students);

    return 0;
}

