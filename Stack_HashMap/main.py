class Node:
    def __init__(self, val):
        self.data = val
        self.addr = None


class Stack:
    def __init__(self):
        self.top = None

    def push(self, val):
        newNode = Node(val)
        newNode.addr = self.top
        self.top = newNode

    def remove(self, val):
        if not self.top:
            return

        if self.top.data == val:
            self.top = self.top.addr
            return

        prev = self.top
        curr = self.top.addr

        while curr and curr.data != val:
            prev = curr
            curr = curr.addr

        if curr:
            prev.addr = curr.addr

    def removeBottom(self):
        if not self.top:
            return -1

        if not self.top.addr:
            val = self.top.data
            self.top = None
            return val

        prev = None
        curr = self.top

        while curr.addr:
            prev = curr
            curr = curr.addr

        prev.addr = None
        return curr.data


class LRUCache:
    def __init__(self, cap):
        self.capacity = cap
        self.map = {}
        self.s = Stack()

    def get(self, key):
        if key not in self.map:
            return -1

        self.s.remove(key)
        self.s.push(key)

        return self.map[key]

    def put(self, key, val):
        if key in self.map:
            self.map[key] = val
            self.s.remove(key)
            self.s.push(key)
        else:
            if len(self.map) == self.capacity:
                lru = self.s.removeBottom()
                del self.map[lru]

            self.map[key] = val
            self.s.push(key)

    def display(self):
        temp = self.s.top
        while temp:
            print(temp.data, end=" ")
            temp = temp.addr
        print()


capacity = int(input())
cache = LRUCache(capacity)

n = int(input())

for i in range(n):
    op = input().split()

    if op[0] == "put":
        cache.put(int(op[1]), int(op[2]))
    else:
        print(cache.get(int(op[1])))

cache.display()