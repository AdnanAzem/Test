#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "algo.h"


#define INF 9999
#define MAX 10
//int arr[10][10], completed[10], n, cost = 0;
int tspAns;

#define null 0

pnode getNode(pnode *head, int id) {
    pnode i = *head;
    while (i != NULL) {
        if (i->node_num == id) {
            return i;
        } else {
            i = i->next;
        }
    }
    return NULL;
}

void insert_node_cmd(pnode *head) {
    int id = -1;
    scanf("%d", &id);
    pnode n = getNode(head, id);

    if (n == NULL) {
        n = (pnode) malloc(sizeof(node));
        n->node_num = id;
        n->edges = NULL;
        n->next = *head; //put n befor head
        *head = n; // set n to be new head
    } else { //if node exist - delete edges out
        pedge e = n->edges;
        while (e != NULL) {
            pedge t = e->next;
            free(e);
            e = t;
        }
    }
    pedge *e = &(n->edges);
    int destid = -1;
    while (scanf("%d", &destid) != null) {
        if (destid == 'n') {
            break;
        }
        pnode dest = getNode(head, destid);
        if(dest == NULL) { //if not exist
            dest = (pnode) malloc(sizeof(node));
            dest->node_num = destid;
            dest->edges = NULL;
            dest->next = *head; //put n befor head
            *head = dest; // set n to be new head
        }
        //connect

        int w = -1;
        scanf("%d", &w);
        *e = (pedge)malloc(sizeof(edge));
        (*e)->endpoint = dest;
        (*e)->weight = w;
        (*e)->next = NULL;
        e = &((*e)->next);
    }
}

void delete_node_cmd(pnode *head){
    int id = 0;
    scanf("%d",&id);
    delete_edge(head,id);
    pnode i = *head;
    node *ptr = NULL;
    if(i->node_num != id){
        while (i->next->node_num != id){
            i = i->next;
        }
        ptr = i->next;
        i->next=i->next->next;
        free_edges(ptr);
        free(ptr);
    }
    else{
        ptr = *head;
        *head = ptr->next;
        free_edges(ptr);
        free(ptr);
    }
}


void free_edges(pnode ptr){
    if(ptr->edges!=NULL){
        pedge temp = ptr->edges;

        while(temp->next!=NULL){
            pedge p1 = NULL;
            p1 = temp;
            temp = temp->next;
            free(p1);
        }
    }
}

void delete_edge(pnode *head,int id){
    pnode i = *head;
    while (i != NULL){
        if(i->node_num != id && i->edges != NULL){
            if(i->edges->endpoint->node_num != id){
                pedge tempEdge = i->edges;
                while (tempEdge->next!= NULL){
                    if(tempEdge->next->endpoint->node_num == id){
                        pedge p1 = tempEdge->next;
                        tempEdge->next=tempEdge->next->next;
                        free(p1);
                        break;
                    }
                    tempEdge = tempEdge->next;
                }
            }
            else{
                if(i->edges->next == NULL){
                    pedge p1 = i->edges;
                    i->edges = NULL;
                    free(p1);
                }
                else{
                    pedge p1 = i->edges;
                    i->edges = p1->next;
                    free(p1);
                }
            }
        }
        i = i->next;
    }
}

void build_graph_cmd(pnode *head) {
    deleteGraph_cmd(head);
    int nodesize = null;
    scanf("%d", &nodesize);
    char n = 'n';
    scanf("%c", &n);
    for (int i = 0; i < nodesize; i++) {
        scanf("%c", &n);
        insert_node_cmd(head);
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

void deleteGraph_cmd(pnode *head) {
    while (*head != NULL) {
        delete_node_cmd(head);
    }
}

int dijkstra(int cost[MAX][MAX], int src, int dest) {
    int dist[MAX], prev[MAX], selected[MAX] = {0};
    char path[MAX];
    for (int i = 0; i < MAX; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    int start = src;
    selected[start] = 1;
    dist[start] = 0;
    while (selected[dest] == 0) {
        int min = INF;
        int m = 0;
        for (int i = 0; i < MAX; i++) {
            int d = dist[start] + cost[start][i];
            if (d < dist[i] && selected[i] == 0) {
                dist[i] = d;
                prev[i] = start;
            }
            if (min > dist[i] && selected[i] == 0) {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    return dist[dest];

}

int findminNode(pnode *head) {
	pnode temp = *head;
	int minweight = INF;
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



void shortsPath_cmd(pnode head) {
	int src, dest;
	scanf("%d", &src);
	scanf("%d", &dest);
	pnode temp = head;
	pnode temp2 = head;
   while (temp != NULL) {
      temp->weight = INF;//set the weight for Node not for edge.
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
int shortsPath_cmd2(pnode head,int src ,int dest) {
	pnode temp = head;
	pnode temp2 = head;
	while (temp != NULL) {
		temp->weight = INF;//set the weight for Node not for edge.
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
