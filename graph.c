#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void build_graph_cmd(pnode *head)
{
    deleteGraph_cmd(head);
    int size = 0;
    scanf("%d", &size);
    char n = 'B';
    scanf("%c", &n);
    for (int i = 0; i < size; ++i)
    {
        scanf("%c", &n);
        insert_node_cmd(head);
    }
}

pnode getNode(pnode *head, int id)
{
    pnode index = *head;
    while (index != NULL)
    {
        if (index->node_num == id)
        {
            return index;
        }
        index = index->next;
    }
    return NULL;
}

void insert_node_cmd(pnode *head)
{
    int id = -1;
    scanf("%d", &id);
    pnode src = getNode(head, id);

    if (src == NULL)
    {
        src = (pnode)malloc(sizeof(node));
        if (src == NULL)
        {
            return;
        }
        src->node_num = id;
        src->next = *head;
        src->edges = NULL;
        *head = src;
    }
    else
    {
        pedge index = src->edges;
        while (index != NULL)
        {
            pedge temp = index->next;
            free(index);
            index = temp;
        }
        src->edges = NULL;
    }
    pedge *lastEdge = &(src->edges);
    int dest = -1;
    int isDone = scanf("%d", &dest);
    while (isDone != 0 && isDone != EOF)
    {
        pnode destNode = getNode(head, dest);
        if (destNode == NULL)
        {
            destNode = (pnode)malloc(sizeof(node));
            if (destNode == NULL)
            {
                return;
            }
            destNode->node_num = dest;
            destNode->edges = NULL;
            destNode->next = *head;
            *head = destNode;
        }
        int weight = -1;
        scanf("%d", &weight);

        *lastEdge = (pedge)malloc(sizeof(edge));
        if ((*lastEdge) == NULL)
        {
            return;
        }
        (*lastEdge)->endpoint = destNode;
        (*lastEdge)->weight = weight;
        (*lastEdge)->next = NULL;
        lastEdge = &((*lastEdge)->next);
        isDone = scanf("%d", &dest);
    }
}
void printGraph_cmd(pnode head)
{
    pnode nodeIndex = head;
    while (nodeIndex != NULL)
    {
        printf("Node %d: ", nodeIndex->node_num);
        pedge edgeIndex = nodeIndex->edges;
        while (edgeIndex != NULL)
        {
            printf("dest %d: weight %d, ", edgeIndex->endpoint->node_num, edgeIndex->weight);
            edgeIndex = edgeIndex->next;
        }
        printf("\n");
        nodeIndex = nodeIndex->next;
    }
}
void deleteGraph_cmd(pnode *head)
{
    pnode nodeIndex = *head;
    while (nodeIndex != NULL)
    {
        pedge edgeIndex = nodeIndex->edges;
        while (edgeIndex != NULL)
        {
            pedge temp = edgeIndex;
            edgeIndex = edgeIndex->next;
            free(temp);
        }
        pnode temp = nodeIndex;
        nodeIndex = nodeIndex->next;
        free(temp);
    }
    *head = NULL;
}
void delete_node_cmd(pnode *head)
{
    int key = -1;
    scanf("%d", &key);
    pnode nodeIndex = *head;
    pnode *isFirst = NULL;
    pnode prevAns = NULL;
    if (nodeIndex->node_num == key)
    {
        isFirst = head;
    }

    while (nodeIndex != NULL)
    {
        if (nodeIndex->next != NULL && nodeIndex->next->node_num == key)
        {
            prevAns = nodeIndex;
        }
        if (nodeIndex->edges != NULL && nodeIndex->edges->endpoint->node_num == key)
        {
            pedge temp = nodeIndex->edges;
            nodeIndex->edges = nodeIndex->edges->next;
            free(temp);
            nodeIndex = nodeIndex->next;
            continue;
        }
        pedge edgeIndex = nodeIndex->edges;
        if (edgeIndex != NULL)
        {
            while (edgeIndex->next != NULL)
            {
                if (edgeIndex->next->endpoint->node_num == key)
                {
                    pedge temp = edgeIndex->next;
                    edgeIndex->next = temp->next;
                    free(temp);
                }
                else
                {
                    edgeIndex = edgeIndex->next;
                }
            }
        }
        nodeIndex = nodeIndex->next;
    }

    if (isFirst != NULL)
    {
        pedge edgeIndex = (*isFirst)->edges;
        while (edgeIndex != NULL)
        {
            pedge temp = edgeIndex;
            edgeIndex = edgeIndex->next;
            free(temp);
        }
        pnode temp = *isFirst;
        *isFirst = temp->next;
        free(temp);
    }
    else if (prevAns != NULL)
    {
        pnode remove = prevAns->next;
        pedge edgeIndex = remove->edges;
        while (edgeIndex != NULL)
        {
            pedge temp = edgeIndex;
            edgeIndex = edgeIndex->next;
            free(temp);
        }
        prevAns->next = remove->next;
        free(remove);
    }
}

