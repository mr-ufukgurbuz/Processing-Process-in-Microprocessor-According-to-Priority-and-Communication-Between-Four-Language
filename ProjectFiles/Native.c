/*	UFUK GÜRBÜZ - 150113058 */

#include "Native.h"

#include "binomial.h"
#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define true 1
#define false 0

//***********************************************************************************
/* structure for a node */
struct node
{
	char name[15];
	int tExe;
    int tArr;
    struct node *next;
};
 
/* Function to insert a node at the begining of a linked lsit */
void insertAtTheBegin(struct node **start_ref, char *name, int tExe, int tArr);
 
/* Function to bubble sort the given linked lsit */
void bubbleSort(struct node *start);
 
/* Function to swap tArr of two nodes a and b*/
void swap(struct node *a, struct node *b);
 
/* Function to print nodes in a given linked list */
void ontoPrintList(struct node *start);
//************************************************************************************


char inputFileName[40];

JNIEXPORT void JNICALL Java_Native_sum(JNIEnv *env, jobject obj, jstring FileName) {
	const char *inputDosyaName = (*env)->GetStringUTFChars(env, FileName, NULL);
	if (NULL == inputDosyaName)
		printf("Q dosyasi yok!\n");
	strcpy( inputFileName, inputDosyaName );
	main1();
}



typedef struct BinNode *Position;

struct BinNode
{
	char name[10];
	ElementType exTime,arTime,priority;				// Node Olusturma
	Position    LeftChild;
	Position    NextSibling;
};

struct Collection
{
	int CurrentSize;									// Node dizisi tanimlama
	BinTree TheTrees[ MaxTrees ];
};

BinQueue Initialize( void )
{
	BinQueue H;
	int i;
	H = malloc( sizeof( struct Collection ) );

	if( H == NULL )
		FatalError( "Out of space!!!" );					// Heap Olusturma

	H->CurrentSize = 0;

	for( i = 0; i < MaxTrees; i++ )
		H->TheTrees[ i ] = NULL;

	return H;
}

static void DestroyTree( BinTree T )
{
	if( T != NULL )
	{
		DestroyTree( T->LeftChild );					// Destroy(Yikmak) Tree yi
		DestroyTree( T->NextSibling );
		free( T );
	}
}

void Destroy( BinQueue H )
{
	int i;
	for( i = 0; i < MaxTrees; i++ )					// Destroy(Yikmak) Heap i
		DestroyTree( H->TheTrees[ i ] );
}

BinQueue MakeEmpty( BinQueue H )
{
	int i;
	Destroy( H );

	for( i = 0; i < MaxTrees; i++ )					// Heap i Bos Yapma
		H->TheTrees[ i ] = NULL;

	H->CurrentSize = 0;

	return H;
}

BinQueue Insert( char name[], ElementType executionTime,ElementType arrivalTime,ElementType priority, BinQueue H )
{
	BinTree NewNode;
	BinQueue OneItem;
	int i;
	NewNode = malloc( sizeof( struct BinNode ) );

	if( NewNode == NULL )
		FatalError( "Out of space!!!" );

	NewNode->LeftChild = NewNode->NextSibling = NULL;
	NewNode->exTime=executionTime;
	NewNode->arTime=arrivalTime;
	NewNode->priority=priority;
	strcpy(NewNode->name,name);										// Heap e eleman ekleme

	OneItem = Initialize( );
	OneItem->CurrentSize = 1;
	OneItem->TheTrees[ 0 ] = NewNode;

	return Merge( H, OneItem );
}

