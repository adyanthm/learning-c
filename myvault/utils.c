#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "sqlite3.h"
#include "ezsqlite.h"
#include "utils.h"

sqlite3 *db;

int init_table(){
    const char *sql =
        "CREATE TABLE IF NOT EXISTS todo "
        "(id INTEGER PRIMARY KEY, "
        "task TEXT NOT NULL, "
        "done INTEGER NOT NULL DEFAULT 0);";

    char path[1024];

    #ifdef _WIN32
        const char *app_data = getenv("APPDATA");
        const char *sep = "\\";

    #else
        const char *app_data = getenv("XDG_DATA_HOME");
        const char *home = getenv("HOME");

        if (!app_data || !*app_data) {
            if (!home || !*home) {
                fprintf(stderr, RED "Error! HOME not set!\n" RESET);
                return 1;
            }
            snprintf(path, sizeof path, "%s/.local/share/todo.db", home);
        } else {
            snprintf(path, sizeof path, "%s/todo.db", app_data);
        }
    #endif

    #ifdef _WIN32
        if (!app_data) {
            fprintf(stderr, RED "Error! APPDATA not set!\n" RESET);
            return 1;
        }
        snprintf(path, sizeof path, "%s%stodo.db", app_data, sep);
    #endif

    db = db_open(path);
    return db_exec(db, sql);
}

int add_todo(const char *task){
    char sql[1024];
    snprintf(sql, sizeof sql, "INSERT INTO todo (task) VALUES ('%s')", task);
    return db_exec(db, sql);
}

int list_callback(void *data, int argc, char **argv, char **col_names){
    (void)data;
    (void)argc;
    (void)col_names;

    if (strcmp(argv[2], "1") == 0){
        printf(YELLOW "%02d. " CYAN "[" RED "%c" CYAN "] " RESET STRIKETHROUGH "%s\n" RESET,
            atoi(argv[0]),
            'x',
            argv[1]);
    } else {
        printf(YELLOW "%02d. " CYAN "[ ] " RESET "%s\n",
            atoi(argv[0]),
            argv[1]);
    }


    return 0;
}

int list_todos(void){
    printf("\n");
    return db_cexec(db, "SELECT id, task, done FROM todo ORDER BY id;", list_callback, NULL);
}

int exists_callback(void *data, int argc, char **argv, char **col_names) {
    (void)argc;
    (void)col_names;

    *(int *)data = atoi(argv[0]);
    return 0;
}

int id_exists(int id) {
    char sql[128];
    int exists = 0;

    snprintf(sql, sizeof sql, "SELECT EXISTS(SELECT 1 FROM todo WHERE id = %d);", id);

    if (db_cexec(db, sql, exists_callback, &exists) != SQLITE_OK)
        return -1;

    return exists;  // 1 = exists, 0 = doesn't exist, -1 = error
}

int update_done(int id){
    if(!id_exists(id)) return 1;
    char sql[50];
    snprintf(sql, sizeof(sql), "UPDATE todo SET done = 1 where id = %d", id);
    return db_exec(db, sql);
}

int update_undone(int id){
    if(!id_exists(id)) return 1;
    char sql[50];
    snprintf(sql, sizeof(sql), "UPDATE todo SET done = 0 where id = %d", id);
    return db_exec(db, sql);
}

int edit_todo(int id, char *task){
    char sql[1024];
    snprintf(sql, sizeof(sql), "UPDATE todo SET task = '%s' WHERE id = %d;", task, id);
    return db_exec(db, sql);
}

int next_digit(char *str) {
    while (*str && !isdigit((unsigned char)*str))
        str++;

    int num = 0;
    while (isdigit((unsigned char)*str)) {
        num = num * 10 + (*str - '0');
        str++;
    }

    return num;
}

int delete_todo(int id){
    if(!id_exists(id)) return 1;
    char sql[50];
    snprintf(sql, sizeof(sql), "DELETE FROM todo WHERE id = %d;", id);
    return db_exec(db, sql);
}

char *read_after_space(char str[]) {
    static char new[1024];
    int i = 0, j = 0;

    while (str[i] && !isspace((unsigned char)str[i]))
        i++;

    while (isspace((unsigned char)str[i]))
        i++;

    while (str[i] && j < 1023)
        new[j++] = str[i++];

    new[j] = '\0';
    return new;
}
