#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Classes establishment

typedef struct Tree Tree;
typedef struct treeNode treeNode;

struct treeNode
{
    int data;
    treeNode *right;
    treeNode *left;
};

struct Tree
{
	treeNode *root;
};



// Double list struct

typedef struct resources resources;
typedef struct resourcesNode resourcesNode;
typedef struct resourceInfo resourceInfo;

struct resourceInfo{
	int id;
	char resourceName[20];
	char resourceType[20];
	char manager[20];
	int capacity;
	int quantity;
};

struct resources{
	resourcesNode *first;
    resourcesNode *last;
};

struct resourcesNode{
	resourceInfo resourceInfo;
	resourcesNode *previous;
	resourcesNode *next; 
};


// BTS structures

typedef struct taskInfo taskInfo;
typedef struct managerName managerName;

struct managerName{
	char name[50];
	char surname1[30];
	char surname2[30];
};

struct taskInfo{
	int id;
	char description[10];
	char type[20];
	managerName managerName;
	int effort;
	int time;
};

// Graph structures

typedef struct task graphNode;
typedef struct Graph Graph;
typedef struct edge edge;


struct task // graph�s node
{
    int destiny;
    graphNode* next;
    taskInfo taskInfo;
    Tree files;
    resourceInfo resourceInfo;
    
};

struct Graph
{
    graphNode* head[20]; // An array of pointers to Node to represent an adjacency list
};


struct edge{
	int estimatedTime;
	int effortRequired;
    int source;
	int destiny;
};

// File structures
typedef struct fileInfo file;

typedef struct fileInfo{
    int id;
    char ruta [100];
    char description [40];
    char type [10]; 
    file *fileLeft;
    file *fileRight;
}


// Starting functions -----------------------------------------------------------------------------

/*
void registerNewTaskCSV(taskInfo taskInfo){
    FILE *file;
    file = fopen("tasksData.csv","a");
    fprintf(file, "%d,%s,%d, %s, %s, %s, %d, %s",taskInfo.id,taskInfo.description, taskInfo.effort, taskInfo.managerName.name, taskInfo.managerName.surname1, taskInfo.managerName.surname2, taskInfo.time, taskInfo.type);
    fprintf(file, "\n");
    fclose(file);
}
*/

Tree *newTree(void)
{
    Tree *newT;
    newT = (Tree *) malloc(sizeof(Tree));
    newT->root->right = NULL;
    newT->root->left = NULL;
    return newT;
}

treeNode* newTreeNode(int data)
{
    treeNode *newN;
    newN = (treeNode *) malloc(sizeof(treeNode));
    newN->right = NULL;
    newN->left=NULL;
    newN->data = data;
    return newN;
}


// Function to create an adjacency list from specified edges
Graph* createGraph(edge edges[], int n)
{
	int i, destiny, source;
    // allocate storage for the graph data structure
    Graph* graph = (Graph*)malloc(sizeof(Graph));
 
    // initialize head pointer for all vertices
    for (i = 0; i < 20; i++) {
        graph->head[i] = NULL;
    }
 
    // add edges to the directed graph one by one
    for (i = 0; i < n; i++)
    {
        // get the source and destination vertex
        source = edges[i].source;
        destiny = edges[i].destiny;
 
        // allocate a new node of adjacency list from source to dest
        graphNode* newNode = (graphNode*)malloc(sizeof(graphNode));
        newNode->destiny = destiny;
 
        // point new node to the current head
        newNode->next = graph->head[source];
 
        // point head pointer to the new node
        graph->head[source] = newNode;
    }
 
    return graph;
}

// MainMenu

int main(){
	return 0;
}

