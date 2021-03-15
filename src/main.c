//includes necessary libraries to the program
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include <dirent.h>

//struct implementation for BH
struct node {
    int key, degree;
    char file_path [50], file_name[50];
    struct node *first, *parent, *child, *sibling, *next;
};

//functions to be used
struct node* BH_CREATE();
struct node* BH_INSERT(struct node*, struct node*);
struct node* BH_MERGE(struct node*, struct node*);
struct node* Merge_Root_Lists(struct node*, struct node*);
struct node* insertToQueue(struct node*);
void BH_DELETE_MAX(struct node*);
void GET_a_BT_k(struct node*, struct node*);
void display(struct node*);
void readDirectory(char *, char *);
void read_and_operate(struct node *, char *, char *);
void wordBufferUpdater(char* );
void wordBufferCleaner(char *);
void wordBufferDeleteSpaces(char * );
void fillTheQueue(struct node *);
void printHeap(struct node* );
void printFile(char *);
void swap(struct node *, struct node*);
void heapSort(struct node*);

//define HEAP and priorityQueue is null
struct node * HEAP = NULL;
struct node * priorityQueue = NULL;

//creates a binomial heap
struct node * BH_CREATE(){
        struct node * header = (struct node *)malloc(sizeof(struct node));
        header = NULL;
        return header;
}
//obtains a BT from two nodes
void GET_a_BT_k(struct node* y, struct node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree ++;
}

//merges two binomial heap header1 and header2
struct node* BH_MERGE(struct node* header1, struct node* header2) {
    struct node* previousNode = NULL, * nextNode, *x;
    //Merge root lists of two heap into one by descanding order
    struct node* header = BH_CREATE();
    header = Merge_Root_Lists(header1, header2);
    if (header == NULL)
        return header;
    x = header;
    //link the nexNode to x's sibling
    nextNode = x->sibling;
    //iterate through x's siblings
    while (nextNode != NULL) {
        if ((x->degree != nextNode->degree) || ((nextNode->sibling != NULL) && (nextNode->sibling)->degree == x->degree)){
            //redetermine x according to degree of nextNode and its sibling
            previousNode = x;
            x = nextNode;
        }
        else {
            //otherwise get a binomial tree with those two acc to keys
            if (x->key > nextNode->key) {
                x->sibling = nextNode->sibling;
                GET_a_BT_k(nextNode, x);
            }
            else {
                if (previousNode == NULL)
                    header = nextNode; //change the header as next
                else
                    previousNode->sibling = nextNode; // link the pre and next
                GET_a_BT_k(x, nextNode);
                x = nextNode;
            }
        }
        nextNode = x->sibling;
    }
    return header;
}
//inserts a node to binomial heap
struct node* BH_INSERT(struct node* header, struct node* x) {
    //create a header
    struct node* header1 = BH_CREATE();
    //assign null for node that will be added to the heap
    x->parent = NULL; x->child = NULL; x->sibling = NULL; x->degree = 0;
    header1 = x;
    //merge the heap with given node
    header = BH_MERGE(header, header1);
    return header;
}

