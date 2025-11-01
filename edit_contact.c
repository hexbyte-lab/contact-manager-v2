#include "db.h"
#include <stdio.h>
#include <string.h>

int edit_contact()
{
    sqlite3* db;
    char* err_msg = 0;
    int rc = connect_db(&db);

    if (SQLITE_OK != rc) {
        return rc;
    }

    int id;
    char name[100];
    char phone[30];
    char note[200];

    printf("Enter the ID of the contact to edit: ");
    //fgets(name, sizeof(name), stdin); // to clear the leftover inputs.
    scanf("%d", &id);
    getchar(); // clear newline.

    printf("Enter new name (leave empty to keep unchanged): ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter new phone (leave empty to keep unchanged): ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    printf("Enter new note (leave empty to keep unchanged): ");
    fgets(note, sizeof(note), stdin);
    note[strcspn(note, "\n")] = 0;

    // build sql based on which fields user filled.
    char sql[512] = "UPDATE contacts SET ";
    int first = 1; // used to know when to add commas between multiple fields

    if (strlen(name) > 0) {
        strcat(sql, "name = '");
        strcat(sql, name);
        strcat(sql, "'");
        first = 0;
    }

    if (strlen(phone) > 0) {
        if (!first)
            strcat(sql, ", ");
        strcat(sql, "phone = '");
        strcat(sql, phone);
        strcat(sql, "'");
        first = 0;
    }

    if (strlen(note) > 0) {
        if (!first)
            strcat(sql, ", ");
        strcat(sql, "note = '");
        strcat(sql, note);
        strcat(sql, "'");
    }

    strcat(sql, " WHERE id = ");
    char id_str[10];
    snprintf(id_str, sizeof(id_str), "%d", id);
    strcat(sql, id_str);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (SQLITE_OK != rc) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        int changes = sqlite3_changes(db);
        if (0 == changes) {
            printf("No contact found with ID %d.\n", id);
        } else {
            printf("Contact updated successfully\n");
        }
    }
    close_db(db);
    return rc;
}