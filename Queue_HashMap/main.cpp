#include <iostream>
#include <unordered_map>
using namespace std;

class Node{
public:
    int data;
    Node* addr;

    Node(int val){
        data = val;
        addr = NULL;
    }
};

class Queue{
public:
    Node *front, *rear;

    Queue(){
        front = rear = NULL;
    }

    void enqueue(int val){
        Node* newNode = new Node(val);

        if(rear == NULL){
            front = rear = newNode;
            return;
        }

        rear->addr = newNode;
        rear = newNode;
    }

    int dequeue(){
        if(front == NULL)
            return -1;

        int val = front->data;
        Node* temp = front;
        front = front->addr;

        if(front == NULL)
            rear = NULL;

        delete temp;
        return val;
    }

    void removeNode(int val){
        if(front == NULL)
            return;

        if(front->data == val){
            dequeue();
            return;
        }

        Node* prev = front;
        Node* curr = front->addr;

        while(curr != NULL && curr->data != val){
            prev = curr;
            curr = curr->addr;
        }

        if(curr != NULL){
            prev->addr = curr->addr;
            if(curr == rear)
                rear = prev;
            delete curr;
        }
    }
};

class LRUCache{
    int capacity;
    unordered_map<int, int> map;
    Queue Q;

public:
    LRUCache(int cap){
        capacity = cap;
    }

    int get(int key){
        if (map.find(key) == map.end())
            return -1;

        Q.removeNode(key);
        Q.enqueue(key);

        return map[key];
    }

    void put(int key, int value){
        if (capacity == 0)
            return;

        if (map.find(key) != map.end()){
            map[key] = value;
            Q.removeNode(key);
            Q.enqueue(key);
        } 
        else{
            if(map.size() == capacity){
                int lru = Q.dequeue();
                map.erase(lru);
            }
            map[key] = value;
            Q.enqueue(key);
        }
    }

    void display(){
        Node* temp = Q.front;
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->addr;
        }
        cout<<endl;
    }
};

int main(){
    int capacity,n;
    cin>>capacity;

    LRUCache cache(capacity);

    cin>>n;

    for(int i = 0; i < n; i++){
        string op;
        cin>>op;

        if(op == "put"){
            int key,val;
            cin>>key>>val;
            cache.put(key, val);
        } 
        else if(op == "get"){
            int key;
            cin>>key;
            cout<<cache.get(key)<<endl;
        }
    }
    cache.display();
}