ElementType DeleteMin( BinQueue H )
{
	int i, j;
	int MinTree;   /* The tree with the minimum item */

	BinQueue DeletedQueue;
	Position DeletedTree, OldRoot;
	ElementType MinItem;

	if( IsEmpty( H ) )
	{
		Error( "Empty binomial queue" );
		MinItem=-Infinity;
		return MinItem;
	}
	MinItem = Infinity;
	for( i = 0; i < MaxTrees; i++ ){
		if( H->TheTrees[ i ] && H->TheTrees[ i ]->priority < MinItem )
		{
			/* Update minimum */
			 MinItem = H->TheTrees[ i ]->priority;
			 MinTree = i;																// Heapteki minimum elemani silme
		}
	}

	DeletedTree = H->TheTrees[ MinTree ];
	OldRoot = DeletedTree;
	DeletedTree = DeletedTree->LeftChild;

	free( OldRoot );

	DeletedQueue = Initialize( );
	DeletedQueue->CurrentSize = ( 1 << MinTree ) - 1;

	for( j = MinTree - 1; j >= 0; j-- )
	{
	    DeletedQueue->TheTrees[ j ] = DeletedTree;
	    DeletedTree = DeletedTree->NextSibling;
	    DeletedQueue->TheTrees[ j ]->NextSibling = NULL;
	}

	H->TheTrees[ MinTree ] = NULL;
	H->CurrentSize -= DeletedQueue->CurrentSize + 1;

	Merge( H, DeletedQueue );

	return MinItem;
}

ElementType FindMin( BinQueue H )
{
 	int i;
 	ElementType MinItem;

	 if( IsEmpty( H ) )
 	{
    	Error( "Empty binomial queue" );
		MinItem=0;
    	return MinItem;
  	}

    MinItem = Infinity;											// Heap teki minimum elemani bulma

    for( i = 0; i < MaxTrees; i++ )
    {
        if( H->TheTrees[ i ] &&
        	H->TheTrees[ i ]->priority < MinItem ) {
            MinItem = H->TheTrees[ i ]->priority;
		}
    }

    return MinItem;
}

BinTree FindMinNode( BinQueue H )
{
	int i;
	ElementType MinItem;
	BinTree node;

	if( IsEmpty( H ) )
    {
        puts( "Empty binomial queue" );
		MinItem=0;
    }

    MinItem = Infinity;

    for( i = 0; i < MaxTrees; i++ )								// Tree deki minimum node u bulma
    {
        if( H->TheTrees[ i ] &&
            H->TheTrees[ i ]->priority < MinItem ) {
            MinItem = H->TheTrees[ i ]->priority;
			node =  H->TheTrees[ i ] ;
		}
    }

	return node;
}

int IsEmpty( BinQueue H )
{
            return H->CurrentSize == 0;				// Heap Bos mu
}

int IsFull( BinQueue H )
{
            return H->CurrentSize == Capacity;		// Heap Dolu mu
}

BinTree CombineTrees( BinTree T1, BinTree T2 )
{
    if( T1->priority > T2->priority )
    	return CombineTrees( T2, T1 );

	T2->NextSibling = T1->LeftChild;
    T1->LeftChild = T2;

	return T1;
}

BinQueue Merge( BinQueue H1, BinQueue H2 )
{
    BinTree T1, T2, Carry = NULL;
    int i, j;

    if( H1->CurrentSize + H2->CurrentSize > Capacity )
        Error( "Merge would exceed capacity" );

    H1->CurrentSize += H2->CurrentSize;
    for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 )
    {
        T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

        switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
        {
            case 0: /* No trees */
            case 1: /* Only H1 */
                break;
            case 2: /* Only H2 */
                H1->TheTrees[ i ] = T2;
                H2->TheTrees[ i ] = NULL;
                break;
            case 4: /* Only Carry */
                H1->TheTrees[ i ] = Carry;
                Carry = NULL;
                break;
            case 3: /* H1 and H2 */
                Carry = CombineTrees( T1, T2 );
                H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
                break;
            case 5: /* H1 and Carry */
                Carry = CombineTrees( T1, Carry );
                H1->TheTrees[ i ] = NULL;
                break;
            case 6: /* H2 and Carry */
                Carry = CombineTrees( T2, Carry );
                H2->TheTrees[ i ] = NULL;
                break;
            case 7: /* All three */
                H1->TheTrees[ i ] = Carry;
                Carry = CombineTrees( T1, T2 );
                H2->TheTrees[ i ] = NULL;
                break;
        }
    }
    return H1;
}

