#ifndef GRAPH_
#define GRAPH_
#define infinity 100000
typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int weight;
	int tag;
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

int findminNode(pnode *head);
void setWeight(pnode *head, int key, int weight);
//void free_edges(pnode ptr);
//void delete_edge(pnode *head,int id);
pnode getNode(pnode *head, int id);
int shortsPath_cmd(pnode head,int src ,int dest);
//void shortsPath_cmd(pnode head);









void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
//int shortsPath_cmd(pnode head, int src, int dest);
//int TSP_cmd(pnode head);
int shortest_path(pnode* head, int src, int dest);
//int TSP(pnode *head);
void tsp(pnode *head);
//void TSP_cmd(pnode head);
//pnode getNode(pnode *head, int id);

#endif