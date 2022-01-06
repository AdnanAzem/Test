#ifndef GRAPH_
#define GRAPH_


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
void free_edges(pnode ptr);
void delete_edge(pnode *head,int id);
pnode getNode(pnode *head, int id);
int shortsPath_cmd2(pnode head,int src ,int dest);

void build_graph_cmd(pnode *head); //Done
void insert_node_cmd(pnode *head); //Done
void delete_node_cmd(pnode *head); //Done
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head); //Done
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);






#endif