#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct Node{
    int data;
    struct Node *addr;
};


struct Node *top = NULL;

void push(int val){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    
    newNode->addr = top;
    top = newNode;
}

void removeNode(int val){
    if(top==NULL)
        return;
    
    if(top->data == val){
        struct Node *temp = top;
        
        top = top->addr;
        free(temp);
        return;
    }

    struct Node *prev = top;
    struct Node *curr = top->addr;

    while(curr!=NULL && curr->data!=val){
        prev = curr;
        curr = curr->addr;
    }

    if(curr!=NULL){
        prev->addr = curr->addr;
        free(curr);
    }
}

int removeBottom(){
    if(top==NULL)
        return -1;
    
    if(top->addr == NULL){
        int val = top->data;
        free(top);
        top=NULL;
        return val;
    }

    struct Node *prev = NULL;
    struct Node *curr = top;

    while(curr->addr != NULL){
        prev=curr;
        curr=curr->addr;
    }

    prev->addr = NULL;
    int val = curr->data;
    free(curr);
    return val;
}


int capacity,size=0;
int map[MAX],present[MAX];

int get(int key){
    if(!present[key])
        return -1;
    
    removeNode(key);
    push(key);

    return map[key];
}

void put(int key,int val){
    if(present[key]){
        map[key]=val;
        removeNode(key);
        push(key);
    }
    else{
        if(size==capacity){
            int lru = removeBottom();
            if(lru != -1){
                present[lru]=0;
                size--;
            }
        }
        map[key]=val;
        present[key]=1;
        push(key);
        size++;
    }
}

void display(){
    struct Node *temp = top;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->addr;
    }
    printf("\n");
}

int main(){
    
    scanf("%d",&capacity);

    for(int i=0;i<MAX;i++){
        present[i]=0;
    }

    int n;
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        char op[10];
        scanf("%s",op);

        if(op[0]=='p'){
            int key,val;
            scanf("%d %d",&key,&val);
            put(key,val);
        }
        else if(op[0]=='g'){
            int key;
            scanf("%d",&key);
            printf("%d\n",get(key));
        }
    }
    display();
    return 0;
}