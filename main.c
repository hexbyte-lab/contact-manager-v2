#include "db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototype
int add_contact(const char* name, const char* phone, const char* note);
int view_contact();
int edit_contact();

// funtion to get the string inputs
void get_input(char* prompt, char* buffer, size_t size)
{
    printf("%s", prompt);
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // to remove the new line.
    }
}

int main()
{
    char choice_str[10];
    int choice;
    char name[50], phone[20], note[100];

    // infinite loop for the menu;
    int app_running = 1;
    while (app_running) {
        printf("*********** CONTACT MANAGER ***********\n");
        printf("1. Add Contact\n");
        printf("2. View Contact List\n");
        printf("3. Edit Contact\n");
        printf("0. Exit\n");
        printf("Enter your choice >>>: ");
        get_input("", choice_str, sizeof(choice_str));
        choice = atoi(choice_str); // convert sting to int.

        // adding a new contact
        if (1 == choice) {
            // get the contact data
            get_input("Enter Name: ", name, sizeof(name));
            get_input("Enter Phone: ", phone, sizeof(phone));
            get_input("Enter Note: ", note, sizeof(note));

            add_contact(name, phone, note);
        }
        // view contact list
        if (2 == choice) {
            view_contact();
        }

        if (3 == choice) {
            printf("Debug\n");
            edit_contact();
        }
        if (0 == choice) {
            app_running = 0;
        }
    }
    return 0;
}