BinTree printTree(BinTree p, BinTree *r, int i, FILE *write)
{
	BinTree t[20]={NULL}, q; int j;

	for ( j=0; j<i; j++ ) t[j]= r[j];

	i=0;

	if (p!=NULL) {

		//printf("%s %4lf %4lf %4lf \n",p->name,p->exTime,p->arTime,p->priority);
		fprintf( write, "%s %4lf %4lf %4lf \n",p->name,p->exTime,p->arTime,p->priority);
		q=p->NextSibling;
		j=0;

		do {
		  while (q!=NULL) {
		    //printf("%s %4lf %4lf %4lf\n",q->name,q->exTime,q->arTime,q->priority);
		    fprintf( write, "%s %4lf %4lf %4lf\n",q->name,q->exTime,q->arTime,q->priority);

			if (q->LeftChild != NULL) { r[i]=q->LeftChild; i++; }
		    	q=q->NextSibling;
		  }

		  q=t[j++];
		} while (q!=NULL);

	}

	else return NULL;

	//printf("\n\n");
	fprintf( write, "\n\n");
	printTree(p->LeftChild, r, i, write);
}


float emax;//for use finding new priority queue

int get_q_value(){
	int q;
	printf("Please enter q value for priority: ");				// Kullanicidan q degeri alma
	scanf("%d", &q);

	return q;
}

FILE * openingFile( char * filename, char *mod ){

	FILE *file = fopen( filename, mod );

	if(file == 0){
		puts("File does not exist!");
		exit(0);
	}

    return file;
}

int checkExt( BinTree p, BinTree r[20], float exT){
    /*If p tree null return 0*/
	if(p==NULL)
		return 0;
	if(p->exTime==exT)		// Checking p tree execution time equal to execution time of process
		return 1;

    return 0;
}