int findminNode(pnode *head) {
	pnode temp = *head;
	int minweight = infinity;
	int id = 1;
	while (temp != NULL) {
			if (temp->weight <= minweight&&temp->tag==0) {
				minweight = temp->weight;
				id = temp->node_num;
			}
		temp = temp->next;
	}
	return id;
}


void setWeight(pnode *head, int key, int weight) {
	pnode temp = *head;
	while (temp != NULL) {
		if (temp->node_num == key) {
			temp->weight = weight;
		}
		temp = temp->next;
	}
}


/*
void shortsPath_cmd(pnode head) {
	int src, dest;
	scanf("%d", &src);
	scanf("%d", &dest);
	pnode temp = head;
	pnode temp2 = head;
   while (temp != NULL) {
      temp->weight = infinity;//set the weight for Node not for edge.
	  temp->tag = 0;//this for check if visit this node
		temp = temp->next;
	}
	setWeight(&head, src, 0);//set the weight for Node not for edge.
	while (temp2 != NULL) {
		int min = findminNode(&head);
		if (getNode(&head, min)->edges != NULL) {
			pedge e = getNode(&head, min)->edges;
			if (e != NULL) {
				while (e != NULL) {
					int currentWeight = getNode(&head, e->endpoint->node_num)->weight;
					int eWeight = e->weight;
					int srcPlusEdge = getNode(&head, min)->weight + eWeight;
					if (srcPlusEdge < currentWeight) {
						setWeight(&head,e->endpoint->node_num, srcPlusEdge);
						
					}
					e = e->next;
				}
			}
		}
		getNode(&head, min)->tag = 1;//visit the node
		temp2 = temp2->next;
	}
	if (getNode(&head, dest)->weight > 0) {
		printf("Dijsktra shortest path: %d\n", getNode(&head, dest)->weight);
	}
	else {
		printf("Dijsktra shortest path: -1\n");
	}

}
*/
int shortsPath_cmd2(pnode head,int src ,int dest) {
	pnode temp = head;
	pnode temp2 = head;
	while (temp != NULL) {
		temp->weight = infinity;//set the weight for Node not for edge.
		temp->tag = 0;//this for check if visit this node
		temp = temp->next;
	}
	setWeight(&head, src, 0);//set the weight for Node not for edge.
	while (temp2 != NULL) {
		int min = findminNode(&head);
		if (getNode(&head, min)->edges != NULL) {
			pedge e = getNode(&head, min)->edges;
			if (e != NULL) {
				while (e != NULL) {
					int currentWeight = getNode(&head, e->endpoint->node_num)->weight;
					int eWeight = e->weight;
					int srcPlusEdge = getNode(&head, min)->weight + eWeight;
					if (srcPlusEdge < currentWeight) {
						setWeight(&head, e->endpoint->node_num, srcPlusEdge);

					}
					e = e->next;
				}
			}
		}
		getNode(&head, min)->tag = 1;//visit the node
		temp2 = temp2->next;
	}
	return getNode(&head, dest)->weight;
	
}
/*
void TSP_cmd(pnode head) {
	int sizeTsp;
	int *arr;
	scanf("%d", &sizeTsp);
	arr= (int*)malloc(sizeTsp * sizeof(int));
	if (arr == NULL) {
		return;
	}
	int i =0;
	while (i< sizeTsp) {
		scanf("%d", &arr[i]);
		i++;
	}
	int sum=0;
	for (i = 0; i < sizeTsp-1; i++) {
		sum += shortsPath_cmd2(head, arr[i], arr[i + 1]);
	}
	printf("TSP shortest path: %d\n", sum);
	free(arr);
}
*/
int TSP_cmd(pnode head) {
	int sizeTsp;
	int *arr;
	scanf("%d", &sizeTsp);
	arr= (int*)malloc(sizeTsp * sizeof(int));
	if (arr == NULL) {
		return -1;
	}
	int i =0;
	while (i< sizeTsp) {
		scanf("%d", &arr[i]);
		i++;
	}
	int sum=0;
	for (i = 0; i < sizeTsp-1; i++) {
		sum += shortsPath_cmd2(head, arr[i], arr[i + 1]);
	}
	//printf("TSP shortest path: %d\n", sum);
	free(arr);
    return sum;
}