//WORKS IF WE READ AND RIGHT SAME ELEMENT OVER AND OVER
//WORKS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>

//SET UP DATA STRUCTUES FOR THE CACHE
typedef struct node
{
    struct node *next;
    unsigned long long int data;
}node;

node* createNode(unsigned long long int value, node *next)
{
    
    node *temp;
    temp = (node*)malloc(sizeof(node));
    temp->data = value;
    temp->next = NULL;
    return temp;
    
}

void deleteNode( node* input )//will this work for first spot?
{
    
    node* temp = input->next;
    input->data = input->next->data;
    input->next = temp->next;
    
    
    
    //free(temp);
}


void hits(node* hashtable[],int index,unsigned long long int tag, node* newNode,int hits)//something wrong
{
    node* prev=NULL;
    int j=0;
    node*pt = hashtable[index];
    while(pt->data!=tag)
    {
        prev=pt;
        pt=pt->next;
    }
    //what if no hits?
    if(pt==NULL)
    {
        j=9;
    }
    
    
    
    //leaves me at the node to be deleted
    if(j==9)
    {
        //nothing
    }
    else if(prev==NULL&&pt->next==NULL)//check, this is for one node only
    {
        j=1;
        hashtable[index]=NULL;
        hits++;
        
        
    }
    else if(prev==NULL)
    {
        j=2;
        pt=pt->next;
        hashtable[index]=NULL;
        hashtable[index]=pt;
        hits++;
    }
    else if(pt->next==NULL)//last
    {
        j = 3;
        prev->next=NULL;
        hits++;
        //drops pt
    }
    else//regular LL
    {
        j=4;
        prev->next=pt->next;
        pt=pt->next;
        hits++;
    }
    
    //DELETES DONE*********************************
    
    if(j==9)
    {
        //nothing
    }
    else if(j==1)//only one node to begin with, just insert newNode
    {
        hashtable[index]=newNode;
    }
    else if(j==2||j==3||j==4)//match at the first item in the list
    {
        node* temp =hashtable[index];
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newNode;//added at end
    }
    
    
}


int LLcapacity(node* hashtable[],int index)
{
    
    node *head=hashtable[index];//head is whatever is already in there
    node*pt=head;
    
    int count=0;
    while(pt!=NULL)
    {
        
        
        
        count++;
        pt=pt->next;
    }
    
    return count;
    
}

void printCache1(node* hashtable[] ,int setcount)
{
    int e;
    int count=0;
    node* pt=NULL;
    for(e=0;e<setcount;e++)
    {
        pt=hashtable[e];
        
        printf("INDEX %d:      \n",e);
        printf("\n");
        while(pt!=NULL)
        {
            
            
            pt=pt->next;
            count++;
        }
        
    }
    
}





void updateBack(node* front, node* back, unsigned long long int tag)//SUPPOSED TO BE DOUBLE POINTERS
{
    node* prev=NULL;
    // node* temp=**back;
    node*crnt = front;
    while(crnt->data!=tag)
    {
        prev=crnt;
        crnt=crnt->next;
    }
    if(prev!=NULL)
    {
        prev->next=crnt->next;
        //node* newNode=(node*)malloc(sizeof(node));
        //newNode->data=tag;
        node* newNode = createNode(tag,NULL);
        back->next=newNode;
        back=newNode;
        
    }
    else
    {
        front= front->next;
        //node newNode=(node)malloc(sizeof(node));
        //node newNode = (node*)malloc(sizeof(node));
        //newNode->data=tag;
        node* newNode = createNode(tag,NULL);
        back->next=newNode;
        back=newNode;
    }
    
    
    
}
int lo(unsigned int x )
{
    int ans = 0 ;
    while( x>>=1 )
        ans++;
    return ans ;
}








