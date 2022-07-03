#include <stdlib.h>
#include<time.h>


void change_month(int *date)
{
    date[1] += 1;
    date[2] = 1;
}

void add_one_day_to_date(int *date)
{  
    

    if (date[0] == 2024 || date[0] == 2028 || date[0] == 2032 ) //Bissextil year 29 days
    {
        if (date[1] == 2 && date[2] == 29)
        {
            change_month(date);
            return;
        }
    }
    
    if (date[0] != 2024 && date[1] == 2 && date[2] == 28) // month 28 days
    {
        change_month(date);
        return;
    }
    if (date[1] == 4 || date[1] == 6 || date[1] == 9 || date[1] == 11)
    {
        if (date[2] == 30 )
        {
            change_month(date);
            return;
        }
        
    }
    if (date[1] == 1 || date[1] == 3 || date[1] == 5 || date[1] == 7 
            ||date[1] == 8 || date[1] == 10)
    {
        if (date[2] == 31)
        {
            change_month(date);
            return;
        }
    }
    if (date[1] == 12 && date[2] == 31)
    {
        date[0] += 1;
        date[1] = 1;
        date[2] = 1;
        return;
    }
    date[2] += 1;
}
int *find_date() 
{
    int *date;
    date = malloc(sizeof(int)*3);
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    date[0] = local->tm_year + 1900;
    date[1] = local->tm_mon + 1;
    date[2] = local->tm_mday;
      
    return date;
}