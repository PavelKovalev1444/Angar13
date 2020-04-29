#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year);

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);

void push(MusicalComposition* head, MusicalComposition* element);

void removeEl(MusicalComposition* head, char* name_for_remove);

int count(MusicalComposition* head);

void print_names(MusicalComposition* head);


int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove); 
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}

MusicalComposition* createMusicalComposition(char* name, char* autor,int year)
{
    struct MusicalComposition* composition = malloc(sizeof(struct MusicalComposition));
    strcpy(composition->name, name);
    strcpy(composition->author, autor);
    composition -> year = year;
    composition -> next = NULL;
    composition -> prev = NULL;
    return composition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    struct MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    struct MusicalComposition* tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    head -> next = tmp;
    head -> prev = NULL;
    tmp -> prev = head;
    for(int i = 2; i < n; i++){
        tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tmp->next->next = NULL;
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    return head;
}

void push(MusicalComposition*  head, MusicalComposition* element)
{
    struct MusicalComposition* tmp;
    element -> next == NULL;
    tmp = head;
    while(tmp != NULL){
        tmp = tmp->next;
    }
    tmp->next = element;
    element->prev == tmp;
}

void removeEl(MusicalComposition* head, char* name_for_remove)
{
    struct MusicalComposition* lst;
    lst = head;
    while(strcmp(lst->name, name_for_remove) != 0){
        lst = lst->next;
    }
    struct MusicalComposition* prev, *next;
    prev = lst->prev;
    next = lst->next;
    if (prev != NULL){
        prev->next = lst->next;
    }    
    if (next != NULL){
        next->prev = lst->prev;
    }
    free(lst);
}

int count(MusicalComposition* head){
    struct MusicalComposition* tmp;
    tmp = head;
    int a;
    while(tmp != NULL){
        a++;
        tmp = tmp->next;
    }
    return a;
}

void print_names(MusicalComposition*  head)
{
    struct MusicalComposition* tmp = head;
    while(tmp != NULL){
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}
