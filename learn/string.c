#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String{
    char *data;
    int size;
    int capacity;
};

void realloc_string(struct String *s){
    if (s->size == s->capacity){
        char *temp = realloc(s->data, s->capacity*2);
        if (temp == NULL){
            return;
        }
        s->data = temp;
        s->capacity *= 2;
    }
}

struct String new_string(char *chars){
    struct String string;

    string.size = strlen(chars) + 1;
    string.data = malloc( string.size * sizeof(char));
    string.capacity = string.size;

    // for (int i = 0; i < string.size; i++){
    //     string.data[i] = chars[i];
    // }

    strcpy(string.data, chars);

    return string;
}

void append(struct String *s, char c){
    realloc_string(s);

    s->data[s->size-1] = c;
    s->data[s->size] = '\0';

    s->size++;
}

int main(void){
    struct String name = new_string("\nHello world");
    printf("%s", name.data);

    append(&name, '!');
    printf("%s", name.data);

    free(name.data);
}
