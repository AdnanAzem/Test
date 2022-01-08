#include <stdio.h>
#include "graph.h"
int main()
{
    pnode temp = NULL;
    pnode *head = &temp;
    char input = '\0';
    while (scanf("%c", &input) != EOF)
    {
        if (input == 'A')
        {
            build_graph_cmd(head);
        }
        else if (input == 'B')
        {
            insert_node_cmd(head);
        }
        else if (input == 'D')
        {
            delete_node_cmd(head);
        }
        else if (input == 'S')
        {
            /*
            int src = -1, dest = -1;
            scanf("%d %d", &src, &dest);
            int dis = shortsPath_cmd(*head, src, dest);
            printf("Dijsktra shortest path: %d \n", dis);
            */
           shortsPath_cmd(*head);
        }
        else if (input == 'T') {
            //int weight = TSP_cmd(*head);
            //printf("TSP shortest path: %d \n", weight);
            //TSP_cmd(*head);
             TSP_cmd(head);
        }
    }
    deleteGraph_cmd(head);
    return 0;
}

