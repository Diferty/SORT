#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "library.h"



int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"Rus");
    FILE *file, *file_graphic;
    program_going(argc,argv);
}