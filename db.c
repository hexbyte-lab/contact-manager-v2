#include "db.h"
#include <stdio.h>

int connect_db(sqlite3 **db){
    // opening the database
    int rc = sqlite3_open("contacts.db", db);

    // check the connection
    if (SQLITE_OK != rc){
        fprintf(stderr, "Failed to connect to Database: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return SQLITE_OK;
}

// closeing the database
void close_db(sqlite3 *db){
    sqlite3_close(db);
}