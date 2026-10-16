#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define STRIKETHROUGH "\x1b[9m"

#ifndef UTILS_H
#define UTILS_H

#include "sqlite3.h"

extern sqlite3 *db;

int init_table(void);
int add_todo(const char *task);
int list_callback(void *data, int argc, char **argv, char **col_names);
int list_todos(void);
int exists_callback(void *data, int argc, char **argv, char **col_names);
int id_exists(int id);
int update_done(int id);
int update_undone(int id);
int next_digit(char *str);
int edit_todo(int id, char *task);
int delete_todo(int id);
char *read_after_space(char str[]);

#endif
