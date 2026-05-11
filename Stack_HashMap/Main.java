import java.util.Scanner;
import java.util.HashMap;

class Node{
    int data;
    Node addr;

    Node(int val){
        data = val;
        addr= null;
    }
}

class Stack{
    Node top;

    Stack(){
        top = null;
    }

    void push(int val){
        Node newNode = new Node(val);
        newNode.addr = top;
        top = newNode;
    }

    void remove(int val){
        if(top==null)
            return;

        if(top.data==val){
            top=top.addr;
            return;
        }

        Node prev = top;
        Node curr = top.addr;

        while(curr!=null && curr.data!=val){
            prev = curr;
            curr = curr.addr;
        }

        if(curr!=null)
            prev.addr = curr.addr;
    }

    int removeBottom(){
        if(top==null)
            return -1;

        if(top.addr==null){
            int val = top.data;
            top=null;
            return val;
        }

        Node prev = null;
        Node curr = top;

        while(curr.addr!=null){
            prev = curr;
            curr = curr.addr;
        }

        prev.addr = null;
        return curr.data;
    }
}

class LRUCache{

    int capacity;
    HashMap<Integer,Integer> map;
    Stack s;

    LRUCache(int cap){
        capacity = cap;
        map = new HashMap<>();
        s = new Stack();
    }

    int get(int key){
        if(!map.containsKey(key))
            return -1;

        s.remove(key);
        s.push(key);

        return map.get(key);
    }

    void put(int key,int val){
        if(map.containsKey(key)){
            map.put(key,val);
            s.remove(key);
            s.push(key);
        }
        else{
            if(map.size()==capacity){
                int lru = s.removeBottom();
                map.remove(lru);
            }
            map.put(key,val);
            s.push(key);
        }
    }

    void display(){
        Node temp = s.top;
        while(temp!=null){
            System.out.print(temp.data+" ");
            temp = temp.addr;
        }
        System.out.println();
    }
}

public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int capacity = sc.nextInt();
        LRUCache cache = new LRUCache(capacity);

        int n = sc.nextInt();

        for(int i=0;i<n;i++){
            String op = sc.next();

            if(op.equals("put")){
                int key = sc.nextInt();
                int val = sc.nextInt();
                cache.put(key,val);
            }
            else if(op.equals("get")){
                int key = sc.nextInt();

                System.out.println(cache.get(key));
            }
        }
        cache.display();
    }
}