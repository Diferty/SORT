#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct elem 
{
    int inf;
    struct elem *prev;
    struct elem *next;
} Elem;
void print_file();
void program_going(int num, char *files[]);
void hand_enter();
int start_file(int num, char *files[]);
void change_elements(Elem *p, Elem *pk);
int start_enter(FILE *file);
void delete_dek();
void bubble_sort(FILE *file);
int find_element_by_num(int num);
Elem *find_element_by_count(int num);
int find_element_by_way(Elem *p);
void sort_piram();






#endif