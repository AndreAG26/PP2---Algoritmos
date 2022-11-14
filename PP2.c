#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Classes establishment

typedef struct Tree Tree;
typedef struct treeNode fileInfo;
typedef struct treeInfo treeInfo;

struct treeInfo
{
    int id;
    char route [100]; // projectGraph->task5->file3; scanf("projectGraph->task%d->file%d", i, j); 
    char description [40];
    char type [10]; 
};


struct treeNode
{
    fileInfo *right;
    fileInfo *left;
	treeInfo treeInfo;
};


struct Tree
{
	fileInfo *root;
};


// Double list struct

typedef struct resources resources;
typedef struct resourcesNode resourcesNode;
typedef struct resourceInfo resourceInfo;


struct resourceInfo{
	int id;
	char resourceName[20];
	char resourceType[20];
	char name[50];
	char surname1[30];
	char surname2[30];
	int capacity;
	int quantity;
};

struct resourcesNode{
	resourceInfo resourceInfo;
	resourcesNode *previous;
	resourcesNode *next; 
};

struct resources{
	resourcesNode *first;
    resourcesNode *last;
};


// BTS structures

typedef struct taskInfo taskInfo;


struct taskInfo{
	int id;
	char description[100];
	char type[20];
	char name[50];
	char surname1[30];
	char surname2[30];
	int effort;
	int time;
};

// Graph structures

typedef struct task graphVertex;
typedef struct Graph Graph;
typedef struct edge edge;


struct task // graph vertex
{
    int destiny;
    graphVertex* next;
    taskInfo* taskInfo;
    Tree files;
    resources* resourcesList;
    
};

struct Graph
{
    graphVertex* head[20]; // An array of pointers to Node to represent an adjacency list
};


struct edge{
	int source;
	int destiny;
	int estimatedTime; // = source ?
	int effortRequired; // = destiny ?
};

// projectGraph->head[i]->files->root->treeInfo->id;

// Starting functions --------------------------------------------------------------------------------------


void keepTaskInfo(taskInfo taskInfo){
    FILE *file = fopen("ProjectInfo", "a+");
    fprintf(file, "%d,%s,%d, %s, %s, %s, %d, %s\n",taskInfo.id,taskInfo.description, taskInfo.effort, taskInfo.managerName.name, taskInfo.managerName.surname1, taskInfo.managerName.surname2, taskInfo.time, taskInfo.type);
    fclose(file);
}

void keepFilesInfo(fileInfo fileInfo){
    FILE *file= fopen("ProjectInfo", "a+");
    fprintf(file, "%d, %s, %s, %s, %s, %d, %s\n",fileInfo.treeInfo.id, fileInfo.treeInfo.rute, fileInfo.treeInfo.description, fileInfo.treeInfo.type);
    fclose(file);
}

void keepResourceInfo(resourceInfo resourceInfo){
    FILE *file= fopen("ProjectInfo", "a+");
    fprintf(file, "%d,%s, %s, %s, %s, %s, %d, %d\n",resourceInfo.id, resourceInfo.resourceName, resourceInfo.resourceType, resourceInfo.managerName.name, resourceInfo.managerName.surname1, resourceInfo.managerName.surname2, resourceInfo.capacity, resourceInfo.quantity);
    fclose(file);
}


Tree *newTree(void)
{
    Tree *newT;
    newT = (Tree *) malloc(sizeof(Tree));
    newT->root->right = NULL;
    newT->root->left = NULL;
    return newT;
}

fileInfo* newTreeNode(treeInfo data)
{
    fileInfo *newN;
    newN = (fileInfo *) malloc(sizeof(fileInfo));
    newN->right = NULL;
    newN->left = NULL;
    newN->treeInfo = data;
    return newN;
}