int function(int q, FILE *dosya, FILE *pythonFile){
	
	//int q = get_q_value();

	char name[10];//process name;
	float exeT=0, arrT=0;
	float priority=0;//															//--For icinde tanimla
    
	int j=0;		//array elemani															//--Gerek kalmadi.Sadece altta
   
    int process=0;			//Total islem
	
	float realtime = 0;		//gercek zaman
	float waitingT=0;		//waiting time
    float averagewaitingT=0;	//average waiting time
    
	float arrayArr[100];	//Ýslemlerin gelis zamanlarini arraye kaydetme
    
	BinQueue H1;		//collection of binomial tree
    BinTree p, r[20]={NULL};		//p include element of BinTree;


    FILE *data = openingFile( inputFileName, "r" );
    

	while(!feof(data)) {
		
     	if(EOF != fscanf(data, "%s%f%f",name, &exeT, &arrT)) {
	     	arrayArr[j++]=arrT;
	     	if(exeT > emax)
	     	{
	     		emax = exeT;
	     	}
	     	process=process+1;
	     }
	     else break;
	     
    }
    
    j=0;//j equal to 0;

	fseek( data, 0, SEEK_SET );			// Dosyayi bastan okuma

//*************************************************************************
	H1 = Initialize( );		/*Initialize Heap Yaratma*/
	FILE *write = dosya;

	while (true){
		
		int a;
		//printf("\n\t\t<<< REAL TIME >>>\n");
		//printf("\nReal time is %4f\n " ,realtime);

		fprintf( write, "\n\t\t<<< REAL TIME >>>\n");
		fprintf( write, "\nReal time is %4f\n " ,realtime);
		
		while(realtime>=arrayArr[j]&&!feof(data)){
			
			fscanf(data,"%s%f%f",name, &exeT, &arrT);

			
			int i;
			for(i=0; i<MaxTrees; i++) {		/*Check execution time in binomial heap*/
				p=H1->TheTrees[i];
				a = checkExt(p, r, exeT);
		   }
		   
			if(a==1){
				priority=exeT+arrT/100;	/*If execution time is equal,determine priority queue*/
			}
			
			else{
				priority=exeT;	/*Else priority queue egual to executýon týme*/
			}
			
			//printf("\n\n\t\t<<< ADDING PROCESS >>>\n\n");
			//printf("ID %s Execution time %4f ArivalTime %4f Priority %4f\n\n",name, exT, arT,priority);

			fprintf( write, "\n\n\t\t<<< ADDING PROCESS >>>\n\n");
			fprintf( write, "ID %s Execution time %4f ArivalTime %4f Priority %4f\n\n",name, exeT, arrT,priority);
			
			Insert(name,exeT,arrT,priority,H1);		/*Coming time process insert*/
			
			j++;	/*Next arrival time*/
		}

		//printf("\n\n\t\t<<< THE BINOMIAL HEAP ELEMENTS >>> \n\n");
		fprintf( write, "\n\n\t\t<<< THE BINOMIAL HEAP ELEMENTS >>> \n\n");
		
		int i;
		for(i=0; i<MaxTrees; i++) {
			p=H1->TheTrees[i];					/*Print process in the binomial heap*/
			printTree(p, r, 0, write);
		}

		BinTree min = FindMinNode(H1);			/*Find node highest priority queue in the binomial heaps*/

		/*Calculate the process waitingT time*/
		waitingT=waitingT+realtime-min->arTime;

		//printf("\n\t\t<<< WAITING TIME >>>\n");
		//printf("\nWaiting time is %4f\n",waitingT);

		fprintf( write, "\n\t\t<<< WAITING TIME >>>\n");
		fprintf( write, "\nWaiting time is %4f\n",waitingT);

		//printf("--------------------------------------------------------------------------------\n");

		fprintf( write, "--------------------------------------------------------------------------------\n");

		
		DeleteMin(H1);	/*Delete highest the priority queue*/

		/*If minnode execution time greather than quantum size*/
		if(min->exTime>q){
			
			realtime=realtime+q;	/*Increasing real time*/
			
			float eNew=min->exTime-q;	/*Calculating new execution time*/
			
			float c = 1.0/exp(-pow(2.0*eNew/3.0/emax,3));
			
			priority=eNew*c;	/*Calculating new priority queueu*/
			
			Insert(name,eNew,realtime,priority,H1);	/*Reýnsert updating information the process*/
			
		}
		/*Else*/
		else{
			
			if(min->exTime==q){		/*If minnode execution time equal to quantum size*/
				realtime=realtime+q;	/*Gercek zamani arttirma*/
			}
			/*Else*/
			else{
				realtime=realtime+min->exTime;	/*Gercek zamani arttirma*/
			}
		}
		
		if(IsEmpty(H1)){	/*If binomial heap empty,check feof file*/
			
			if(feof(data)){		/*If file is feof,program is finished*/
            	//printf("\n\t\t<<< REAL TIME >>>\n");
				//printf("\nReal time is %4f\n",realtime);
				//printf("\n\n\t\t<<< THE BINOMIAL HEAP ELEMENTS >>> \n");
				//printf("\nEMPTY\n\n");

                fprintf( write, "\n\t\t<<< REAL TIME >>>\n");
				fprintf( write, "\nReal time is %4f\n",realtime);
				fprintf( write, "\n\n\t\t<<< THE BINOMIAL HEAP ELEMENTS >>> \n");
				fprintf( write, "\nEMPTY\n\n");
				break;
				
			}
		}
	}
	
	//printf("--------------------------------------------------------------------------------\n");
	//printf("////////////////////////////////////////////////////////////////////////////////\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\t\t\t\t<<< Q=%d >>>\n\n", q);
	
	printf("\n\t\t<<< AVERAGE WAITING TIME >>>\n");
	printf("\nThe number of total processes is %d\n",process);
	
	
	fprintf( pythonFile, "--------------------------------------------------------------------------------\n");
	fprintf( pythonFile, "\t\t\t\t<<< Q=%d >>>\n\n", q);
	
	fprintf( pythonFile, "\n\t\t<<< AVERAGE WAITING TIME >>>\n");
	fprintf( pythonFile, "\nThe number of total processes is %d\n",process);


	fprintf( write, "--------------------------------------------------------------------------------\n");
	fprintf( write, "oooooooooooooooooooooooooooooooooooooooooooooooooooooo\n");
	fprintf( write, "--------------------------------------------------------------------------------\n");
	fprintf( write, "\n\t\t<<< AVERAGE WAITING TIME >>>\n");
	fprintf( write, "\nThe number of total processes is %d\n",process);

	/*Calculating averagewaitingT time*/
	averagewaitingT=waitingT/process;

	printf("Average waiting time is %4f\n",averagewaitingT);
	fprintf( pythonFile, "q= %d Avarage Waiting Time = %4f\n",q,averagewaitingT);
	fprintf( write,"q= %d Avarage Waiting Time = %4f\n",q,averagewaitingT);

	fclose(data);
	fclose(write);
	fclose(pythonFile);
	
}

