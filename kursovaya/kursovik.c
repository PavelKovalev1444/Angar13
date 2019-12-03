#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "printCurrentDate.h"

struct tm parse_date(char *str);
char* ReadSentence();

char* DelTab(char* s);

char* DelProbel(char* s);

int DoubleSentence(char** arr, int* n);

int main(){
    char** arr = malloc(10*sizeof(char*));
    int size = 10;
    int n = 0;
    char* s;
    char date[7];
    while(1){
        s = ReadSentence();
        if(strcmp(s, "\n") == 0){
            break;
        }
        if(n == size -1){
            size += 10;
            arr = realloc(arr, sizeof(char*)*size);
        }
        s = DelTab(s);
        arr[n] = DelProbel(s);
        n++;
    }
    DoubleSentence(arr, &n);
    struct tm data_input_user = parse_date(arr[0]);
    time_t now_time;
    time(&now_time);
    struct tm* data_now;
    data_now = localtime(&now_time);
    printCurrentDate(arr, n);

    printf("\n\n========================================================================\n");
    for(int i = 0; i<n; i++){
        printf("|\t\t\t{%s}\t\t\t\t\t|\n", arr[i]);
    }

    for(int i = 0; i < n; i++){
        free(arr[i]);
    }
    free(arr);
    free(s);
    return 0;
}

char* ReadSentence()
{
    char* s = malloc(10*sizeof(char));
    int n = 0;
    char c;
    int size = 10;
    while((c = getchar()) && c != '!' && c != '.' && c != ';' && c != '?' && c != '\n'){
        if(n == (size-2)){
            size += 10;
            s = realloc(s, size);
        }
        s[n] = c;
        ++n;
    }
    s[n] = c;
    s[n+1] = '\0';
    return s;
}

char* DelTab(char* s)
{
    int k = 0;
    int length = strlen(s);
    if(s[0] == '\t'){
        while(k < length){
            s[k] = s[k+1];
            k++;
        }
    }
    return s;
}

char* DelProbel(char* s)
{
    int i = 0;
    int length = strlen(s);
    if(s[0] == ' '){
        while(i < length){
            s[i] = s[i+1];
            i++;
        }
    }
    return s;
}

int DoubleSentence(char** arr, int *n)
{
    int i = 0;
    int length = 0;
    length = *n;
    while(i < length - 1){
        for(int j = i + 1; j < length; j++){
            if(strcmp(arr[i], arr[j]) == 0){
                free(arr[j]);
                for(int a = j; a < length - 1; a++){
                    arr[a] = arr[a+1];
                }
                length--;
                *n-=1;
                j--;
            }
        }
        i++;
    }
}
