class Node :
    def __init__(self,value):
        self.next = None
        self.value = value

class Stack :
    def __init__(self):
        self.head = None
        self.size = 0

    def push(self,value):
        new_node = Node(value)
        if self.head :
            new_node.next = self.head
        self.head = new_node
        self.size += 1

    def pop(self):
        if self.isEmpty():
            return "Stack is empty."
        popped_node = self.head
        self.head = self.head.next
        self.size -= 1
        return popped_node.value
    
    def peek(self):
        if not self.isEmpty(): 
            return self.head.value
        
    def isEmpty(self):
        return self.size == 0
    
    def stackSize(self):
        return self.size 
    
    