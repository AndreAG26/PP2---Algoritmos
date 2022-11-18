/*
        NECESITA QUE EN EL CÓDIGO DE CREAR TAREA ESTA INICIE ROOD EN NULL 

        newTask(): newVertex->files.root=NULL;
*/


//NUEVA ESTRUCTURAAAAAA!!!!!!!!!
struct treeNode // (fileInfo) Binary tree node struct
{
    fileInfo *right;
    fileInfo *left;
    fileInfo *father;
	treeInfo treeInfo;

    int factorEQ;
};

//CODIGOOOOOOO

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
	
	int contador;
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
			contador++;
		}

		if(id > prev->treeInfo.id){
			prev->right=newFileNode(id,description,route,type, prev);			
		}else{
			prev->left=newFileNode(id,description,route,type, prev);			
		}
		swing(tree,prev);		
	}
}

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

void newFile(){
    char vertex[50];
    graphVertex*aux = start;
    if(start != NULL){
        fflush(stdin);
        printf("Type the task name where you want to add a file:");
        scanf("%s",&vertex);
        while(aux!=NULL){
            if(strcmp(aux->taskName,vertex) == 0){
                Tree*tree;
                tree->root=aux->files.root;
                fileInformation(tree);
                printf("\n-- The file were add succesfuly! --\n");
                break;
            }
            aux=aux->next;
        } 
        
        if(aux==NULL){
            printf("\n%s\n",aux->taskName);
            printf("Error: Vertex not found\n");
        }
    }
}
