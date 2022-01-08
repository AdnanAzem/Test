#include"graph.h"
#include<stdio.h>
int main()
{
	pnode head = NULL;
	char select;
	
	while (scanf("%c", &select)!=0) {
		switch (select)
		{
		case 'A': {
			build_graph_cmd(&head);
			break;
		}
		case'B': {
			insert_node_cmd2(&head);
			break;
		}
		case 'D': {
			delete_node_cmd(&head);
			//printGraph_cmd(head);
			break;
		}
		case'S':
		{
			int src, dest;
			scanf("%d", &src);
			scanf("%d", &dest);
			int temp= shortsPath_cmd(head, src, dest);
			printf("Dijsktra shortest path: %d\n", temp);
			break;
		}
		case 'T': {
			TSP_cmd(head);
			break;
		}

		}
		
	}
	deleteGraph_cmd(&head);
	return 0;
}