//Merges two header into one in descending order
struct node* Merge_Root_Lists(struct node* header1, struct node* header2) {
    struct node* header = NULL;
    struct node *y = header1 , *z = header2 , *a, *b;
    if (y != NULL) {
        //determine the header node according to the degree
        if (z != NULL && y->degree > z->degree)
            header = z;
        else
            header = y;
    } else
        header = z;
    while (y != NULL && z != NULL) {
        //check the degress of two and link two nodes properly
        if (y->degree < z->degree) {
            y = y->sibling;
        } else if (y->degree == z->degree) {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } else {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return header;
}
//reverse the linked list of the max's child
void reverse(struct node * header){
    struct node* prev = NULL;
    struct node* current = header;
    struct node* next = NULL;
    while (current != NULL) {
        // Store next
        next = current->sibling;

        // Reverse current node's pointer
        current->sibling = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    header = prev;
}

//deletes the max key in the priority queue
void BH_DELETE_MAX(struct node *header){
	struct node * nodeWithMaxKey = NULL, * x = header, *prev; int max = 0;
        //determine the node with max key
	while(x != NULL){
		if(x -> key > max){ max = x -> key; nodeWithMaxKey = x; }
                prev = x; // H
                x = x -> sibling;
	}
        //hold the child of the max node
        struct node * childOfMax = nodeWithMaxKey -> child;

        prev -> sibling = childOfMax; // unlink the max from the heap
        free(nodeWithMaxKey); // free max

        reverse(childOfMax); // H' reverse the children list
        struct node * header1 = BH_CREATE();
        //merge header wih new heap
        header = BH_MERGE(header1, header);
}



//sorts the priority queue in descending order
void heapSort(struct node * head){
        //invoke fill the list method to fill priority
         fillTheQueue(HEAP);
         //creates two iterator to compare
         struct node * current = head, *index = NULL;
         if(head == NULL) return;
         else {
                 while(current != NULL){
                         index = current -> next;
                         while(index != NULL){
                                 //if current smaller then the next key, swap nodes
                                 if(current -> key < index -> key){
                                         swap(current, index);
                                 }
                                 index = index -> next;
                         }
                         current = current -> next;
                 }
         }
}
//displays the root nodes and displays as priority queueu
void display(struct node* header) {
    struct node* p,*temp = NULL, *iter = NULL;
    if (header == NULL) {
        printf("\n Heap is empty");
        return;
    }
    printf("\nRoot nodes are : ");
    p = header;
    while(p != NULL) {
        //print the key of the root of BH
        printf("%d", p->key);
            if(p -> sibling != NULL)
            printf("--> ");
        //go to the next sibling
        p = p->sibling;
    }
    printf("\nHeap -> ");
    //invoke the recursive printHeap function to print all the nodes in the heap
    printHeap(HEAP);
    printf("\n");
}

//prints all the nodes in the heap recursively
void printHeap(struct node * node){
	if(node != NULL){
		printf("%d ", node -> key);
                printHeap(node -> child);
                printHeap(node -> sibling);
	}
}
//reads whole files in directory, this will be used later, need some corrections
void readDirectory(char * directory, char * keyword){
    DIR *folder;
    struct dirent *entry;
    int numOfDocs = 0, numOfRelevantDocs = 0;
    char file_path [50];

    //opens the folder to read all the files
    folder = opendir(directory);

    if(folder == NULL){
        perror("Unable to read directory");
        return;
    }

    while( (entry=readdir(folder)) ){
        //exclude the current and parent firectory entry names -> . and ..
        bool isValidFile = (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0);

        if (isValidFile) {
            strcpy(file_path, directory); // file_path is now -> "../files/"
            //concat the path and file name to read the file
            strcat(file_path, entry->d_name); // ../files/file_name

            //create a node for every file
            struct node * root = (struct node * )malloc(sizeof(struct node));
            //read the file and put the key value of the file to its node
            read_and_operate(root, file_path, keyword); // root -> key is ready
            strcpy(root->file_name, entry->d_name);
            printf("%s has %d %s \n", root->file_name, root -> key, keyword);

            //if the key is found in the doc at least one time, insert the root to the heap
            if(root -> key > 0) {
                    numOfRelevantDocs ++;
                    HEAP = BH_INSERT(HEAP, root);
            }
            // clean the file_path to read over properly
            wordBufferCleaner(file_path); wordBufferUpdater(file_path);
            numOfDocs++;
        }
    }
    printf("\nrelevant documents -> %d found\n", numOfRelevantDocs);
    closedir(folder);
}

//reads the file and sets # of existance of the word in file to the root as key value
void read_and_operate(struct node * node, char * file_path, char * keyword){

    char word [100] = {'\0'}; node -> key = 0;
    //give the path of the file to the pointer to access from the BH later
    strcpy(node -> file_path, file_path);

        //file pointer to to read the file
	FILE * fp = fopen(file_path, "r");
	if (fp == NULL) return;

	char ch = fgetc(fp); int wordBufferCounter = 0;
        //till end of the file
        while(!feof(fp)){
        //character control while reading the file and seperate the words
        if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <='Z'))){
            //delete the spaces around the word to compare correcty
            wordBufferDeleteSpaces(word);
            //if the word is exactyle the same with the keyword to be searced, then increase the node's existance key
            if(strcmp(word, keyword) == 0) node -> key ++;
            //clean the word from the old word and update it as empty word
            wordBufferCleaner(word);
            wordBufferUpdater(word);

            wordBufferCounter = 0;
        }
        //fill the word with the proper chars
        else word[wordBufferCounter++] = ch;
        //jumps to the next character
        ch = fgetc(fp);
    }
        //close the file lastly
	fclose(fp);
}
//prints the doc in the given file_path
void printFile(char * file_path){
	FILE * fp = fopen(file_path,"r");
	char ch = fgetc(fp);
	while(!feof(fp)){
		printf("%c", ch);
		ch = fgetc(fp);
	}
}

