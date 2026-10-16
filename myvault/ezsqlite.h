#ifndef EZSQLITE_H
#define EZSQLITE_H
// header guards!

#include "sqlite3.h"

sqlite3 *db_open(const char *path);
int db_cexec(sqlite3 *db, const char *sql, int (*callback)(void*, int, char **, char **), void *data);
int db_exec(sqlite3 *db, const char *sql);
void db_close(sqlite3 *db);

#endif
