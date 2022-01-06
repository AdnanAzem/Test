#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "algo.h"

int main(){
    char ch;
    int k;
    pnode head = NULL;
    int end_of_file = 0;
    while(end_of_file!=EOF){
        end_of_file = scanf("%c", &ch);
        if (ch == 'A'){
            deleteGraph_cmd(&head);
            scanf("%d", &k);
            //head = allocate_graph(k);
        }
        if (ch == 'n'){
            build_graph_cmd(&head);
        }
        if (ch == 'B'){
            insert_node_cmd(&head);
        }
        if (ch =='S'){
            shortsPath_cmd(head);
        }
        if (ch =='D'){
            delete_node_cmd(&head);
        }
        if (ch =='T'){
            TSP_cmd(head);
        }
        
    }
    deleteGraph_cmd(&head);
    return 0;
}