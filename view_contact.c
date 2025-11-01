#include "db.h"
#include <stdio.h>

// callback to print the each row
int view_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("-----------------------------\n");
    return 0;
}

int view_contact()
{
    sqlite3* db;
    char* err_msg = 0;
    int rc = connect_db(&db);
    if (SQLITE_OK != rc) {
        return rc;
    }

    // create the query to view the list
    const char* sql = "SELECT * FROM contacts;";

    // execute the query
    rc = sqlite3_exec(db, sql, view_callback, 0, &err_msg);

    // confirm
    if (SQLITE_OK != rc) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Back to main menu.\n");
    }
    close_db(db);
    return rc;
}