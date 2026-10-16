#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(void){

    init_table();

    while (1){
        char arg[1024];

        printf(BLUE ">>> " RESET);
        fgets(arg, sizeof(arg), stdin);

        if (!strncmp(arg, "add", 3)){
            char *task = read_after_space(arg);
            add_todo(task);
            printf(YELLOW "\n=> " GREEN "Added task: " RESET "%s\n", task);
        }
        else if (!strncmp(arg, "list", 4)){
            list_todos();
        }
        else if (!strncmp(arg, "delete", 6) || !strncmp(arg, "del", 3)){
            char *id = read_after_space(arg);
            delete_todo(atoi(id));
            printf(YELLOW "\n=> " RED "Deleted task: " RESET "%s\n", id);
        }
        else if (!strncmp(arg, "done", 4) || !strncmp(arg, "finish", 6)){
            char *id = read_after_space(arg);
            update_done(atoi(id));
            printf(YELLOW "\n=> " MAGENTA "Finished task: " RESET "%s\n", id);
        }
        else if (!strncmp(arg, "undo", 4) || !strncmp(arg, "unfinish", 6)){
            char *id = read_after_space(arg);
            update_undone(atoi(id));
            printf(YELLOW "\n=> " MAGENTA "Undone task: " RESET "%s\n", id);
        }
        else if (!strncmp(arg, "edit", 4)){
            int id = next_digit(arg);
            char *task = read_after_space(arg);
            task = read_after_space(task);
            edit_todo(id, task);
            printf(YELLOW "\n=> " MAGENTA "Updated task: " YELLOW "%d. " RESET "%s\n", id, task);
        }
        else if (!strncmp(arg, "quit", 4)){
            printf(YELLOW "\n=> " BLUE "Quitting Program. \n" RESET);
            return 0;
        }
        else {
            printf(RED "\nError: " RESET "Invalid Command!\n\n");
            printf(YELLOW "Usage: " RESET "<command> <task>\n");
            printf(YELLOW "Example: " BLUE "add " MAGENTA "homework\n\n" RESET);
            printf(MAGENTA "Available commands: " RESET "add, list, edit, done, delete\n\n" RESET);
        }
    }
}
