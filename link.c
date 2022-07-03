#include "date.h"
#include <stdlib.h>
#include <stdio.h>

int count_digit(int date)
{
    int i;
    i = 1;
    
    while (date > 10)
    {
        date /= 10;
        i++;
    }
    return i;
}

char *convert_int_to_string(int date)
{
    char *temp_date = malloc(sizeof(char)*5);
    int digit_number = count_digit(date);

    if (digit_number == 1)
    {
        digit_number += 1;
        temp_date[0] = '0';
    }    
    temp_date[digit_number] = '\0';
    while(date > 0)
    {
        digit_number--;
        temp_date[digit_number] = (date % 10) +'0';
        date /= 10;
    }
    return temp_date;
}
void incrementation_string_copy(int *i, int *j, char *concatenate_date, char date)
{
    concatenate_date[*i] = date;
    *i += 1;
    *j += 1;
}

char *convert_date_in_single_str(int *date)
{
    char *year = convert_int_to_string(date[0]);
    char *month = convert_int_to_string(date[1]);
    char *day = convert_int_to_string(date[2]);
    char *concatenate_date = malloc(sizeof(char)* 11);//The number of char needed to complete the URL
    int i = 0;
    int j = 0;
    while (i < 4)
        incrementation_string_copy(&i, &j, concatenate_date, year[j]);

    concatenate_date[i] = '-';
    i+=1;
    j = 0;
    while (i < 7)
        incrementation_string_copy(&i, &j, concatenate_date, month[j]);

    concatenate_date[i] = '-';
    i+=1;
    j = 0;
    while (i < 10)
        incrementation_string_copy(&i, &j, concatenate_date, day[j]);

    concatenate_date[i] = '\0';

    free(year);
    free(month);
    free(day);
    year = NULL;
    month = NULL;
    day = NULL;
    return concatenate_date;
}

char *concatenate_link(char *base_link, char *date_link)
{
    char *final_link = malloc(sizeof(char) *46); //Number of letters in an URL
    int i = 0;
    int j = 0;
    while (base_link[j])
    {
        final_link[i] = base_link[j];
        i++;
        j++; 
    }
    j = 0;
    while (date_link[j])
    {
        final_link[i] = date_link[j];
        i++;
        j++;
    }
    final_link[i] = '\0';
    return final_link;    
}


char **return_url_almanax(int number_of_date)
{
    int *date = find_date();
    char *date_link;
    char *base_link = "https://www.krosmoz.com/fr/almanax/";
    char **final_link = malloc(sizeof(char *) * (number_of_date +1));
    int i = 0;
    while (i < number_of_date)
    {
        if (i != 0)
          add_one_day_to_date(date);
        date_link = convert_date_in_single_str(date);
        final_link[i] = concatenate_link(base_link, date_link);
        concatenate_link(base_link, date_link); 
        i++;
    }
    final_link[i] = '\0';
    
    free(date_link);
    free(date);
    date_link = NULL;
    date = NULL;
    return final_link;
}

