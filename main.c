#include <stdio.h>
#include "my_mat.h"

int main()
{
    char check = 1;
    while (check != 'D')
    {
        scanf(" %c", &check);
        switch (check)
        {
        case 'A':
            buildGraph();
            break;

        case 'B':
            isThereConnection();
            break;

        case 'C':
            shortPath();
            break;

        case 'D':
            break;

        // command doesn't match any case constant A, B, C, D
        default:
            printf("Error! Write from this command A,B,C,D \n");
        }
    }
    return 0;
}