// Function to create an adjacency list from specified edges
Graph* createGraph(edge edges[])
{
	int i, destiny, source;
    // allocate storage for the graph data structure
    Graph* graph = (Graph*)malloc(sizeof(Graph));
 
    // initialize head pointer for all vertices
    for (i = 0; i < 20; i++) {
    	graphVertex* newNode = (graphVertex*)malloc(sizeof(graphVertex));
        graph->head[i] = newNode;
    }
 
    // add edges to the directed graph one by one
    for (i = 0; i < 20; i++)
    {
        // get the source and destination vertex
        source = edges[i].source;
        destiny = edges[i].destiny;
 
        // allocate a new node of adjacency list from source to dest
        graph->head[source-1]->destiny = destiny;
 
        // point new node next to the current head
        graph->head[source-1]->next = graph->head[destiny-1];

    }
 
    return graph;
}

int len(int numero){
	int cociente, divisor, contador;
	cociente = 0;
	divisor = 1;
	contador = 0;

	while (cociente !=1){
		contador++;
		divisor = divisor * 10;
		cociente = numero / divisor;

		if (cociente == 1){
			contador = contador + 1;
		}
		if (cociente < 1){
			cociente = 1;
		}
		if (numero < 10){
			contador = 1;
		}
	}
	return contador;
}

resourcesNode* newResourceNode(resourceInfo information)
{
    resourcesNode *newN;
    newN = (resourcesNode *) malloc(sizeof(resourcesNode));
    newN->next = NULL;
    newN->previous = NULL;
	strcpy(newN->resourceInfo.resourceName,information.resourceName);
	strcpy(newN->resourceInfo.resourceType,information.resourceType);
	strcpy(newN->resourceInfo.managerName.name,information.managerName.name);
	strcpy(newN->resourceInfo.managerName.surname1,information.managerName.surname1);
	strcpy(newN->resourceInfo.managerName.surname2,information.managerName.surname2);
	newN->resourceInfo.id=information.id;
	newN->resourceInfo.capacity=information.capacity;
	newN->resourceInfo.quantity=information.quantity;
}

resources* registerResource(resources *resourcesList, resourceInfo information){
	resourcesNode* newN = newResourceNode(information);
	resourcesNode* aux;
	if(resourcesList->first==NULL)
    {
        resourcesList->first=newN;
        resourcesList->first->next= NULL;
		resourcesList->last = resourcesList->first; // Dado que es el primer elemento ingresado, el primer elemento se convierte en el ultimo. Son lo mismo. (Listas Dobles)
        resourcesList->first->previous = NULL;  // Dado que es el primer elemento ingresado, no existe un elemento anterior. (Listas Dobles)
		return resourcesList;
    }
    resourcesNode *n = resourcesList->first;
    while(n!= NULL)
    {
        aux = n;
        n = n->next;
    }
		aux->next = newN;
   		aux->next->next = NULL;
   		resourcesList->last = aux->next; // El nuevo elemento se convierte en el ultimo. (Listas Dobles)
   		resourcesList->last->previous = aux; // El anterior del ultimo apunto al que antes era ultimo. (Listas Dobles)
		return resourcesList;
}

void addResource(graphVertex* task){
	resourceInfo information;

	printf ("\nWrite the resource ID: \n");
	scanf ("%d",&information.id);


	printf ("\nWrite the new resource name: ");
	scanf ("%s",&information.resourceName);
	while(strlen(information.resourceName) > 19){
		printf("\nResource name is too long, please write a type with a maximum of 49 characteres:");
		scanf ("%s",&information.resourceName);
	}

	printf ("\nWrite the new resource type: ");
	scanf ("%s",&information.resourceType);
	while(strlen(information.resourceType) > 20){
		printf("\nResource type is too long, please write a type with a maximum of 20 characteres: ");
		scanf ("%s",&information.resourceType);
	}

	printf ("\nWrite the new resource manager name: \n");
	scanf ("%s",&information.managerName.name);
	while(strlen(information.managerName.name) > 50){
		printf("\nResources manager name is too long, please write a name with a maximum of 50 characteres:");
		scanf ("%s",&information.managerName.name);
	}

	printf ("\nWrite the new resource manager first surname: \n");
	scanf ("%s",&information.managerName.surname1);
	while(strlen(information.managerName.surname1) > 30){
		printf("\nResources manager name is too long, please write a surname with a maximum of 30 characteres:");
		scanf ("%s",&information.managerName.surname1);
	}

    printf ("\nWrite the new resource manager second surname: \n");
	scanf ("%s",&information.managerName.surname2);
	while(strlen(information.managerName.surname2) > 30){
		printf("\nResources manager name is too long, please write a surname with a maximum of 30 characteres:");
		scanf ("%s",&information.managerName.surname2);
	}

	printf ("\nWrite the new resource capacity: \n");
	scanf ("%d",&information.capacity);
	while(information.capacity > 20){ // ?
		printf("\nCapacity exceeds the limit. Please write a number between 0 and 20");
		scanf ("%d",&information.capacity);
	}

	printf ("\nWrite the new resource capacity: \n");
	scanf ("%d",&information.quantity);
	while(information.quantity > 20){ // ?
		printf("\nCapacity exceeds the limit. Please write a number between 0 and 20");
		scanf ("%d",&information.quantity);
	}


	registerResource(task->resourcesList,information);
}