char output[20][25] ={"dosya//q1.txt","dosya//q2.txt","dosya//q3.txt","dosya//q4.txt","dosya//q5.txt","dosya//q6.txt","dosya//q7.txt","dosya//q8.txt","dosya//q9.txt","dosya//q10.txt","dosya//q11.txt","dosya//q12.txt","dosya//q13.txt",
"dosya//q14.txt","dosya//q15.txt","dosya//q16.txt","dosya//q17.txt","dosya//q18.txt","dosya//q19.txt","dosya//q20.txt"};

int main1(){
	
	//system("color 17");
			//*******************************************************************
		/* start with empty linked list */
	struct node *start = NULL;
	
	char pName[15];
	int tExe;
    int tArr;
	
	FILE *fPtr = fopen(inputFileName, "r");

	while(!feof(fPtr)) {
     	if(EOF != fscanf(fPtr, "%s%d%d", pName, &tExe, &tArr)) {
	     	insertAtTheBegin(&start, pName, tExe, tArr);
	    }
	    else break;
    }
	
	bubbleSort(start);
	
	ontoPrintList(start);
	//*******************************************************************

	

	int q;
	for(q=1;q<=20;q++){
		
		FILE *pythonFile = openingFile("dosya//pythonFile.txt","a");
		FILE *dosya = openingFile( output[q-1], "a");
		
		
		fprintf( dosya, "\t\t\t\t\t\t\t\t\t\t\t-------------------\n");
		fprintf( dosya, "\t\t\t\t\t\t\t\t\t\t\t <<< Q=%d >>>\n", q);
		fprintf( dosya, "\t\t\t\t\t\t\t\t\t\t\t-------------------\n\n");
	
		function( q, dosya, pythonFile );
		fclose(dosya);	
	}
	//	fclose(pythonFile);
	
}


/* Function to insert a node at the begining of a linked lsit */
void insertAtTheBegin(struct node **start_ref, char *name, int tExe, int tArr)
{
    struct node *ptr1 = (struct node*)malloc(sizeof(struct node));
    strcpy(ptr1->name,name);
	ptr1->tExe = tExe;
	ptr1->tArr = tArr; 
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}
 
/* Function to print nodes in a given linked list */
void ontoPrintList(struct node *start)
{
	FILE *fPtr = fopen(inputFileName, "w");
	
    struct node *temp = start;
    printf("\n");

    while (temp!=NULL)
    {	
        fprintf(fPtr, "\n%s\t%d\t%d", temp->name, temp->tExe, temp->tArr);
        temp = temp->next;
    }

   fclose(fPtr);
   
}
 
/* Bubble sort the given linked lsit */
void bubbleSort(struct node *start)
{
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;
 
    /* Checking for empty list */
    if (ptr1 == NULL)
        return;
 	
    do
    {
        swapped = 0;
        ptr1 = start;
        
        while (ptr1->next != lptr)
        {
            if (ptr1->tArr > ptr1->next->tArr)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
    
}
 
/* function to swap tArr of two nodes a and b*/
void swap(struct node *a, struct node *b)
{	
	char tempName[15];
	strcpy(tempName, a->name);
    int tempExe = a->tExe;
	int tempArr = a->tArr;
    
    strcpy(a->name,b->name);
	a->tExe = b->tExe;
	a->tArr = b->tArr;
    
    strcpy(b->name,tempName);
    b->tExe = tempExe;
	b->tArr = tempArr; 
}


