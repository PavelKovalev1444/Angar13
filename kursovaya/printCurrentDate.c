#include "printCurrentDate.h"
#include "parseDate.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCurrentDate(char** arr, int n)
{
    printf("++++++++++++++\n");
    for(int i = 0; i < n; i++) {
        char *buffer = calloc(strlen(arr[i]) + 1, sizeof(char));
        strcpy(buffer, arr[i]);
        char *istr;
        istr = strtok(buffer, " ");
        int count = 0;
        struct tm data_input_user;
        time_t now_time;
        time(&now_time);
        struct tm* data_now;
        data_now = localtime(&now_time);
        while(istr != NULL){
            data_input_user = parse_date(istr);
            if(data_input_user.tm_year == data_now->tm_year && data_input_user.tm_mon == data_now->tm_mon){
                count++;
            }
            istr = strtok(NULL, " ");
        }
        if(count > 0){
            printf("%s\n", arr[i]);
        }
    }
    printf("++++++++++++++");
}