void addTask(Graph*projectGraph){
	
	taskInfo* information;
	information = (taskInfo *) malloc(sizeof(taskInfo));
	int taskType, taskIndex;
	char description[50];

	printf ("\nWrite the task index (between 1 and 20): \n");
	scanf ("%d",&taskIndex);
	while(taskIndex < 1 || taskIndex > 20){
		printf("\nThe number of the task is invalid, please write an number beetween 1 and 20:");
		scanf ("%s",&taskIndex);
	}

	printf ("\nWrite the task ID: \n");
	scanf ("%d",&information->id);

	printf ("\nWrite a description for the task: ");
	fgets(description,50,stdin);
	while(strlen(description) > 50){
		printf("\nThe description is invalid, please write a description with a maximum of 50 characteres:");
		fgets(description,50,stdin);
	}
	strcpy(information->description, description);

	printf ("\nTask types:\n 1. Operative Task\n 2. Approvation Task\n 3. Contract Signing\n 4. Management Task\n 5. Changes");
	printf ("\nWrite the new task type: ");
	scanf ("%d",&taskType);
	if (taskType == 1){
		strcpy(information->type,"OperativeTask");
	}
	else if(taskType == 2){
		strcpy(information->type,"ApprovationTask");
	}
	else if(taskType == 3){
		strcpy(information->type,"ContractSigning");
	}
	else if(taskType == 4){
		strcpy(information->type,"ManagementTask");
	}
	else if(taskType == 5){
		strcpy(information->type,"Changes");
	}
	else{
		printf("\nPlease type a valid number command");
		return;
	}

	printf ("\nWrite the new task effort: \n");
	scanf ("%d",&information->effort);
	while(information->effort > 20){ 
		printf("\nEffort exceeds the limit. Please write a number between 0 and 20: ");
		scanf ("%d",&information->effort);
	}

	printf ("\nWrite the new task time in hours: \n"); // Revisar si es un "float"
	scanf ("%d",&information->time);
	while(information->time > 24){ // ?
		printf("\nTime exceeds the limit. Please write a number between 0 and 24");
		scanf ("%d",&information->time);
	}

	projectGraph->head[taskIndex-1]->taskInfo = information;

}

/*
void addFile(graphVertex* task, int x) // binary tree (arbol) DANIEL
{
    nodo *newN;
    newN = malloc(sizeof(struct nodo));
    newN->info = x;
    newN->izq = NULL;
    newN->der = NULL;
    if (raiz == NULL)
        raiz = nuevo;
    else
    {
        nodo *anterior, *aux;
        anterior = NULL;
        aux = raiz;
        while (aux != NULL)
        {
            anterior = aux;
            if (x < aux->info)
                aux = aux->izq;
            else
                aux = aux->der;
        }
        if (x < anterior->info)
            anterior->izq = newN;
        else
            anterior->der = newN;
    }
}
*/



