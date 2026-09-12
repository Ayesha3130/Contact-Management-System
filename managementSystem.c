#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function declarations
void Menu();
void AddNewContact();
void ShowAllContacts();
void SearchContact();
void EditContact();
void DeleteContact();
void DeleteAllContacts();
void PrintLineWithSpace(char *line, char type);
void ExitProgram();
void UserGuideline();
void AboutUs();
void ErrorAndRestart(const char *msg);

int main() 
{
    bool isRunning = true;
    char option;

    while (isRunning) 
    {
        Menu();
        scanf(" %c", &option);

        switch (option) 
        {
            case '0': ExitProgram(); break;
            case '1': AddNewContact(); break;
            case '2': ShowAllContacts(); break;
            case '3': SearchContact(); break;
            case '4': EditContact(); break;
            case '5': DeleteContact(); break;
            case '6': DeleteAllContacts(); break;
            case '7': system("cls || clear"); break;
            case 'I':
            case 'i': UserGuideline(); break;
            case 'A':
            case 'a': AboutUs(); break;
            default: ErrorAndRestart("Option not found"); break;
        }
    }
    return 0;
}

// ===== Menu =====
void Menu() 
{
    printf("\n\t **** My-Contact Management System ****\n\n");
    printf("\t\tMAIN MENU\n");
    printf("\t\t=====================\n");
    printf("\t\t[1] Add a new Contact\n");
    printf("\t\t[2] List all Contacts\n");
    printf("\t\t[3] Search for contact\n");
    printf("\t\t[4] Edit a Contact\n");
    printf("\t\t[5] Delete a Contact\n");
    printf("\t\t[6] Delete All Contacts\n");
    printf("\t\t[7] Clear Window\n");
    printf("\t\t[I] User Guideline\n");
    printf("\t\t[A] About Us\n");
    printf("\t\t[0] Exit\n");
    printf("\t\t=================\n");
    printf("\t\tEnter your choice: ");
}

// ===== Add New Contact =====
void AddNewContact() 
{
    char Name[100], Phone[100], Email[100];

    printf("Enter Name: ");
    scanf(" %[^\n]", Name);
    printf("Enter Phone: ");
    scanf(" %[^\n]", Phone);
    printf("Enter Email: ");
    scanf(" %[^\n]", Email);

    FILE *fp = fopen("All-Contact.txt", "a");
    if (fp == NULL) 
    {
        printf("File could not be opened");
        return;
    }

    fprintf(fp, "%s\n%s\n%s\n", Name, Phone, Email);
    fclose(fp);
    printf("\nContact Added Successfully!\n\n");
}

// ===== Show All Contacts =====
void ShowAllContacts() 
{
    FILE *fp = fopen("All-Contact.txt", "r");
    if (fp == NULL) 
    {
        printf("No contacts found.\n");
        return;
    }

    char line[256];
    int count = 0, contactCount = 0;

    printf("|====================|====================|==============================|\n");
    printf("|        Name        |    Phone Number    |          Email               |\n");
    printf("|====================|====================|==============================|\n");

    while (fgets(line, sizeof(line), fp)) 
    {
        count++;
        if (count == 1)
        {
            PrintLineWithSpace(line, 'n');
        }
        else if (count == 2)
        {
            PrintLineWithSpace(line, 'p');
        }
        else if (count == 3) 
        {
            PrintLineWithSpace(line, 'e');
            count = 0;
            contactCount++;
        }
    }

    fclose(fp);
    printf("You Have Total %d Contacts.\n\n", contactCount);
}

