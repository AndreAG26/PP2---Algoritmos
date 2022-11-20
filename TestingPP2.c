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

// Starting functions --------------------------------------------------------------------------------------



void keepInfo(){
	Graph* projectGraph = start;
    int i;
    resources* resourcesList;
    FILE* file;
	file = fopen("ProjectInfo.csv", "a"); //Open the ProjectInfo file to add information
    for(i=0; i <= projectTasks; i++){
        fprintf(file,"%d\n", i+1);
	    fprintf(file,"taskInfo:\n");
	    fprintf(file,"%d,%s,%s,%d,%d\n\n", projectGraph->task->taskInfo.id, projectGraph->task->taskInfo.description, projectGraph->task->taskInfo.managerName, projectGraph->task->taskInfo.effort, projectGraph->task->taskInfo.time); //The task information is printed on ProjectInfo

		fprintf(file,"resources: \n");
	    resourcesList = projectGraph->task->resourcesList;//Points to the top of the list
	    
	    if(resourcesList->first == NULL){ //Go through the list to the end
			fprintf(file, "No resources found \n");
	    }
		else{
			while(resourcesList->first != NULL){
		        fprintf(file, "%d,%s,%s,%s,%d,%d\n", resourcesList->first->resourceInfo.id,resourcesList->first->resourceInfo.resourceName, resourcesList->first->resourceInfo.resourceType, resourcesList->first->resourceInfo.managerName, resourcesList->first->resourceInfo.capacity, resourcesList->first->resourceInfo.quantity); //Adds the information of each resource to ProjectInfo
				resourcesList->first = resourcesList->first->next;				
			}
		}

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



/*
FUNCTION: len()

Inputs:
- number (int)

Outputs:
- counter (int)

Restrictions:
- The function don´t validate any restrictions

*/

int isNumber(char string[500]){
	int i;

	for (i = 0; i < strlen(string); i++)
	{	
		while(!isdigit(string[i])){
			if(!isdigit(string[i])) {
				printf("Please type a number for this input:");
				scanf("%s",&tasks);
			}
		}
		return 1;
	}
}

int len(int number){
	int quotient, divisor, counter;
	quotient = 0;
	divisor = 1;
	counter = 0;

	while (quotient !=1){
		counter++;
		divisor = divisor * 10;
		quotient = number / divisor; // divide the number by the divisor

		if (quotient == 1){
			counter = counter + 1; // the counter is increased by one
		}
		if (quotient < 1){
			quotient = 1;
		}
		if (number < 10){
			counter = 1; // the counter is set to 1
		}
	}
	return counter;
}


void searchTask(){
    char vertex[50];
    Graph*aux = start;
    if(start != NULL){
        fflush(stdin);
        printf("Type the task you want to search:");
        scanf("%s",&vertex);
        while(aux!=NULL){
            if(strcmp(aux->taskName,vertex) == 0){
                break;
            }
            aux=aux->next;
        }
        printf("\n%s\n",aux->taskName);
        if(aux==NULL){
            printf("Error: Vertex not found\n");
        }
    }
}



/*
FUNCTION: addTask()

Inputs:
- aux (graphVertex*)

Outputs:
- the vertex given in the parameters but with the task information given by the user

Restrictions:
- The function don´t validate any restrictions

*/


void modifyTask(Graph* aux){
	
	graphVertex* information;
	information = (graphVertex *) malloc(sizeof(graphVertex));
	int taskType, taskIndex;
	char description[50];
    char managerName[100];
	char type [1];

	int id = aux->task->taskInfo.id;
	information->taskInfo.id = id;

	printf ("\nWrite a new description for the task: ");
    gets(description);
	gets(description);
	while(strlen(description) > 50){
		printf("\nThe description is invalid, please write a description with a maximum of 50 characteres:");
		fgets(description,50,stdin);
	}
	strcpy(information->taskInfo.description, description);
    	
    printf ("\nWrite a new name for the manager: ");
	gets(managerName);
	while(strlen(managerName) > 50){
		printf("\nThe name is invalid, please write a description with a maximum of 50 characteres:");
		fgets(managerName,50,stdin);
	}
	strcpy(information->taskInfo.managerName, managerName);

	printf ("\nTask types:\n 1. Operative Task\n 2. Approvation Task\n 3. Contract Signing\n 4. Management Task\n 5. Changes");
	printf ("\nWrite the new task type: ");
	scanf ("%s",&type);
		while(strlen(type) > 1){
		printf("\nPlease type only one digit, a number between 1 and 5: ");
		scanf ("%s",&type);
	}
	if(isNumber(type) == 1){
		taskType = atoi(type);
		
		while(taskType >= 5){
			printf("\nPlease type a valid number command");
			scanf ("%s",&type);
			if(isNumber(type) == 1){
				taskType = atoi(type);
			}
		}
		if (taskType == 1){
			strcpy(information->taskInfo.type,"OperativeTask");
		}
		else if(taskType == 2){
			strcpy(information->taskInfo.type,"ApprovationTask");
		}
		else if(taskType == 3){
			strcpy(information->taskInfo.type,"ContractSigning");
		}
		else if(taskType == 4){
			strcpy(information->taskInfo.type,"ManagementTask");
		}
		else if(taskType == 5){
			strcpy(information->taskInfo.type,"Changes");
		}
	}

	printf ("\nWrite the task new effort: \n");
	scanf ("%d",&information->taskInfo.effort);
	while(information->taskInfo.effort > 20){ 
		printf("\nEffort exceeds the limit. Please write a number between 0 and 20: ");
		scanf ("%d",&information->taskInfo.effort);
	}

	printf ("\nWrite the task new time in hours: \n"); // Revisar si es un "float"
	scanf ("%d",&information->taskInfo.time);
	while(information->taskInfo.time > 24){ // ?
		printf("\nTime exceeds the limit. Please write a number between 0 and 24");
		scanf ("%d",&information->taskInfo.time);
	}
	aux->task=information;
	// No almacena aun porque se necesita leer el archivo antes
}


void selectTaskToModify(){
    Graph* aux;
	char name[50];
	int id;
	fflush(stdin);

    if(start != NULL){
        fflush(stdin);
		printf("Enter the name of the task to modify: ");
		scanf("%s",&name);
		printf("Enter the ID of the task to modify: ");
		scanf("%d",&name);
        while(aux!=NULL){
            if(strcmp(aux->taskName,name) == 0 && aux->task->taskInfo.id == id){
                modifyTask(aux);
            }
            aux=aux->next;
        }
        printf("\n%s\n",aux->taskName);
        if(aux==NULL){
            printf("Error: Vertex not found\n");
        }
    }
 
}


void addTask(Graph* aux){
	
	graphVertex* information;
	information = (graphVertex *) malloc(sizeof(graphVertex));
	int taskType, taskIndex, numberId, numberEffort, i;
	char description[50];
	char managerName[100];
	char type[1];
	char id[500];
	char effort[500];
	char time[48];

	printf("\n------------------------\n");
	printf ("\nWrite the task ID: ");
	gets (id);
	gets (id);
	while(strlen(id) > 500){
		printf("\nThe ID is so big, please write a ID with a maximum of 500 digits: ");
		fgets(id,500,stdin);
	}

	if(isNumber(id) == 1){
		information->taskInfo.id = atoi(id);
	}

	printf ("\nWrite a description for the task: ");
    gets(description);

	while(strlen(description) > 50){
		printf("\nThe description is invalid, please write a description with a maximum of 50 characteres: ");
		fgets(description,50,stdin);
	}
	strcpy(information->taskInfo.description, description);
    	
    printf ("\nWrite the name of the task manager: ");
	gets(managerName);

	while(strlen(managerName) > 100){
		printf("\nThe name is invalid, please write a description with a maximum of 50 characteres:");
		fgets(managerName,100,stdin);
	}
	strcpy(information->taskInfo.managerName, managerName);

	printf ("\nTASK TYPES:\n 1. Operative Task\n 2. Approvation Task\n 3. Contract Signing\n 4. Management Task\n 5. Changes");
	printf ("\nWrite the task type by a number: ");
	gets(type);
	while(strlen(type) > 1){
		printf("\nPlease type only one digit, a number between 1 and 5: ");
		fgets (type,1,stdin);
	}
	if(isNumber(type) == 1){
		taskType = atoi(type);
		
		while(taskType >= 5){
			printf("\nPlease type a valid number command");
			fgets (type,1,stdin);
			if(isNumber(type) == 1){
				taskType = atoi(type);
			}
		}
		if (taskType == 1){
			strcpy(information->taskInfo.type,"OperativeTask");
		}
		else if(taskType == 2){
			strcpy(information->taskInfo.type,"ApprovationTask");
		}
		else if(taskType == 3){
			strcpy(information->taskInfo.type,"ContractSigning");
		}
		else if(taskType == 4){
			strcpy(information->taskInfo.type,"ManagementTask");
		}
		else if(taskType == 5){
			strcpy(information->taskInfo.type,"Changes");
		}
	}

	printf ("\nWrite the task effort: "); 
	gets(effort);

	while(strlen(effort) > 48){ 
		printf("\nEffort exceeds the limit. Please write a number between 0 and 24: ");
		fgets(effort,48,stdin);
	}	
	if(isNumber(effort) == 1){
		information->taskInfo.effort = atoi(effort);
	}


	printf ("\nWrite the new task time in hours (FLOAT type not allowed): "); // Revisar si es un "float"
	gets(time);

	while(strlen(time) > 48){ // ?
		printf("\nTime exceeds the limit. Please write a number between 0 and 48: ");
		fgets(time,48,stdin);
	}
	if(isNumber(id) == 1){
		information->taskInfo.time = atoi(time);
	}

	aux->task = information;
	projectTasks++;
}

/*
FUNCTION: newTask()

Inputs:
- (void)

Outputs:
- a new vertex given in the parameters with the task information given by the user (void)

Restrictions:
- The function don´t validate any restrictions

*/

void newTask(){
    Graph* aux;
	Graph* newVertex = (Graph*)malloc(sizeof(Graph));
	fflush(stdin);
	system("cls");
	printf("Enter the new task name: ");
	scanf("%s",&newVertex->taskName);
	newVertex->next = NULL;
    newVertex->adjacency = NULL;
    newVertex->visited = newVertex->finished = 0;
    newVertex->amount=-1;
    strcpy(newVertex->previousTask,"0");
    addTask(newVertex);
    if(start==NULL){
        start = newVertex;
    }else{
        aux = start;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next = newVertex;
    }
	newVertex->task->files.root = NULL; // Por Andre
}

/*
FUNCTION: addEdge()

Inputs:
- aux (graphVertex*)
- aux2 (graphVertex*)
- newEdge (edge*)

Outputs:
- the edge given but with the adjacency of both vertex

Restrictions:
- The function don´t validate any restrictions

*/

void addEdge(Graph*aux, Graph*aux2, edge*newEdge){
    edge* a;
    if(aux->adjacency == NULL){   
	    aux->adjacency = newEdge;
        newEdge->task = aux2;
    }else{   
	    a=aux->adjacency;
        while(a->next != NULL)
            a = a->next;
        newEdge->task = aux2;
        a->next = newEdge;
    }
}

/*
FUNCTION: newEdge()

Inputs:
- (void)

Outputs:
- the edge given but with the adjacency of both vertex

Restrictions:
- The function don´t validate any restrictions

*/

void newEdge(){   
    char source[50], destiny[50], effortRequired[50];
    edge* newEdge=(edge*)malloc(sizeof(edge));
    newEdge->next=NULL;
    Graph* aux;
	Graph* aux2;
    if(start==NULL){
         printf("Error: The graph is empty\n");
         return;
    }
    fflush(stdin);
    printf("Type the name of the source task: ");
    gets(source);
	while(strlen(source) > 50){
		printf("\nThe source task is invalid, please write a source task between 0 and 50 ");
		fgets(source,50,stdin);
	}
	
    printf("Type the name of the destiny task: ");
    gets(destiny);
	while(strlen(destiny) > 50){
		printf("\nThe destiny task is invalid, please write a destiny task between 0 and 50 ");
		fgets(destiny,50,stdin);
	}
	
    printf("Type the effort required: ");
    gets(effortRequired);
	while(strlen(effortRequired) > 50){
		printf("\nThe required effort is invalid, please write a required effort between 0 and 50 ");
		fgets(effortRequired,50,stdin);
	}
	if(isNumber(tasks) == 1){
		newEdge->effortRequired = atoi(effortRequired);
	}	
    aux = start;
    aux2 = start;
    while(aux2 != NULL){
        if(strcmp(aux2->taskName, destiny) == 0){
            break;
        }
        aux2 = aux2->next;
    }
    if(aux2 == NULL){
    	printf("Error: Vertex not found\n");
    	return;
	}
    while(aux != NULL){
        if(strcmp(aux->taskName, source) == 0){
            addEdge(aux,aux2,newEdge);
            return;
        }
        aux = aux->next;
    }
    if(aux==NULL)
    	printf("Error: Vertex not found\n");
}

/*
FUNCTION: newResourceNode()

Inputs:
- information (resourceInfo)

Outputs:
- the new node added with the information (void)

Restrictions:
- The function don´t validate any restrictions

*/

resourcesNode* newResourceNode(resourceInfo information)
{
    resourcesNode *newN;
    newN = (resourcesNode *) malloc(sizeof(resourcesNode));
    newN->next = NULL;
	strcpy(newN->resourceInfo.resourceName,information.resourceName);
	strcpy(newN->resourceInfo.resourceType,information.resourceType);
	strcpy(newN->resourceInfo.managerName,information.managerName);
	newN->resourceInfo.id=information.id;
	newN->resourceInfo.capacity=information.capacity;
	newN->resourceInfo.quantity=information.quantity;
	return newN;
}


/*
FUNCTION: registerResource()

Inputs:
- resourcesList (resources*)
- information (resourceInfo)

Outputs:6
- resourcesList (resources)

Restrictions:
- The function don´t validate any restrictions

*/

resources* registerResource(resources* resourcesList, resourceInfo information){
	resourcesNode* newN = newResourceNode(information);
	resourcesNode* aux;

	if(resourcesList->first == NULL)
    {
        resourcesList->first = newN;
        resourcesList->first->next = NULL;
        printf("New resource save!\n");
		return resourcesList;
    }

    resourcesNode *node = resourcesList->first;
    while(node != NULL)
    {
        aux = node;
        node = node->next;
    }
	aux->next = newN;
	aux->next->next = NULL;
	printf("New resource saved!\n");
	return resourcesList;
}

/*
FUNCTION: addResource()

Inputs:
- task (graphVertex*)

Outputs:
- information with the data given by the user

Restrictions:
- The function don´t validate any restrictions

*/

void addResource(Graph* projectGraph){
	resourceInfo information;
    char name[50];
	char id[50];
    char capacity[50];
	char quantity[50];
	

	system("cls");
	printf ("\nWrite the resource ID: ");
	gets (id); // what is typed by the user is stored in the type int of information called "id"
	while(strlen(id) > 50){
		printf("\nResource ID is so big, please type an ID with a maximum of 50 digits:");
		fgets (id,50,stdin);
	}	
	if(isNumber(id) == 1){
		information.id = atoi(id);
	}

	printf ("\nWrite the new resource name: "); // prints in terminal "Write the new resource name"
	gets (information.resourceName);
	while(strlen(information.resourceName) > 50){
		printf("\nResource name is too long, please type a name with a maximum of 50 characteres:");
		fgets (information.resourceName,50,stdin);
	}

	printf ("\nWrite the resource type: ");
	gets(information.resourceType); // what is typed by the user is stored in the type int of information called "resourceType"
	while(strlen(information.resourceType) >= 50){
		printf("\nResource type is too long, please write a type with a maximum of 50 characteres: ");
		fgets (information.resourceType,50,stdin);
	}

	printf ("\nWrite the resource manager name: "); // prints in terminal "Write the new resource manager name: "
	gets(information.managerName);
	while(strlen(information.managerName) > 100){
		printf("\nResources manager name is too long, please write a name with a maximum of 100 characteres:");
		fgets(information.managerName,100,stdin);
	}

	printf ("\nWrite the resource capacity: ");
	gets (capacity); // what is typed by the user is stored in the type int of information called "capacity"
	while(strlen(capacity) > 50){ 
		printf("\nCapacity exceeds the limit. Please digit a capacity between 0 and 50");
		fgets (capacity,50,stdin);
	}
	if(isNumber(capacity) == 1){
		information.capacity = atoi(capacity);
	}

	printf ("\nWrite the resource quantity: "); // prints in terminal "Write the new resource capacity: "
	gets (quantity); 
	while(strlen(quantity) > 50){ 
		printf("\nCapacity exceeds the limit. Please type a number between 0 and 20");
		fgets (quantity,50,stdin);
	}
	if(isNumber(quantity) == 1){
		information.quantity = atoi(quantity);
	}

	if(projectGraph->task->resourcesList == NULL){
		projectGraph->task->resourcesList = (resources *) malloc(sizeof(resources));
		projectGraph->task->resourcesList->first = NULL;
	}

	registerResource(projectGraph->task->resourcesList,information); // call the function registerResource(), and send as parameters task and information
}


void newResource(){
    char vertex[50];
	char id[50];
	int numberID;
    Graph*aux = start;

    if(start != NULL){
        fflush(stdin);
        printf("Type the name of task where you want to add a resource: ");
        gets(vertex);
		while(strlen(vertex) > 50){
			printf("\nThe task name is invalid, please write the task name with a maximum of 50 characteres: ");
			fgets(vertex,50,stdin);
		}	

        printf("\nType the ID of the task where you want to add a resource: ");
        gets(id);
		while(strlen(id) > 50){
			printf("\nThe task id is invalid, please write the task id with a maximum of 50 characteres: ");
			fgets(id,50,stdin);
		}			
		if(isNumber(id) == 1){
			numberID = atoi(id);
		}
        while(aux!=NULL){
            if(strcmp(aux->taskName,vertex) == 0 && aux->task->taskInfo.id == numberID){
                addResource(aux);
				return;
            }
            aux = aux->next;
        }
        if(aux == NULL){
            printf("Error: Vertex not found\n");
			return;
        }
    }
}


fileInfo *newFileNode(int id, char description[50], char route[50], char type[10],fileInfo *f ){
    fileInfo* information;
	information = (fileInfo *) malloc(sizeof(fileInfo));

	information->treeInfo.id=id;
    strcpy(information->treeInfo.description,description);
    strcpy(information->treeInfo.route, route);
    strcpy(information->treeInfo.type,type);

    information->left=information->right=NULL;
	information->father=f;
    information->factorEQ=0;

    return information;
}


int itsNullTheTree(Tree*tree){
	if(tree->root==NULL){
		return 1;
	}else{
		return 0;
	}
}


int heightNode(fileInfo*node){
	if(node!=NULL){
		int hi=heightNode(node->left);
		int hd=heightNode(node->right);
		if(hi>hd){
			return hi+1;
		}else{
			return hd + 1;
		}	
	}else{
		return 0;
	}
}

int balanceFactor(fileInfo*node){
	return heightNode(node->right) - heightNode(node->left);
}

void leftRotation(Tree*a,fileInfo*node){
	fileInfo *aux,*p,*q;
	aux=node->right;
	q=aux->left;
	p=node->father;
	
	node->right=q;
	aux->left=node;
	
	if(q!=NULL){
		q->father=node;
	}
	node->father=aux;
	if(p==NULL){ //Tree rood
		a->root=aux;
	}else{
		aux->father=p;
		if(aux->treeInfo.id > p->treeInfo.id){
			p->right=aux;
		}else{
			p->left=aux;
		}
	}	
	aux->factorEQ=balanceFactor(aux);
	node->factorEQ=balanceFactor(node);
}

void rightRotation(Tree*a,fileInfo*node){
	fileInfo *aux,*p,*q;
	aux=node->left;
	q=aux->right;
	p=node->father;
	
	node->left=q;
	aux->right=node;
	
	if(q!=NULL){
		q->father=node;
	}
	node->father=aux;
	if(p==NULL){ // Tree rood
		a->root=aux;
	}else{
		aux->father=p;
		if(aux->treeInfo.id > p->treeInfo.id){
			p->right=aux;
		}else{
			p->left=aux;
		}
	}	
	aux->factorEQ=balanceFactor(aux);
	node->factorEQ=balanceFactor(node);
}

void doubleLeftRotation(Tree*a,fileInfo*node){	
	rightRotation(a,node->right);
	leftRotation(a,node);
}

void rotationDoubleRight(Tree*a,fileInfo*node){	
	leftRotation(a,node->left);
	rightRotation(a,node);
	
}

void swing(Tree*a,fileInfo*f){
	fileInfo *father;
	if(f!=NULL){
		father=f->father;
		f->factorEQ=balanceFactor(f);
		if(f->factorEQ>1){ //right imbalance
			if(balanceFactor(f->right)<0){
				doubleLeftRotation(a,f);
			}else{
				leftRotation(a,f);
			}			
		}else if(f->factorEQ<-1){ //left imbalance
			if(balanceFactor(f->left)>0){
				rotationDoubleRight(a,f);
			}else{
				rightRotation(a,f);
			}
		}
		swing(a,father);
	}
}



void addFile(Tree*tree, int id, char description[50], char route[50], char type[10]){
	fileInfo *aux,*prev;
	
	int counter;
	if(itsNullTheTree(tree)){
		prev=NULL;
		tree->root=newFileNode(id,description,route,type, prev);		
	}else{
		aux=tree->root;
		while(aux!=NULL){
			prev=aux;
			if(id > aux->treeInfo.id){
				aux=aux->right;
			}else{
				aux=aux->left;
			}
			counter++;
		}

		if(id > prev->treeInfo.id){
			prev->right=newFileNode(id,description,route,type, prev);			
		}else{
			prev->left=newFileNode(id,description,route,type, prev);			
		}
		swing(tree,prev);		
	}
}


void modifyFile(Tree*tree){
	
	int id;
	char description[50];
    char route[50];
    char type[10];

	strcpy(route, tree->root->treeInfo.route);
	id = tree->root->treeInfo.id;

	system("cls");
	
	printf("\n------------------------\n");
	printf ("\nWrite a new description for the file: ");
    gets(description);
	while(strlen(description) > 50){
		printf("\nThe description is invalid, please write a description with a maximum of 50 characteres: ");
		fgets(description,50,stdin);
	}
	
    printf ("\nWrite the type of the file: ");
	gets(type);
	while(strlen(type) > 50){
		printf("\nThe type is invalid, please write a description with a maximum of 50 characteres:");
		fgets(type,50,stdin);
	}

    addFile(tree,id,description,route,type);
}

// ROBUSTEZ POR ID
void fileInformation(Tree*tree){
	
	int id;
	char description[50];
    char route[50];
    char type[10];
	system("cls");
	printf("\n------------------------\n");

	printf ("\nWrite the file ID: ");
	scanf ("%d",&id);

	printf ("\nWrite a description for the file: ");
    gets(description);
	gets(description);
	while(strlen(description) > 50){
		printf("\nThe description is invalid, please write a description with a maximum of 50 characteres: ");
		fgets(description,50,stdin);
	}
	
    printf ("\nWrite the type of the file: ");
	gets(type);
	while(strlen(type) > 50){
		printf("\nThe type is invalid, please write a description with a maximum of 50 characteres:");
		fgets(type,50,stdin);
	}

    addFile(tree,id,description,route,type);
}


// ROBUSTEZ POR ID
void newFile(){
    char vertex[50];
	int id;
    Graph*aux = start;
    if(start != NULL){
        fflush(stdin);
        printf("Type the task name where you want to add a file: ");
        scanf("%s",&vertex);
        printf("\nType the ID of the task where you want to add a resource: ");
        scanf("%d",&id);
        while(aux!=NULL){
            if(strcmp(aux->taskName,vertex) == 0 && aux->task->taskInfo.id == id){
                Tree*tree;
                tree->root=aux->task->files.root;
                fileInformation(tree);
                printf("\n-- The file were add succesfully! --\n");
                break;
            }
            aux=aux->next;
        } 
        
        if(aux==NULL){
            printf("Error: Vertex not found\n");
        }
    }
}

void restart(){
	if(start!=NULL){
		Graph*aux=start;
		while(aux!=NULL){
			aux->visited=aux->finished=0;
		    aux=aux->next;
		}
	}
}

void insertStack(Graph* aux){
	Stack*newG = (Stack*)malloc(sizeof(Stack));
	newG->data = aux;
	newG->next=NULL;
	if(initial==NULL){
		initial=newG;
		end=newG;
	}else{
	   newG->next=initial;
	   initial=newG;    	
	}
}

Graph*dequeue(){
	Stack*aux;
	if(initial==NULL){
		return NULL;
	}else{
		aux=initial;
		initial=initial->next;
		aux->next=NULL;
		if(initial==NULL)
		end=NULL;
	}
	Graph*result=aux->data;
	free(aux);
	return result;
}

void dijkstra()
{
	Graph*aux = start;
	char source[50], destiny[50];
	fflush(stdin);
    printf("Type the name of the source task: ");
    scanf("%s",&source);
    printf("Type the name of the destiny task: ");
    scanf("%s",&destiny);

	while(aux!=NULL){
		if(strcmp(aux->taskName, source) == 0){
			aux->finished = 1;
			aux->amount = 0;
			break;
		}
		aux = aux->next;
	}
	if(aux==NULL){
		printf("Vertex not found\n");
		return;
	}
	while(aux!=NULL){
		edge*a = aux->adjacency;
	    while(a!=NULL){
		    if(a->task->amount==-1 || (aux->amount+a->effortRequired) < a->task->amount){
		    	a->task->amount = aux->amount+a->effortRequired;
		        strcpy(a->task->previousTask, aux->taskName);
			}
		    a = a->next;
	    }
	    aux = start;

	    Graph* min = start;
	    while(min->previousTask==0 || min->finished ==1)
	        min = min->next;
	    while(aux!=NULL){
	    	if(aux->amount < min->amount && aux->finished == 0 && aux->previousTask != 0)
            {
	    	    min = aux;
	    	    aux=aux->next;
            }
		}
		aux=min;
		aux->finished=1;
		if(aux->taskName==destiny){
		    break;            
        }
	}
	while(aux->previousTask != 0){
		insertStack(aux);
		char temp[50];
		strcpy(temp,aux->previousTask);
		aux = start;
		while(aux->taskName!=temp){
		   aux = aux->next;	
		}
	}
	insertStack(aux);
	while(initial!=NULL){
		printf("%s ",dequeue()->taskName);
	}
		printf("\n");
	restart();
}

void tasksMenu(){
    int answer;
	system("cls");
	printf ("\n ------------ Tasks Menu ------------");
	printf ("\n 1. Add new task"); // prints in terminal " 1. Add new task"
    printf ("\n 2. Add new edge");
	printf ("\n 3. View tasks");
	printf ("\n 4. Modify tasks\n");

	scanf("%d", &answer);
	switch(answer){
		case 1:
			newTask();
            break;
        case 2:
            newEdge();
            break;
		case 3:
			//viewTasks(); // call the function viewTasks()
			break;
		case 4:
			//modifyTask();// Se debe poder modificar todo menos el ID
			break;
	}
}

void documentsMenu(){ 
    int answer;
	system("cls");
	printf ("\n ------------ Files Menu ------------");
	printf ("\n 1. Add new file"); // prints in terminal " 1. Add new file"
	printf ("\n 2. View file route\n");
	printf ("\n 3. Modify file\n");
	printf ("\n 4. Delete file\n"); // prints in terminal " 4. Delete file"
	printf ("\n 5. Search file\n");

	scanf("%d", &answer);
	switch(answer){
		case 1:
			newFile();
			break;
		case 2:
			//viewFileRoute(); call the function viewFileRoute()
			//projectGraph->task5->file3; scanf("projectGraph->task%d->file%d", i, j); 
			break;
		case 3:
			//modifyFile();
			break;
		case 4:
			//deleteFile(); // call the function deleteFile() **VEREMOS
			break;
		case 5:
			//searchFile(); 
							/*
							recibe de parámetro el vértice del grafo (graphVertex*task), accesa al arbol de esa "Task" y 
							busca el documento por medio del ID (debe desplegar la ruta de acceso si se encontró, 
							sino "Not File with that ID was found")
							*/
			break;
	}
}



int main(){   
    int numberOfOption, i, taskNumber;
	char option[1];
	printf("Type the number of tasks you wanna add to the project: ");
    scanf("%s",&tasks);

	if(isNumber(tasks) == 1){
		taskNumber = atoi(tasks);
	}
	if(taskNumber <= 500){
		for(i = 0; i < taskNumber; i++){
			newTask();
		}
	}
	else{
		while(taskNumber >= 500){
			printf("ERROR! Number of tasks not supported \nPlease type a smaller number: ");
			scanf("%s",tasks);
			if(isNumber(tasks) == 1){
				taskNumber = atoi(tasks);
				break;
			}			
		}
	}

	system("cls");
    do{
		printf ("\n ------------ Project Management Menu - APTEC ------------");
        printf ("\n 1. Project visualization");
		printf ("\n 2. Establish project route");
		printf ("\n 3. Project route visualization");
		printf ("\n 4. Tasks menu");
		printf ("\n 5. Add a new resource");
		printf ("\n 6. Documents menu");
		printf ("\n 7. Project tasks realization recommendation");
		printf ("\n 8. Exit\n");
        printf("Escoge opcion: ");
        gets(option);
		while(strlen(option) > 1){
			printf("\nThe required effort is invalid, please write a required effort between 0 and 50 ");
			fgets(option,1,stdin);
		}
		if(isNumber(option) == 1){
			numberOfOption = atoi(option);
		}
        switch(numberOfOption){
			case 1:
				//visualizeGraphProject(); // Imprimir el grafo en forma de árbol de expansión mínima, por anchura
				break;
			case 2:
				//establishProjectRoute(); //RUBÉN. Nota: lanzar error si la tarea no tiene arista a la siguiente
													/* 
													3.2. Armar una ruta crítica: Aristas de grafo general 
													[cálculo de esfuerzos y comparación + impresión de ruta del grafo (tareas)]
													*/
				break;
			case 3:
				//visualizeProjectRoute(projectGraph);
				break;
			case 4:
				tasksMenu();
				break;
			case 5:
				newResource();
				break;
			case 6:
				documentsMenu();
				break;
            case 7: 
                dijkstra();
			    break;
			case 8:
				keepInfo();
                return 0;
            default: 
                printf("Not a valid option\n");
                break;
        }
        system("pause");
        system("cls");
    }while(numberOfOption!=6);
    return 1;
}
