#include <stdio.h>
#include "ezsqlite.h"
#include "sqlite3.h"

sqlite3 *db_open(const char *path){
    sqlite3 *db = NULL; // null pointer
    if (sqlite3_open(path, &db) != SQLITE_OK){
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

int db_cexec(sqlite3 *db, const char *sql, int (*callback)(void*, int, char **, char **), void *data){
    // warning: no safeguard against sql injection / syntax error
    // use this when you need callback. hence cexec.
    // sqlite calls something like callback(data, column_count, column_values, column_names)
    char *err = NULL; // null pointer
    int rc = sqlite3_exec(db, sql, callback, data, &err);
    if (rc != SQLITE_OK){
        fprintf(stderr, "%s\n", err);
        if (err){
            fprintf(stderr, "%s\n", sqlite3_errmsg(db));
            sqlite3_free(err); // free the memory allocated by sqlite3 for this.
        }
    }
    return rc;
}

int db_exec(sqlite3 *db, const char *sql){
    // warning: No safeguard against sql injection / syntax error
    // for use when you dont need callback
    char *err = NULL; // null pointer
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err);
    if (rc != SQLITE_OK){
        fprintf(stderr, "%s\n", err);
        if (err){
            fprintf(stderr, "%s\n", sqlite3_errmsg(db));
            sqlite3_free(err); // free the memory allocated by sqlite3 for this.
        }
    }
    return rc;
}

void db_close(sqlite3 *db){
    sqlite3_close(db);
}
