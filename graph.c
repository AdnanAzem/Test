#include "graph.h"
#include<stdio.h>
#include<stdlib.h>
#define infinity 1000000
void deleteGraph_cmd(pnode *head) {
	pnode current = *head;
	pnode next;
	while (current != NULL) {
		pedge signaledge = current->edges;
		while (signaledge != NULL) {
			pedge Redge = signaledge->next;
			free(signaledge);
			signaledge = Redge;
			
		}
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
	
}
pnode searchNode(pnode *head, int key) {
	pnode search = *head;
	while (search != NULL) {
		if (search->node_num >= 0) {
			if (search->node_num == key) {
				return search;
			}
			search = search->next;
		}
	}
	return NULL;
}


void insert_node_cmd(pnode *head) {
	int idSrc, idDest, weight;
	char stop = 0;
	scanf("%d", &idSrc);
	pnode NodeSrc = searchNode(head, idSrc);
	if (NodeSrc == NULL) {
		NodeSrc = (pnode)malloc(sizeof(node));
		if (NodeSrc == NULL) {
			return;
		}
		else {
			NodeSrc->node_num = idSrc;
			NodeSrc->edges = NULL;
			NodeSrc->next = *head;
			*head = NodeSrc;
		}
	}
	else {
		pedge Edge = NodeSrc->edges;
		while (Edge != NULL) {
			pedge temp = Edge->next;
			free(Edge);
			Edge = temp;
		}
		NodeSrc->edges = NULL;

	}
	int check =scanf("%d", &idDest);
	if (idDest >= 0) {
		while (check!=0&&stop != 'n' && stop != EOF&&stop != 'B') {
			pnode NodeDest = searchNode(head, idDest);
			if (NodeDest == NULL) {
				NodeDest = (pnode)malloc(sizeof(node));
				if (NodeDest == NULL) {
					return;
				}
				else {
					NodeDest->node_num = idDest;
					NodeDest->edges = NULL;
					NodeDest->next = *head;
					*head = NodeDest;
				}
			}
			scanf("%d", &weight);
			if (NodeSrc->edges == NULL) {
				NodeSrc->edges = (pedge)malloc(sizeof(edge));
				if (NodeSrc->edges == NULL) {
					return;
				}
				NodeSrc->edges->endpoint = NodeDest;
				NodeSrc->edges->weight = weight;
				NodeSrc->edges->next = NULL;
			}
			else {
				pedge e = NodeSrc->edges;
				NodeSrc->edges = NodeSrc->edges->next;
				NodeSrc->edges = (pedge)malloc(sizeof(edge));
				if (NodeSrc->edges == NULL) {
					return;
				}
				NodeSrc->edges->endpoint = NodeDest;
				NodeSrc->edges->weight = weight;
				NodeSrc->edges->next = e;

			}
			scanf("%c", &stop);
			scanf("%c", &stop);
			idDest = (stop)-'0';
		}
	}
}
void insert_node_cmd2(pnode *head) {
	int idSrc, idDest, weight;
	scanf("%d", &idSrc);
	pnode NodeSrc = searchNode(head, idSrc);
	if (NodeSrc == NULL) {
		NodeSrc = (pnode)malloc(sizeof(node));
		if (NodeSrc == NULL) {
			return;
		}
		else {
			NodeSrc->node_num = idSrc;
			NodeSrc->edges = NULL;
			NodeSrc->next = *head;
			*head = NodeSrc;
		}
	}
	else {
		pedge Edge = NodeSrc->edges;
		while (Edge != NULL) {
			pedge temp = Edge->next;
			free(Edge);
			Edge = temp;
		}
		NodeSrc->edges = NULL;

	}
		while (scanf("%d", &idDest)) {
			pnode NodeDest = searchNode(head, idDest);
			if (NodeDest == NULL) {
				NodeDest = (pnode)malloc(sizeof(node));
				if (NodeDest == NULL) {
					return;
				}
				else {
					NodeDest->node_num = idDest;
					NodeDest->edges = NULL;
					NodeDest->next = *head;
					*head = NodeDest;
				}
			}
			scanf("%d", &weight);
			if (NodeSrc->edges == NULL) {
				NodeSrc->edges = (pedge)malloc(sizeof(edge));
				if (NodeSrc->edges == NULL) {
					return;
				}
				NodeSrc->edges->endpoint = NodeDest;
				NodeSrc->edges->weight = weight;
				NodeSrc->edges->next = NULL;
			}
			else {
				pedge e = NodeSrc->edges;
				NodeSrc->edges = NodeSrc->edges->next;
				NodeSrc->edges = (pedge)malloc(sizeof(edge));
				if (NodeSrc->edges == NULL) {
					return;
				}
				NodeSrc->edges->endpoint = NodeDest;
				NodeSrc->edges->weight = weight;
				NodeSrc->edges->next = e;

			}
		
	}
}

void build_graph_cmd(pnode *head) {
	deleteGraph_cmd(head);
	int sizeNode;
	char ch;
	scanf("%d", &sizeNode);
	scanf("%c", &ch);
	scanf("%c", &ch);
	while (sizeNode > 0) {
		insert_node_cmd(head);
		sizeNode--;
	}


}
void printGraph_cmd(pnode head) {
	pnode temp = head;
	while (temp != NULL)
	{
		printf("The Node is %d -> ", temp->node_num);
		pedge tempEdge = temp->edges;
		while (tempEdge != NULL)
		{
			printf("dest %d  weight for edge: %d-> ", tempEdge->endpoint->node_num, tempEdge->weight);
			tempEdge = tempEdge->next;
		}
		printf("\n");
		temp = temp->next;
	}
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
		if (temp->weight <= minweight&&temp->tag == 0) {
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
int shortsPath_cmd(pnode head, int src, int dest) {
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
		if (searchNode(&head, min)->edges != NULL) {
			pedge e = searchNode(&head, min)->edges;
			if (e != NULL) {
				while (e != NULL) {
					int currentWeight = searchNode(&head, e->endpoint->node_num)->weight;
					int eWeight = e->weight;
					int srcPlusEdge = searchNode(&head, min)->weight + eWeight;
					if (srcPlusEdge < currentWeight) {
						setWeight(&head, e->endpoint->node_num, srcPlusEdge);

					}
					e = e->next;
				}
			}
		}
		searchNode(&head, min)->tag = 1;//visit the node
		temp2 = temp2->next;
	}
	if (searchNode(&head, dest)->weight == infinity)
		return -1;
    return searchNode(&head, dest)->weight;

}
void TSP_cmd(pnode head) {
	int sizeTsp;
	int *arr;
	scanf("%d", &sizeTsp);
	arr = (int*)malloc(sizeTsp * sizeof(int));
	if (arr == NULL) {
		return;
	}
	int i = 0;
	while (i< sizeTsp) {
		scanf("%d", &arr[i]);
		i++;
	}
	int sum = 0;
	for (i = 0; i < sizeTsp - 1; i++) {
		sum += shortsPath_cmd(head, arr[i], arr[i + 1]);
	}
	printf("TSP shortest path: %d\n", sum);
	free(arr);
}

