#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
  char *name;
  char *phone;
};

struct ContactBook {
  struct Contact *contacts;
  int size;
  int capacity;
};

struct ContactBook new_book(void) {
  struct ContactBook book;
  book.size = 0;
  book.capacity = 4;
  book.contacts = malloc(sizeof(struct Contact) * book.capacity);
  return book;
}

void extend_book(struct ContactBook *book) {

  if (book->size < book->capacity) {
    return;
  }

  int new_capacity = book->capacity * 2;

  struct Contact *temp = realloc(book->contacts, sizeof(struct Contact) * new_capacity);

  if (temp == NULL) {
    return;
  }

  book->contacts = temp;
  book->capacity = new_capacity;

}

char *copy_string(char *text) {
  int size = strlen(text) + 1;
  char *copy = malloc(size);

  if (copy == NULL) {
    return NULL;
  }

  strcpy(copy, text);
  return copy;
}

void add_contact(struct ContactBook *book, char *name, char *phone) {
  extend_book(book);
  book->contacts[book->size].name = copy_string(name);
  book->contacts[book->size].phone = copy_string(phone);
  book->size++;
}

void list_contacts(struct ContactBook *book) {
  for (int i = 0; i < book->size; i++) {
    printf("%d: %s\t%s\n", i, book->contacts[i].name, book->contacts[i].phone);
  }
}
void find_contact(struct ContactBook *book, char *name) {
  for (int i = 0; i < book->size; i++) {
    if (strcmp(book->contacts[i].name, name) == 0) {
      printf("Name: %s\n", book->contacts[i].name);
      printf("Phone: %s\n", book->contacts[i].phone);
      return;
    }
  }
  printf("Contact not found\n");
}

void delete_contact(struct ContactBook *book, int index) {

  if (index < 0 || index >= book->size) {
    printf("Invalid index\n");
    return;
  }

  free(book->contacts[index].name);
  free(book->contacts[index].phone);

  for (int i = index; i < book->size - 1; i++) {
    book->contacts[i] = book->contacts[i + 1];
  }

  book->size--;
}

void free_book(struct ContactBook *book) {
  for (int i = 0; i < book->size; i++) {
    free(book->contacts[i].name);
    free(book->contacts[i].phone);
  }

  free(book->contacts);
}

int main(void) {
  struct ContactBook book = new_book();

  char command[20];
  char name[100];
  char phone[100];
  int index;

  while (1) {
    printf("> ");
    scanf("%19s", command);

    if (strcmp(command, "add") == 0) {
      scanf("%99s %99s", name, phone);
      add_contact(&book, name, phone);
    } else if (strcmp(command, "list") == 0) {
      list_contacts(&book);
    } else if (strcmp(command, "find") == 0) {
      scanf("%99s", name);
      find_contact(&book, name);
    } else if (strcmp(command, "delete") == 0) {
      scanf("%d", &index);
      delete_contact(&book, index);
    } else if (strcmp(command, "exit") == 0) {
      break;
    } else {
      printf("Unknown command\n");
    }
  }
  free_book(&book);
  return 0;
}
