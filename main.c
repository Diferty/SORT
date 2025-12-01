#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "library.h"



int main()
{
    setlocale(LC_ALL,"Rus");
    FILE *file, *file_graphic;
    file = fopen("Сортировка.txt","w");
    file_graphic = fopen("График.txt","w");
    start_enter(file);
    bubble_sort(file,file_graphic);
    //delete_dek();
    sort_piram(file);
    fclose(file);
    fclose(file_graphic);
}