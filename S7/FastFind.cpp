#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

//� ����� �������� ������� ��������� � �� �������� ������, ���������� ������ �������� � �������� ������.������������ ���
//��������� ����� ��� �������� ������ ���������� �� ������ �� ���� �������.

struct Student {
    char name[50];
    char passportNumber[20];
    char studentID[20];
};

// ��������� ��� �������� ������� �� ������ ��������
struct PassportIndex {
    char passportNumber[20];
    int index;
};

// ��������� ��� �������� ������� �� ������ �������� ������
struct StudentIDIndex {
    char studentID[20];
    int index;
};

// ������� ��� ����������������� ������ �� ������ ��������
int sequentialSearchByPassport(Student students[], int n, char passportNumber[])
{
    for (int i = 0; i < n; ++i) 
    {
        if (strcmp(students[i].passportNumber, passportNumber) == 0) 
            return i; // ������� ����������, ���������� ������
    }
    return -1; // ���������� �� �������
}

// ������� ��� ����������������� ������ �� ������ �������� ������
int sequentialSearchByStudentID(Student students[], int n, char studentID[]) 
{
    for (int i = 0; i < n; ++i) 
    {
        if (strcmp(students[i].studentID, studentID) == 0)
            return i; // ������� ����������, ���������� ������
    }
    return -1; // ���������� �� �������
}

// ������� ��� �������� ���������� ����� ��� ������ ��������
void createPassportIndex(struct Student students[], int n) 
{
    FILE* passportIndexFile = fopen("passport_index.txt", "w");

    if (passportIndexFile == NULL)
    {
        printf("������ ��� �������� ���������� ����� ��� ������� ���������.\n");
        exit(1);
    }

    for (int i = 0; i < n; ++i)
        fprintf(passportIndexFile, "%s %d\n", students[i].passportNumber, i);

    fclose(passportIndexFile);
}

// ������� ��� �������� ���������� ����� ��� ������ �������� ������
void createStudentIDIndex(Student students[], int n) 
{
    FILE* studentIDIndexFile = fopen("student_id_index.txt", "w");

    if (studentIDIndexFile == NULL) 
    {
        printf("������ ��� �������� ���������� ����� ��� ������� �������� ������.\n");
        exit(1);
    }

    for (int i = 0; i < n; ++i)
        fprintf(studentIDIndexFile, "%s %d\n", students[i].studentID, i);

    fclose(studentIDIndexFile);
}

// ������� ��� �������� ������ �� ������ �������� � �������������� ���������� �����
int searchByPassportWithIndex(char passportNumber[], Student students[], int n)
{
    FILE* passportIndexFile = fopen("passport_index.txt", "r");

    if (passportIndexFile == NULL) 
    {
        printf("������ ��� �������� ���������� ����� ��� ������� ���������.\n");
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
            printf("������� ������ (������� ����� �� ������ ��������):\n");
            printf("������: %d\n", currentIndex);
            printf("���: %s\n", students[currentIndex].name);
            printf("����� ��������: %s\n", students[currentIndex].passportNumber);
            printf("����� �������� ������: %s\n", students[currentIndex].studentID);
            break;
        }
    }

    fclose(passportIndexFile);

    if (!found)
    {
        printf("������� �� ������ (������� ����� �� ������ ��������)\n");
        // ���� �� ������, ���������� ���������������� �����
        int sequentialResult = sequentialSearchByPassport(students, n, passportNumber);
        if (sequentialResult != -1) {
            printf("������� ������ (���������������� ����� �� ������ ��������):\n");
            printf("������: %d\n", sequentialResult);
            printf("���: %s\n", students[sequentialResult].name);
            printf("����� ��������: %s\n", students[sequentialResult].passportNumber);
            printf("����� �������� ������: %s\n", students[sequentialResult].studentID);
        }
        else {
            printf("������� �� ������ (���������������� ����� �� ������ ��������)\n");
        }
    }

    return -1;
}

// ������� ��� �������� ������ �� ������ �������� ������ � �������������� ���������� �����
int searchByStudentIDWithIndex(char studentID[], Student students[], int n)
{
    FILE* studentIDIndexFile = fopen("student_id_index.txt", "r");

    if (studentIDIndexFile == NULL) 
    {
        printf("������ ��� �������� ���������� ����� ��� ������� �������� ������.\n");
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
            printf("������� ������ (������� ����� �� ������ �������� ������):\n");
            printf("������: %d\n", currentIndex);
            printf("���: %s\n", students[currentIndex].name);
            printf("����� ��������: %s\n", students[currentIndex].passportNumber);
            printf("����� �������� ������: %s\n", students[currentIndex].studentID);
            return currentIndex; // ������� ����������, ���������� ������ �� ���������� �����
        }
    }

    fclose(studentIDIndexFile);

    if (!found)
    {
        printf("������� �� ������ (������� ����� �� ������ �������� ������)\n");
        // ���� �� ������, ���������� ���������������� �����
        int sequentialResult = sequentialSearchByPassport(students, n, studentID);
        if (sequentialResult != -1) {
            printf("������� ������ (���������������� ����� �� ������ ��������):\n");
            printf("������: %d\n", sequentialResult);
            printf("���: %s\n", students[sequentialResult].name);
            printf("����� ��������: %s\n", students[sequentialResult].passportNumber);
            printf("����� �������� ������: %s\n", students[sequentialResult].studentID);
        }
        else {
            printf("������� �� ������ (���������������� ����� �� ������ ��������)\n");
        }
        
    }

    return -1; // ���������� �� �������

}

int main() 
{
    system("chcp 1251");

    FILE* inputFile = fopen("students_data.txt", "r");

    if (inputFile == NULL)
    {
        printf("������ ��� �������� �����.\n");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n);

    Student* students = (Student*)malloc(n * sizeof(Student));

    for (int i = 0; i < n; ++i) 
        fscanf(inputFile, "%s %s %s", students[i].name, students[i].passportNumber, students[i].studentID);

    fclose(inputFile);

    // ������� ��������� �����
    createPassportIndex(students, n);
    createStudentIDIndex(students, n);

    char searchPassportNumber[20];
    printf("������� ����� �������� ��� ������: ");
    scanf("%s", searchPassportNumber);

    // ���������� ��������� ���� ��� �������� ������
    int indexResult = searchByPassportWithIndex(searchPassportNumber, students, n);

    char searchStudentID[15];
    printf("������� ����� �������� ������ ��� ������: ");
    scanf("%s", searchStudentID);

    // ���������� ��������� ���� ��� �������� ������
    int indexResultID = searchByStudentIDWithIndex(searchStudentID, students, n);

    free(students);

    return 0;
}

