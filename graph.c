#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <malloc.h>
#include <math.h>
#include <limits.h>

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
}/*
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
*/





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

/*
int shortsPath_cmd(pnode head,int src ,int dest) {
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
*/


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
/*
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
    if(sum >= infinity)
    return -1;
    return sum;
}
*/


int dijkstra(pnode* head , int src , int dest , int bool){
    int max = INT_MIN;
    pnode temp = *head;
    while(temp){
        if(temp->node_num >max){
            max= (temp->node_num);
        }
        temp = temp->next;
    }
    int *Queue = (int*) malloc(sizeof (int) * (max+1));
    int *dist = (int*) malloc(sizeof (int) * (max+1));
    if((!Queue) || (!dist)){
        return -1;
    }
    temp = *head;
    for (int i = 0; i <max+1 ; ++i) {
        dist[i] = INT_MAX;
        Queue[i] = -1;//want to make sure when i add nodes whichever index dosent hold a node will be -1
    }
    dist[src]=0;

    while(temp){//filling queue with nodes
        int index = temp->node_num;
        Queue[index]=1;
        temp = temp->next;
    }

    while(1){
        //the next 8 rows of code is my way to check if queue is empty
        int min = INT_MAX;
        int curr_node_id = -1;
        for (int i = 0; i <max+1; ++i) {
            if(Queue[i]==1){//only if queue[i] is 1 then that i node exits and we can
                if(dist[i]<min){
                    min = dist[i];
                    curr_node_id = i;//if its the min distance then i will work on this node
                }
            }
        }
        if(min==INT_MAX){
            break;
        }
        Queue[curr_node_id]=-1; //remove node from queue
        temp= *head;
        //This next loop will find the node we want to work on and temp will hold that node.
        //once we found that node we break and iterate over temps neighbors which are still in Queue
        while(temp){
            if(temp->node_num==curr_node_id){
                break;
            }
            temp=temp->next;
        }
        //in each iteration we will hold an edge coming out of temp and the node at the end of that edge\
        //meaning the node which is temps neighbor
        pedge edge_of_neighbor = temp->edges;
        while(edge_of_neighbor){
            int neighbors_id = edge_of_neighbor->endpoint->node_num;
            int alternative = dist[curr_node_id]+ (edge_of_neighbor->weight);
            if(alternative<dist[neighbors_id]){
                dist[neighbors_id]= alternative;
            }
            edge_of_neighbor = edge_of_neighbor->next;
        }
    }
    if(bool){
        if(dist[dest]!=INT_MAX){
            printf("%d \n" , dist[dest]);
        }
        else{
            int a = -1;
            printf("%d \n" , a);
        }
    }
    free(Queue);
    int ret = dist[dest];
    free(dist);
    return  ret;
}

void swap(int *x, int *y) {
    int c;
    c = *x;
    *x = *y;
    *y = c;
}


int factorial(int size){
    if(size < 0) return 0;
    if(size == 0) return 1;
    return factorial(size-1)*size;
}

int arrayDijkstra(pnode *head,int values[], int size){
    int dist = 0;
    for (int i = 0; i < size-1; ++i) {
        int dijk = dijkstra(head,values[i],values[i+1],0);
        if(dijk == INT_MAX){
            return INT_MAX;
        }
        dist += dijk;
    }
    return dist;
}

int min(const int arr[],int n){
    int index = 0;
    for (int i = 1; i <n; ++i) {
        if(arr[i]<arr[index]){index = i;}
    }
    return index;
}


void permutation(pnode *head, int *values, int right, int left ,int *permutat, int *n){
    if(right == left){
        permutat[(*n)++] = arrayDijkstra(head, values, left+1);
        return;
    }
    for (int i = right; i <=left; ++i) {
        swap((values + i), (values + right));
        permutation(head,values,right+1,left,permutat,n);
        swap((values+i),(values+right));
    }
}

void TSP_cmd(pnode *head){
    int NumberOfNodes = 0;
    scanf("%d", &NumberOfNodes);
    int values[NumberOfNodes];
    for (int i = 0; i < NumberOfNodes; ++i) {
        scanf("%d", &values[i]);
    }
    int f = factorial(NumberOfNodes);
    int permutations[f];
    int temp = 0;
    permutation(head,values,0,NumberOfNodes-1,permutations,&temp);
    int n = min(permutations,f);
    if(permutations[n] == INT_MAX){
        printf("TSP shortest path: %d \n",-1);
    }else{
        printf("TSP shortest path: %d \n",permutations[n]);
    }
}

