#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char ch;
    int num;
    struct node *next;
}node;

node* create_node(char c){
    node* newNode = (node*) malloc(sizeof(node));
    newNode -> ch = c;
    newNode -> num = 0;
    newNode -> next = NULL;
    return newNode;
}

int main()
{
    FILE *file;
    file = fopen("main.c", "r");

    if(file == NULL){
        printf("wrong open\n");
        return 1;
    }

    char c; 
    node *head = create_node('\0');
    node *current = NULL;

    while((c = fgetc(file)) != EOF){
        current = head;
        while(current->ch != c){
            if(current->next != NULL) {current = current->next;}
            else {current->next = create_node(c); current = current->next; break;}
        }
        current->num++;
    }

    fclose(file);

    current = head->next;
    do{
        printf("%c : %d\n", current->ch, current->num);
        current = current->next;
    }while(current != NULL);

    return 0;
}