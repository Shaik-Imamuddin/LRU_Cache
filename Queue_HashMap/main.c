#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct Node{
    int data;
    struct Node* addr;
};

struct Node *front=NULL,*rear=NULL;

void enqueue(int val){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->addr = NULL;

    if(rear==NULL){
        front=rear=newNode;
        return;
    }

    rear->addr = newNode;
    rear = newNode;
}

int dequeue(){
    if(front==NULL)
        return -1;

    int val = front->data;
    struct Node* temp = front;
    front = front->addr;

    if(front==NULL)
        rear=NULL;

    free(temp);
    return val;
}

void removeNode(int val){
    if(front==NULL)
        return;

    if(front->data==val){
        dequeue();
        return;
    }

    struct Node* prev = front;
    struct Node* curr = front->addr;

    while(curr!=NULL && curr->data!=val){
        prev = curr;
        curr = curr->addr;
    }

    if(curr!=NULL){
        prev->addr = curr->addr;
        if(curr==rear)
            rear = prev;
        free(curr);
    }
}

// LRU
int capacity, size=0;
int map[MAX], present[MAX];

int get(int key){
    if(!present[key])
        return -1;

    removeNode(key);
    enqueue(key);

    return map[key];
}

void put(int key,int val){
    if(capacity==0)
        return;

    if(present[key]){
        map[key]=val;
        removeNode(key);
        enqueue(key);
    }
    else{
        if(size==capacity){
            int lru = dequeue();
            present[lru]=0;
            size--;
        }
        map[key]=val;
        present[key]=1;
        enqueue(key);
        size++;
    }
}

void display(){
    struct Node* temp = front;
    while(temp){
        printf("%d ",temp->data);
        temp=temp->addr;
    }
    printf("\n");
}

int main(){
    scanf("%d",&capacity);

    for(int i=0;i<MAX;i++)
        present[i]=0;

    int n;
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        char op[10];
        scanf("%s",op);

        if(op[0]=='p'){
            int k,v;
            scanf("%d %d",&k,&v);
            put(k,v);
        }
        else if(op[0]=='g'){
            int k;
            scanf("%d",&k);
            printf("%d\n",get(k));
        }
    }

    display();
}