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

int is_keyword(const char *str){
    const char *keywords[] = {"int", "main", "if", "else", "while"};
    for(int i=0; i<5; i++)
        if(strcmp(str, keywords[i])==0) return i+1;
    return 0;
}

#define MAX_ID_COUNT 100
char *id[MAX_ID_COUNT]={};
int is_id(const char *str){
    for(int i=0; i<MAX_ID_COUNT; i++)
        if(strcmp(str, id[i])==0) return 1;
    return 0;
}

int is_token(char c){
    char non_id[100] = {' ', '\n', '\t', '=', '>', '<', '+', '-', '(', ')', '{', '}', ';'};
    
    for(int i=0; non_id[i]; i++){
        if(c==non_id[i]) return (i+1);
    }return 0;
}

char* print_token(int a){
    char* TOKEN[100]={"ASSIGN", "GREATER", "LESS", "PLUS", "MINUS", "LEFTPAREN", "REFTPAREN", "LEFTBRACE", "RIGHTBRACE", "SEMICOLON", "EQUAL", "GREATEREQUAL", "LESSEQUAL"};
    return TOKEN[a-4];
}

void to_upper(char *s) {
    for (int i = 0; s[i]; i++) {
        if(s[i]>=97 && s[i]<=122)
            s[i] -= 32;
    }
}

int is_digit(char ch){
    return (ch>='0' && ch<='9');
}

int is_alpha(char ch){
    return ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch=='_'));
}

int main()
{
    FILE *file;
    file = fopen("identify_token.c", "r");

    if(file == NULL){
        printf("wrong open\n");
        return 1;
    }

    char c, in_char[100];
    char *str_array[1000]={NULL};
    int index = 0, index_str = 0;
    node *head = create_node('\0');
    node *current = NULL;
    
    while((c = fgetc(file)) != EOF){
        int a = is_token(c);
        if(!a){
            in_char[index++] = c;
        }else{
            in_char[index] = '\0';
            str_array[index_str++] = strdup(in_char);
            index = 0;
            if(a>3){
                in_char[index++] = c;
                in_char[index] = '\0';
                str_array[index_str++] = strdup(in_char);
                index = 0;
            }
        }
    }

    char *upper_str="";
    for(int i=0; str_array[i]; i++){
        if(is_keyword(str_array[i])){
            if(strcmp(str_array[i], "int") == 0)
                printf("%s:TYPE_TOKEN\n", str_array[i]);
            else{
                upper_str = strdup(str_array[i]);
                to_upper(upper_str);
                printf("%s:%s_TOKEN\n", str_array[i], upper_str);
                free(upper_str);
            }
        }else{
            int a = is_token(str_array[i][0]);
            
            if(a!=0){
                if((a==4 || a==5 || a==6) && str_array[i+1] && (is_token(str_array[i+1][0]))==4){
                    printf("%s=:%s_TOKEN\n", str_array[i], print_token(a+10));
                }
                printf("%s:%s_TOKEN\n", str_array[i], print_token(a));
            }
            else{
                if (str_array[i]=="\0"){}
                if(is_digit(str_array[i][0]))
                    printf("%s:LITERAL_TOKEN\n", str_array[i]);
                if(is_alpha(str_array[i][0]))
                    printf("%s:ID_TOKEN\n", str_array[i]);
            }
        }
        //printf("%s\n", str_array[i]);
        free(str_array[i]);
    }
    fclose(file);
    return 0;
}