// ===== Search Contact =====
void SearchContact() 
{
    char searchName[100], line[256];
    int lineCount = 0, found = 0;

    printf("Enter the name to search: ");
    scanf(" %[^\n]", searchName);
    strcat(searchName, "\n");

    FILE *fp = fopen("All-Contact.txt", "r");
    if (fp == NULL) 
    {
        printf("No contacts found.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) 
    {
        lineCount++;
        if (lineCount == 1 && strcmp(searchName, line) == 0) 
        {
            found = 1;
            printf("\nContact Information:\n");
            printf("Name: %s", line);
            fgets(line, sizeof(line), fp);
            printf("Phone: %s", line);
            fgets(line, sizeof(line), fp);
            printf("Email: %s\n", line);
            break;
        }
        if (lineCount == 3)
        {
            lineCount = 0;
        }
    }

    if (!found)
    {
        printf("\nContact not found.\n");
    }

    fclose(fp);
}

// ===== Edit Contact =====
void EditContact() 
{
    char searchName[100], newName[100], newPhone[100], newEmail[100], line[256];
    int found = 0, lineCount = 0;

    printf("Enter the name of the contact to edit: ");
    scanf(" %[^\n]", searchName);
    strcat(searchName, "\n");

    FILE *fp = fopen("All-Contact.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) 
    {
        lineCount++;

        if (lineCount == 1 && strcmp(line, searchName) == 0) 
        {

            found = 1;

            printf("Enter new name (0 to keep old): ");
            scanf(" %[^\n]", newName);
            if (strcmp(newName, "0") == 0)
            {
                fputs(line, temp);
            }
            else
            {
                fprintf(temp, "%s\n", newName);
            }

            fgets(line, sizeof(line), fp);
            printf("Enter new phone (0 to keep old): ");
            scanf(" %[^\n]", newPhone);

            if (strcmp(newPhone, "0") == 0)
            {
                fputs(line, temp);
            }
             else
            {
                fprintf(temp, "%s\n", newPhone);
            }

            fgets(line, sizeof(line), fp);
            printf("Enter new email (0 to keep old): ");
            scanf(" %[^\n]", newEmail);

            if (strcmp(newEmail, "0") == 0)
            {
                fputs(line, temp);
            }
            else
            {
                fprintf(temp, "%s\n", newEmail);
            }

            lineCount = 0;
        } 
        else 
        {
            fputs(line, temp);
        }

        if (lineCount == 3)
        lineCount = 0;
    }

    fclose(fp);
    fclose(temp);

    if (found) 
    {
        remove("All-Contact.txt");
        rename("temp.txt", "All-Contact.txt");
        printf("\nContact Updated Successfully!\n\n");
    } 
    else 
    {
        remove("temp.txt");
        printf("\nContact Not Found.\n\n");
    }
}

// ===== Delete Contact =====
void DeleteContact() 
{
    char searchName[100], line[256];
    int found = 0, lineCount = 0, skip = 0;

    printf("Enter the name to delete: ");
    scanf(" %[^\n]", searchName);
    strcat(searchName, "\n");

    FILE *fp = fopen("All-Contact.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) 
    {
        lineCount++;

        if (lineCount == 1 && strcmp(line, searchName) == 0) 
        {
            found = 1;
            skip = 2; 
        } else if (skip > 0) 
        {
            skip--;
        } 
        else 
        {
            fputs(line, temp);
        }

        if (lineCount == 3)
            lineCount = 0;
    }

    fclose(fp);
    fclose(temp);

    if (found) 
    {
        remove("All-Contact.txt");
        rename("temp.txt", "All-Contact.txt");
        printf("\nContact Deleted Successfully!\n\n");
    } 
    else 
    {
        remove("temp.txt");
        printf("\nContact Not Found.\n\n");
    }
}

// ===== Delete All Contacts =====
void DeleteAllContacts() 
{
    char option;
    printf("Are you sure you want to delete all contacts? (Y/N): ");
    scanf(" %c", &option);

    if (option == 'Y' || option == 'y') 
    {
        remove("All-Contact.txt");
        FILE *fp = fopen("All-Contact.txt", "w");
        if (fp != NULL)
        fclose(fp);
        printf("All Contacts Deleted.\n");
    } 
    else 
    {
        printf("Operation Cancelled.\n");
    }
}

// ===== Helper Functions =====
void ExitProgram() 

{
    printf("Exiting program...\n");
    exit(0);
}

void UserGuideline() 
{
    printf("\n-- User Guideline --\nYou can add, view, edit, and delete contacts using menu options.\n");
}

void AboutUs() 
{
    printf("\n-- About Us --\nSimple Contact Management System in C.\n");
}

void ErrorAndRestart(const char *msg) 
{
    printf("Error: %s\n", msg);
}

void PrintLineWithSpace(char *line, char type) 
{
    line[strcspn(line, "\n")] = 0; // remove newline
    if (type == 'n')
        printf("| %-20s", line);
    else if (type == 'p')
        printf("| %-20s", line);
    else if (type == 'e')
        printf("| %-30s |\n", line);
}
