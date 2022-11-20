#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Structs establishment
typedef struct Tree Tree;
typedef struct treeNode fileInfo;
typedef struct treeInfo treeInfo;

struct treeInfo // Binary tree information in node struct
{
    int id;
    char route [100]; // projectGraph->task5->file3; scanf("projectGraph->task%d->file%d", i, j); 
    char description [40];
    char type [10]; 
};


struct treeNode // (fileInfo) Binary tree node struct
{
    fileInfo *right;
    fileInfo *left;
    fileInfo *father;
	treeInfo treeInfo;

    int factorEQ;
};


struct Tree // Binary tree struct
{
	fileInfo *root;
};


typedef struct resources resources;
typedef struct resourcesNode resourcesNode;
typedef struct resourceInfo resourceInfo;


struct resourceInfo // Resources information in node struct
{ 
	int id;
	char resourceName[50];
	char resourceType[50];
	char managerName[100];
	int capacity;
	int quantity;
};

struct resourcesNode // Resources (double list) node struct
{
	resourceInfo resourceInfo;
	resourcesNode *next; 
};

struct resources // Resources double list struct
{ 
	resourcesNode *first;
};

typedef struct graphVertex graphVertex;
typedef struct taskInfo taskInfo;

struct taskInfo{
	int id;
	char description[100];
	char type[20];
	char managerName[100];
	int effort;
	int time;	
};

struct graphVertex // Task information in vertex node struct
{
    Tree files;
    resources* resourcesList;
    taskInfo taskInfo;
};


// Graph structures
typedef struct Graph Graph;
typedef struct List Stack; // Pila
typedef struct edge edge;


struct Graph // Graph struct
{
	char taskName[50]; 
	Graph* next;
	edge* adjacency;

    graphVertex* task;

	int visited, finished;
    int amount;
	char previousTask[50];
};

struct edge // Edges of the graph struct
{
	Graph* task; 
	edge*next;
	int effortRequired;
};

struct List // Graph struct
{
	Graph* data;
	Stack* next;
};

int projectTasks;
char tasks[500];
fileInfo *raiz=NULL;
Graph*start = NULL;
Stack* initial = NULL;
Stack* end = NULL;


// ANDRE´S CODE

/*
void preOrder(fileInfo* taskFile, int i) { //Receives the address of the file root of the task
    FILE* file = fopen("ProjectInfo.csv", "w+");//Open the file to continue typing
	
    if (taskFile!= NULL) {//Evaluate if the node exists
        fprintf(file,"%d,projectGraph->task%s->file%d,%s,%s\n",taskFile->treeInfo.id,i,taskFile->treeInfo.id,taskFile->treeInfo.description, taskFile->treeInfo.type); //Escribe en ProjectInfo toda la información de la tarea
        preOrder(taskFile->left,i); //Recursive call to enter left node
        preOrder(taskFile->right,i); //Recursive call to enter right node
    }
	fclose(file); 
}

void keepInfo(){
    Graph*projectGraph = start;
    FILE* file = fopen("ProjectInfo.csv", "w+"); //Open the ProjectInfo file to add information
    resourcesNode* aux;
    int i;
    for(i=0; i < projectTasks; i++){ //Stops until all nodes of the task graph have been visited, increases by 1 per task visited
        fprintf(file,"%d\n", i+1);

        fprintf(file,"%s\n", projectGraph->taskName);

        fprintf(file,"taskInfo:\n");
        fprintf(file,"%d,%s,%s,%s,%d,%d\n\n", projectGraph->task->taskInfo.id, projectGraph->task->taskInfo.description, projectGraph->task->taskInfo.managerName, projectGraph->task->taskInfo.effort,projectGraph->task->taskInfo.time); //The task information is printed on ProjectInfo 

        fprintf(file,"files:\n");

        if(projectGraph->task->files.root!=NULL){
           preOrder(projectGraph->task->files.root, i); //Send task file root information
        } 

        aux = projectGraph->task->resourcesList->first;//Points to the top of the list
        fprintf(file,"\nresources:\n");
        if(aux != NULL){ //Go through the list to the end
            while (aux!=NULL)
            {
                fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%d\n"); //Adds the information of each resource to ProjectInfo
                aux = aux->next; // Advance aux to the next node
            }
        }
        fprintf(file,"\n//\n");
		if(projectGraph->task != NULL){
        	projectGraph = projectGraph->next;
		}
		else{
			break;
		}

    }
    fclose(file); //Close ProjectInfo by finishing the file modifications
}

*/

// Starting functions --------------------------------------------------------------------------------------

// FUNCIONAL
void keepInfo(){
	Graph* projectGraph = start;
    int i;
    FILE* file;
	file = fopen("ProjectInfo.csv", "a"); //Open the ProjectInfo file to add information
    for(i=0; i <= projectTasks; i++){
        fprintf(file,"%d\n", i+1);
	    fprintf(file,"taskInfo:\n");
	    fprintf(file,"%d,%s,%s,%d,%d\n\n", projectGraph->task->taskInfo.id, projectGraph->task->taskInfo.description, projectGraph->task->taskInfo.managerName, projectGraph->task->taskInfo.effort, projectGraph->task->taskInfo.time); //The task information is printed on ProjectInfo

		fprintf(file,"resources: \n");
		//projectGraph->task->resourcesList = keepResources(projectGraph);

        if(projectGraph->next != NULL){
            projectGraph = projectGraph->next;
        }
        else{
            break;
        }

    }
    fclose(file); //Close ProjectInfo by finishing the file modifications
    return;
}
