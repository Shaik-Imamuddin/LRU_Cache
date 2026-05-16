import java.util.HashMap;
import java.util.Scanner;

class Node{
    int data;
    Node addr;

    Node(int val){
        data=val;
        addr=null;
    }
}

class Queue{
    Node front,rear;

    Queue(){
        front=rear=null;
    }

    void enqueue(int val){
        Node newNode = new Node(val);

        if(rear==null){
            front=rear=newNode;
            return;
        }

        rear.addr = newNode;
        rear=newNode;
    }

    int dequeue(){
        if(front==null)
            return -1;

        int val=front.data;
        front=front.addr;

        if(front==null)
            rear = null;

        return val;
    }

    void remove(int val){
        if(front == null)
            return;

        if(front.data == val){
            dequeue();
            return;
        }

        Node prev = front;
        Node curr = front.addr;

        while(curr!=null && curr.data!=val){
            prev = curr;
            curr=curr.addr;
        }

        if(curr!=null){
            prev.addr = curr.addr;
            
            if(curr==rear)
                rear = prev;
        }
    }
}

class LRUCache{

    private int capacity;
    private HashMap<Integer,Integer> map;
    private Queue Q;

    LRUCache(int cap){
        capacity = cap;
        map = new HashMap<>();
        Q = new Queue();
    }

    public int get(int key){
        if(!map.containsKey(key))
            return -1;

        Q.remove(key);
        Q.enqueue(key);

        return map.get(key);
    }

    public void put(int key,int value){

        if(capacity==0)
            return;

        if(map.containsKey(key)){
            map.put(key,value);
            Q.remove(key);
            Q.enqueue(key);
        }
        else{
            if(map.size()==capacity){
                int lru = Q.dequeue();
                map.remove(lru);
            }
            map.put(key,value);
            Q.enqueue(key);
        }
    }

    public void display(){
        Node temp = Q.front;
        while(temp != null){
            System.out.print(temp.data + " ");
            temp = temp.addr;
        }
        System.out.println();
    }
}


public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int capacity = sc.nextInt();
        LRUCache cache = new LRUCache(capacity);
        
        int n = sc.nextInt();

        for(int i=0;i<n;i++){
            String op = sc.next();

            if(op.equals("put")){
                int key = sc.nextInt();
                int value = sc.nextInt();
                cache.put(key, value);
            }

            else if(op.equals("get")){
                int key = sc.nextInt();
                System.out.println(cache.get(key));
            }
        }
        cache.display();
    }
}