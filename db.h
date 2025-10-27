#ifndef DB_H
#define DB_H

#include "sqlite3.h"

int connect_db(sqlite3 **db);
void close_db(sqlite3 *db);

#endif