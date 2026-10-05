#include <corecrt_search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Vector {
  int *data;
  int size;
  int capacity;
};

struct Vector new_vec(){
    struct Vector v;
    v.size = 0;
    v.capacity = 4;
    v.data = malloc(sizeof(int) * v.capacity);
    return v;
}

void extend_vec(struct Vector *v){
    if (v->size == v->capacity){
        int *temp = realloc( v->data , sizeof(int) * (v->capacity+v->size));

        if (temp == NULL){
            return;
        }

        v->data = temp;
        v->capacity += v->size;
    }
}

void push(struct Vector *v, int val){
    extend_vec(v);
    v->data[v->size] = val;
    v->size++;
}

int pop(struct Vector *v, int *result){
    if (v->size == 0)
        return 0;

    v->size--;
    *result = v->data[v->size];
    return 1;
}

int sum_vec(struct Vector *v){
    int sum = 0;
    for (int i = 0; i < v->size; i++){
        sum += v->data[i];
    }
    return sum;
}

int main(void){
    struct Vector v = new_vec();
    int not_done = 1;

    while (not_done){
        char input[100];

        printf("> ");
        scanf("%99s", input);

        if (strcmp(input, "done") == 0){
            not_done = 0;
            break;
        }

        push(&v, atoi(input));
    }

    int sum = sum_vec(&v);
    printf("Sum: %d\n", sum);
    printf("Mean: %.2f", (double)sum / v.size);
    free(v.data);
}
