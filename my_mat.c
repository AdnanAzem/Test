
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Dijkstra(int s);
#define N 10
#define MAX 100
#define TEMP 0
#define PERM 1
#define infinity 9999
#define NIL -1

int adj[N][N];
//int** adj;
int predecessor[N];   /*predecessor of each vertex in shortest path*/
int pathLength[N];
int status[N];

//int mat[N][N];
int min(int a, int b) {
	if (a<b) return a;
	else 
		return b;
}

void floydWarshalle(int mat[][N]) {
	
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (mat[i][j]&&mat[i][k] != 0 &&mat[k][j] != 0) {
					mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
				}
				else if(i!=j&&mat[i][j]==0&&mat[i][k]!=0&&mat[k][j]!=0){
                        mat[i][j]=mat[i][k]+mat[k][j];
				}
			}
		}
	}
}

void buildGraph()
{
        int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			scanf("%d", &adj[i][j]);
		}
	}

    floydWarshalle(adj);

}

/*

void isThereConnection(){
    int x,y;
    scanf("%d%d",&x, &y);
    if(adj[x][y] != 0){
        printf("True\n");
    }
    else{
        printf("False\n");
    }
}
*/



int min_temp( )
{
        int i;
        int min = infinity;
        int k = NIL;
        for(i=0;i<N;i++)
        {
                if(status[i] == TEMP && pathLength[i] < min)
                {
                        min = pathLength[i];
                        k = i;
                }
        }
        return k;
}/*End of min_temp( )*/


void Dijkstra( int s)
{
        int i,current;

        /* Make all vertices temporary */
        for(i=0; i<N; i++)
        {
                predecessor[i] =  NIL;
                pathLength[i] = infinity;
                status[i] = TEMP;
        }
        /* Make pathLength of source vertex equal to 0 */
        pathLength[s] = 0;

        while(1)
        {
                /*Search for temporary vertex with minimum pathLength
                and make it current vertex*/
                current = min_temp( );

                if( current == NIL )
                        return;

                status[current] = PERM;

                for(i=0; i<N; i++)
                {
                        /*Checks for adjacent temporary vertices */
                        if ( adj[current][i] !=0 && status[i] == TEMP )
                                if( pathLength[current] + adj[current][i] < pathLength[i] )
                                {
                                        predecessor[i] = current;  /*Relabel*/
                                        pathLength[i] = pathLength[current] + adj[current][i];
                                }
                }
        }
}/*End of Dijkstra( )*/


int findPath(int s, int v )
{
        int i,u;
        int path[N];          /*stores the shortest path*/
        int shortdist = 0;      /*length of shortest path*/
        int count = 0;          /*number of vertices in the shortest path*/

        /*Store the full path in the array path*/
        while( v != s )
        {
                count++;
                path[count] = v;
                u = predecessor[v];
                shortdist += adj[u][v];
                v = u;
        }
        count++;
        path[count]=s;

        //printf("%d\n", shortdist);
        return shortdist;
        
}/*End of findPath()*/



void shortPath(){
    int x,y;
    scanf("%d",&x);
    scanf("%d",&y);

    //Dijkstra(x);

    if(x == y){
        printf("-1\n");
    }
    else{
        printf("%d\n",findPath(x,y));
    }
  
}

void isThereConnection(){
    int x,y;
    scanf("%d",&x);
    scanf("%d",&y);
    //Dijkstra(x);

    if (adj[x][y] != 0)
    {
        printf("True\n");
    }
    else{
        if(findPath(x,y) != 0){
        printf("True\n");
    }
    else{
        printf("False\n");
    }
    }
}
