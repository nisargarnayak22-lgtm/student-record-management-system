#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student
{
    int id;
    char name[50];
    int age;
    char course[30];
    float marks;
};

struct Student students[MAX];
int count = 0;

// function declarations
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void loadFromFile();
void saveToFile();

int main()
{  
    loadFromFile();
    int choice;

    do
    {
        printf("\n=========================================\n");
        printf("      STUDENT RECORD MANAGEMENT\n");
        printf("=========================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("\nExiting...\n"); break;
            default: printf("\nInvalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}
void addStudent()
{
    if(count >= MAX)
    {
        printf("\nDatabase Full!\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &students[count].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter Age: ");
    scanf("%d", &students[count].age);

    printf("Enter Course: ");
    scanf(" %[^\n]", students[count].course);

    printf("Enter Marks: ");
    scanf("%f", &students[count].marks);

    count++;
    saveToFile();

    printf("\nStudent Added Successfully!\n");
}
void displayStudents()
{
    if(count == 0)
    {
        printf("\nNo Students Found!\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        printf("\n--------------------------------\n");
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Course: %s\n", students[i].course);
        printf("Marks: %.2f\n", students[i].marks);
        printf("--------------------------------\n");
    }
}
void searchStudent()
{
    int id, found = 0;

    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(students[i].id == id)
        {
            printf("\nStudent Found!\n");
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Course: %s\n", students[i].course);
            printf("Marks: %.2f\n", students[i].marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nStudent Not Found!\n");
}

void updateStudent()
{
    int id, found = 0;

    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(students[i].id == id)
        {
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter New Age: ");
            scanf("%d", &students[i].age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", students[i].course);

            printf("Enter New Marks: ");
            scanf("%f", &students[i].marks);

            printf("\nUpdated Successfully!\n");
            saveToFile();
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nStudent Not Found!\n");
}
void deleteStudent()
{
    int id, found = 0;

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(students[i].id == id)
        {
            for(int j = i; j < count - 1; j++)
            {
                students[j] = students[j + 1];
            }

            count--;
            saveToFile();
            printf("\nDeleted Successfully!\n");
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nStudent Not Found!\n");
}
void loadFromFile()
{
    FILE *fp = fopen("students.txt", "r");

    if(fp == NULL)
        return;

    while(fscanf(fp, "%d %s %d %s %f",
                 &students[count].id,
                 students[count].name,
                 &students[count].age,
                 students[count].course,
                 &students[count].marks) != EOF)
    {
        count++;
    }

    fclose(fp);
}
void saveToFile()
{
    FILE *fp = fopen("students.txt", "w");

    for(int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %d %s %.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].course,
                students[i].marks);
    }

    fclose(fp);
}