void tasksMenu(Graph* projectGraph){
    int answer;

	printf ("\n ------------ Tasks Menu ------------");
	printf ("\n 1. Add new task");
	printf ("\n 2. View taks");
	printf ("\n 3. Modify taks\n");

	scanf("%d", &answer);
	switch(answer){
		case 1:
			addTask(projectGraph);
		case 2:
			//viewTasks(); // árbol de expansión mínima [unicamente se imprimen las Task. Todo en forma de lista (Prim o Kruskal)]
			break;
		case 3:
			//modifyTask();// Se debe poder modificar todo menos el ID
			break;
	}
}

void documentsMenu(Graph* projectGraph){ // DANIEL
    int answer;
	printf ("\n ------------ Files Menu ------------");
	printf ("\n 1. Add new file");
	printf ("\n 2. View file route\n");
	printf ("\n 3. Modify file\n");
	printf ("\n 4. Delete file\n");
	printf ("\n 5. Search file\n");

	scanf("%d", &answer);
	switch(answer){
		case 1:
			//addFile(files);
			break;
		case 2:
			//viewFileRoute(); projectGraph->task5->file3; scanf("projectGraph->task%d->file%d", i, j); 
			break;
		case 3:
			//modifyFile();
			break;
		case 4:
			//deleteFile();
			break;
		case 4:
			//searchFile(); 
							/*
							recibe de parámetro el vértice del grafo (graphVertex*task), accesa al arbol de esa "Task" y 
							busca el documento por medio del ID (debe desplegar la ruta de acceso si se encontró, 
							sino "Not File with that ID was found")
							*/
			break;
	}
}


// MainMenu
int main(){

    int answer, validate = 1, answer2;

	Graph* projectGraph;
	edge edges[] =
	{
		{1, 2}, {2, 3}, {3, 4},{4, 5}, {5, 6}, {6, 7},
		{7, 8}, {8, 9},{9, 10}, {10, 11}, {11, 12},{12, 13},
		{13, 14}, {14, 15},{15, 16}, {16, 17}, {17, 18},{18,19},
		{19, 20},{20, 1}  // "edges" (new) struct of type Edge (Espanol: arista = edge)
	};

	projectGraph = createGraph(edges);

    while (validate == 1){
		printf ("\n ------------ Project Management Menu - APTEC ------------");
		printf ("\n 1. Project visualization");
		printf ("\n 2. Establish project route");
		printf ("\n 3. Project route visualization");
		printf ("\n 4. Tasks menu");
		printf ("\n 5. Add a new resource");
		printf ("\n 6. Documents menu");
		printf ("\n 7. Documents menu");
		printf ("\n 8. Exit\n");
		scanf("%d", &answer);

		switch(answer){

			case 1:
				//visualizeGraphProject(projectGraph); // Imprimir el grafo en forma de árbol de expansión mínima, por anchura
				break;
			case 2:
				//establishProjectRoute(projectGraph); RUBÉN
													/* 
													3.2. Armar una ruta crítica: Aristas de grafo general 
													[cálculo de esfuerzos y comparación + impresión de ruta del grafo (tareas)]
													*/
				break;
			case 3:
				//visualizeProjectRoute(projectGraph);
				break;
			case 4:
				tasksMenu(projectGraph);
				break;
			case 5:
				printf ("\n Write the number of the task you wanna add: \n");
				scanf("%d", &taskNumber);
				graphVertex* taskUnit = projectGraph->head[taskNumber];
				addResource(taskUnit);
				break;
			case 6:
				//documentsMenu(projectGraph);
				break;
			case 7:
				//fasterRoute() // Dijkstra
			case 8:
				system("end");
			printf ("\nDo you want to do another option?");
			printf ("\n1. Yes \n0. No\n");
			scanf ("%i",&answer2);
			while(answer2 > 1){
				printf ("\nNot a valid option, write 0 or 1");
				printf ("\nDo you want to do another action ?");
				printf ("\n1. Yes \n0. No\n");
				scanf ("%i",&validate);  
			}
		}
	}

	system ("pause");

	return 0;

}