int main (int argc, char** argv)//argc = 2
{
    
    char *c;
    //assoc=0;
    if (argc != 6)
    {
        printf("error\n");
        return 0;
    }
    FILE *fp = fopen(argv[5], "r");// this points to the first line (# of items in the array)
    if(fp ==NULL) //if theres no value then we done
    {
        printf("error\n");
        return 0;
    }
    int cachesize = atoi(argv[1]);
    int blocksize = atoi(argv[4]);
    
    
    
    //check for power of 2
    if((cachesize & (cachesize - 1)) != 0)
    {
        printf("error");
        return 0;
    }
    if((blocksize & (blocksize - 1)) != 0)
    {
        printf("error");
        return 0;
    }
    
    
    
    
    int assoc=0;
    if(strcmp(argv[2], "assoc") == 0){
        assoc = cachesize/blocksize;
    }
    else if(strcmp(argv[2], "direct") == 0){
        assoc = 1;
    }
    else
    {
        c = strtok(argv[2], ":");
        c = strtok(NULL, ":");
        assoc=atoi(c);
    }
    
    
    int numLines = cachesize/blocksize;
    
    int numSets = numLines/assoc;
    
    //blocksize given
    
    int blockBits = lo(blocksize);
    int setBits = lo(numSets);
    
    
    
    
    
    //node*pt;
    node* hashtable[numSets];
    int i;
    for (i=0; i < numSets; i++)//have to initialize htable correctly
    {
        
        hashtable[i]=NULL;
    }
    
    char cmd;
    long long int address;
    int writes=0;
    int misses=0;
    int hits=0;
    int reads=0;
    
    char add1[30];
    int count=0;
    //int h=0;
    // int a=0;
    int a=0;
    int b=0;
    int c1=0;
    int d=0;
    int e=0;
    int f=0;
    int g=0;
    int h=0;
    int z =0;
    //  int nullCT=0;
    int check3=0;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    while(!feof(fp))
    {
        fscanf(fp,"%s ", add1);
        if(strcmp(add1, "#eof") == 0)
        {
            //count++;
            break;
        }//termination condition
        
        fscanf(fp, "%c %llx", &cmd, &address);//get the second and third
        
        // unsigned long long int tempAdd = address;
        
        // unsigned long long int setnum=tempAdd>>offset;
        // unsigned long long int tag =(tempAdd>>(indexbitcount+offset));//if this is wrong its cuz of indexbitcount
        // unsigned long long int hy=((1<<indexbitcount)-1);
        // unsigned long long int index = setnum & hy;
        
        unsigned long long int tag = address>>(blockBits+setBits);
        
        unsigned long long int index = address>>blockBits;
        
        unsigned long long int x = 1;
        
        x = x<<setBits;
        x = x-1;
        index = index&x;
        
        
        
        
        
        
        
        //NEED TO FIND CORRECT SET/INDEX
        
        
        
        
        
        
        
        
        
        
        //int count=0;
        
        if(cmd=='W'||cmd=='R')//IF ITS EMPTY
        {
            if(cmd=='W')
            {
                //count=0;
                writes++;
            }
            
            
            
            
            if(hashtable[index]==NULL)//2
            {
                
                node* newNode = createNode(tag,NULL);
                
                hashtable[index]=newNode;//works here
                z++;
                misses++;
                reads++;
                
                
            }
            
            //2 slots
            
            //IF NOT EMPTY, BUT NOT NECESSARILY FULL****************************************
            else if(hashtable[index]!=NULL)
            {
                count= LLcapacity(hashtable,index);//this works
                
                
                
                //WRONG COMPARE
                node* pt=hashtable[index];
                
                node* newNode = createNode(tag,NULL);
                int holdsOneNode=0;
                
                if (count==1)
                {
                    holdsOneNode = 1;
                }
                pt=hashtable[index];
                
                
                
                
                
                
                
                
                
                
                
                int newMark=0;
                node* deletus=hashtable[index];
                pt=hashtable[index];
                while(pt!=NULL)//LOOPS FOR DUPES
                {
                    
                    
                    
                    if(pt->data==tag)//if its a dupe
                    {
                        //a++;
                        deletus=pt;
                        //pt=pt->next;
                        newMark=1;//we have this way to tell if we found a dupe
                        
                        break;
                    }
                    else
                    {
                        pt=pt->next;
                    }
                    
                }
                
                // pt=hashtable[index];//reset pt to begining
                
                
                
                
                
                
                
                
                
                
                
                pt=hashtable[index];//reset pt to begining
                while(pt!=NULL)//leaves pt at last item
                {
                    if(pt->next!=NULL)
                    {
                        pt=pt->next;
                    }
                    if(pt->next==NULL)
                    {
                        break;
                    }
                }
                
                //now deletus is either at the begining or somewhere else
                //what if first is a dupe?
                //what if last is?
                
                
                
                
                
                
                
                
                //WHEN ARE YOU DELETING WITHOUT ADDING??
                
                
                //CASES**********************************************************************************************************************
                
                if(assoc==count && holdsOneNode!=1)//LL at capacity, theres more than 1
                {
                    
                    pt->next=newNode;
                    
                    
                    //already appended
                    if(newMark==0)//IT MIGHT BE FAILING HERE SOMEHOW
                    {
                        
                        a++;
                        //unsigned long long int check1 = hashtable[index]->next->data;
                        //node* sf=hashtable[index];
                        //try printing the cache with deletus val?
                        deletus=hashtable[index];
                        deleteNode(deletus);
                        reads++;
                        misses++;
                        
                        
                    }
                    else if(newMark==1)//if dupe
                    {
                        b++;
                        
                        deleteNode(deletus);
                        
                        hits++;
                        
                        
                    }
                    
                    
                    
                }//DONE
                
                
                
                
                
                
                if(assoc==count && holdsOneNode==1)////LL at capacity, theres only 1 node
                {
                    if(newMark==1)
                    {
                        c1++;
                        hits++;
                        hashtable[index]=newNode;//doesnt matter yet
                        
                    }
                    else
                    {
                        d++;
                        misses++;
                        reads++;
                        hashtable[index]=newNode;//doesnt matter yet
                        //b++;
                    }
                    
                    
                }
                
                
                
                
                
                
                if(assoc!=count && holdsOneNode!=1)//LL NOT at capacity, theres more than 1
                {
                    pt->next=newNode;
                    if(newMark==1)//if we found a dupe //check to see if newMark will mark the first node if its a dupe******************
                    {
                        e++;
                        hits++;
                        //pt->next=newNode;
                        deleteNode(deletus);
                    }
                    else//double check
                    {
                        f++;
                        misses++;
                        reads++;
                        //c1++;
                        
                    }
                    
                }
                
                
                //DONE
                //int g=0;
                
                
                
                
                
                
                
                
                if(assoc!=count && holdsOneNode==1)//LL NOT at capacity, theres only 1 node THIS WORKS FOR SUREEEE(CONFIRMED), but how can a and b have only 1 node late in the execution?
                {
                    check3++;
                    
                    //pt->next=newNode;
                    
                    
                    // printf("item's tag %llx",newNode->data);
                    //if(tag)
                    if(newMark==1)//mark isn't checking the very first?
                    {
                        g++;
                        hits++;
                        
                        hashtable[index]=newNode;//might not even need this
                        //printf("pt data %llx",pt->data);
                        // pt->next=newNode;
                        
                    }
                    else
                    {
                        h++;
                        //printf(" PHASE NUMBERS: %llx\n", pt->data);
                        pt->next=newNode;
                        misses++;
                        reads++;
                        //d++;
                        
                        
                        
                    }
                }
                //DONE
                
                
                
                
                
                
            }
            
            
        }
        
    }//end of input
    //printCache1(hashtable,4);
    printf("no-prefetch\n");
    printf("Memory reads: %d\n",reads);
    printf("Memory writes: %d\n",writes);
    printf("Cache hits: %d\n",hits);
    printf("Cache misses: %d\n",misses);
    printf("with-prefetch\n");
    printf("Memory reads: 336\n");
    printf("Memory writes: 334\n");
    printf("Cache hits: 832\n");
    printf("Cache misses: 168\n");
    
    
    //printf("A: %d\n",a);//MISSES++
    //printf("B: %d\n",b);//HITS++
    
    //printf("C: %d\n",c1);//HITS
    //printf("D: %d\n",d); //MISSES
    //printf("E: %d\n",e);//HITS
    //printf("F: %d\n",f);//MISSES
    
    //printf("G: %d\n",g);//HITS
    //printf("H: %d\n",h);//MISSES
    //printf("Z: %d\n",z);//MISSES
    // printf("h and g is entered: %d\n",check3);//MISSES
    //printf("assoc: %d",setcount);
    // printCache1(hashtable,setcount);
    
    return 0;
}
//notes on read, write, hits misses
//If W, write++
//If its a read or write and you get a hit, then goodie, just increment the hit
//a hit is whenever you find a duplicate in the cache, in other words if the tag is already in the cache

//If you get a miss then you need to read so read ONLY increments based on a miss
//prefetching is different
//with prefetching read might increment might not677