/* maybe need to update these three*/
void wordBufferCleaner(char *word){
	for(int i = 0;i< strlen(word);i++){
		if(word[i] != ' '){
		//all characters of word is ' '
		word[i] = ' ';
		}
	}
}
//deleting the empty spaces in string(not the ones between words)
void wordBufferUpdater(char *word){
    int i = 0,j;
	//to control one character and the next character
    for(j = i+1; j < strlen(word); i++,j++){
			//if both are emtpy space, delete them
			if(word[i] == ' ' && word[j] == ' '){
				word[i] = '\0';word[j] = '\0';
			}
			//"string " situation, cont"rol last space and delete it
			if(j == strlen(word)-1 && word[j] == ' '){
				word[j] = '\0';
			}
		}
}
//deletes the spaces in the given word
void wordBufferDeleteSpaces(char * word){
        for(int i = 0; i < strlen(word); i++){
                if(word[i] == ' ') word[i] = '\0';
        }
}

//fills the queue with heap nodes recursively
void fillTheQueue(struct node * node){
	if(node != NULL){
		insertToQueue(node);
		fillTheQueue(node -> child);
		fillTheQueue(node -> sibling);
	}
}
//inserts the nodes to priority queue
struct node * insertToQueue(struct node * node){
	if(priorityQueue == NULL){
                //if queue is empty create one with the node
		priorityQueue = node;
		priorityQueue -> next = NULL;
		return priorityQueue;
	}
        //create an iterater and iterate through the queue
	struct node* iter = priorityQueue;
	while(iter -> next != NULL){
		iter = iter -> next;
	}
        //put the node to the next node assign NULL to the its next
	iter -> next = node;
	iter -> next -> next = NULL;
	return priorityQueue;
}

//swaps values of the nodes and file paths
void swap(struct node * a, struct node * b){
        struct node * temp = (struct node *)malloc(sizeof(struct node));
        temp-> key = a -> key;
        strcpy(temp -> file_path, a->file_path);
        strcpy(temp -> file_name, a->file_name);

        a -> key = b -> key;
        strcpy(a -> file_path, b -> file_path);
        strcpy(a -> file_name, b -> file_name);

        b -> key = temp -> key;
        strcpy(b -> file_path,temp -> file_path);
        strcpy(b -> file_name,temp -> file_name);
}
//prints the results to the screen
void printResults(struct node * priorityQueue, int numOfRelDocs){
        if(priorityQueue == NULL) return;
        struct node * iter = priorityQueue;
        printf("\nThe relevance order: ");
        for(int i = 0; i < numOfRelDocs; i++){
                if(i != numOfRelDocs - 1) printf("%s (%d), ", iter->file_name, iter ->key);
                else printf("%s(%d).\n", iter->file_name, iter -> key);
                if(iter-> next != NULL)
                        iter = iter -> next;
                else break;
        }
        printf("\n\n");
        iter = priorityQueue;
        for(int i = 0; i < numOfRelDocs; i++){
                printf("%s(%d):", iter -> file_name, iter -> key); printFile(iter -> file_path);
                printf("\n\n\n");
                if(iter -> next != NULL)
                        iter = iter -> next;
                else break;
        }
}

/* main  */
int main() {
        char keyword [50]; int numOfRelDocs;
        //take to the keyword and num of relevant docs from the user
        printf("Enter a keyword to search in documents: ");
        scanf("%s", keyword);
        // printf("Enter the number of relevant docs that you want to :");
        // scanf("%d", &numOfRelDocs);

        //read files and create heap
        readDirectory("../files/",keyword);
        display(HEAP);
        heapSort(HEAP);
        printf("\n\nAfter heap sort :");
        display(HEAP);
        printResults(priorityQueue,5); // print the 5 docs

}
