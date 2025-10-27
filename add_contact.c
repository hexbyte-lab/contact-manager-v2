#include "db.h"
#include <stdio.h>

// funtion to insert into database.
int add_contact(const char* name, const char* phone, const char* note)
{
    sqlite3* db;
    char* err_msg = 0;
    int rc = connect_db(&db);
    if (SQLITE_OK != rc)
        return rc;

    // create the query
    char sql[256];
    snprintf(sql, sizeof(sql),
        "INSERT INTO contacts (name, phone, note) VALUES ('%s', '%s', '%s');",
        name, phone, note);

    // execute the query
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    // confirm
    if(SQLITE_OK != rc){
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else{
        printf("Contact added successfully. Back to main menu\n");
    }

    close_db(db);
    return rc;
}