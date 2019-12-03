#include "parseDate.h"

struct tm parse_date(char *str)
{
    int year, mon, day;
    sscanf(str, "%d/%d/%d", &day, &mon, &year);
        struct tm time;
        memset(&time, 0, sizeof(time));
        time.tm_mon = mon - 1;
        time.tm_mday = day;
        time.tm_year = year - 1900;
        time.tm_isdst = -1;
        return time;
};
