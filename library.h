#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct elem 
{
    int inf;
    struct elem *prev;
    struct elem *next;
} Elem;

void change_elements(Elem *p, Elem *pk);
void start_enter(FILE *file);
void delete_dek();
void bubble_sort(FILE *file, FILE *file_graphic);
int find_element_by_num(int num);
Elem *find_element_by_count(int num);
int find_element_by_way(Elem *p);
void sort_piram();






#endif