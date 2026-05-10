#include<iostream>
#include<unordered_map>
using namespace std;

class Node{
public:
    int data;
    Node *addr;

    Node(int val){
        data = val;
        addr = nullptr;
    }
};

class Stack{
public:
    Node *top;

    Stack(){
        top = nullptr;
    }

    void push(int val){
        Node *newNode = new Node(val);
        newNode->addr = top;
        top = newNode;
    }

    void remove(int val){
        if(top == nullptr)
            return;

        if(top->data == val){
            top = top->addr;
            return;
        }

        Node *prev = top;
        Node *curr = top->addr;

        while(curr!=nullptr && curr->data!=val){
            prev = curr;
            curr = curr->addr;
        }

        if(curr!=nullptr)
            prev->addr = curr->addr;
    }

    int removeBottom(){
        if(top == nullptr)
            return -1;

        if(top->addr==nullptr){
            int val = top->data;
            top = nullptr;
            return val;
        }

        Node *prev = nullptr;
        Node *curr = top;

        while(curr->addr!=nullptr){
            prev = curr;
            curr = curr->addr;
        }

        prev->addr = nullptr;
        return curr->data;
    }
};

class LRUCache{
public:
    int capacity;
    unordered_map<int,int> mp;
    Stack s;

    LRUCache(int cap){
        capacity = cap;
    }

    int get(int key){
        if(mp.find(key) == mp.end())
            return -1;

        s.remove(key);
        s.push(key);

        return mp[key];
    }

    void put(int key, int val){
        if(mp.find(key) != mp.end()){
            mp[key] = val;
            s.remove(key);
            s.push(key);
        }
        else{
            if(mp.size() == capacity){
                int lru = s.removeBottom();
                mp.erase(lru);
            }
            mp[key] = val;
            s.push(key);
        }
    }

    void display(){
        Node *temp = s.top;
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp->addr;
        }
        cout << endl;
    }
};

int main(){
    int capacity;
    cin >> capacity;

    LRUCache cache(capacity);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string op;
        cin >> op;

        if(op == "put"){
            int key, val;
            cin >> key >> val;
            cache.put(key, val);
        }
        else if(op == "get"){
            int key;
            cin >> key;
            cout << cache.get(key) << endl;
        }
    }

    cache.display();
    
    return 0;
}