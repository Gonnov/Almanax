#include "main.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    fclose(fopen("data.txt", "w"));
    char *string_ressource;
    char **link;
    FILE *fp = fopen("data.txt", "a");
    int i;
    int number_of_day;
    i = 0;
    printf("Combien de jour voulez vous afficher ? ");
    scanf("%d", &number_of_day);
    link = return_url_almanax(number_of_day);
    while (link[i])
    {
        string_ressource = dailyneed_string(link[i]);
        printf("%s\n", string_ressource);
        fprintf(fp, "%s\n", string_ressource);
        i++;
    }

    i = 0;
    while (i < number_of_day)
    {
        i++;
        free(link[i]);
        link[i] = NULL;
    }
    free(string_ressource);
    free(link);
    string_ressource = NULL;
    link = NULL;  
    fclose(fp);

    return 0;
}
