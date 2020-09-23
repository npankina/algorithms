from node import Node


class LinkedList:
    
    def __init__(self):
        self.__head = None


    def is_empty(self):
        return self.__head is None

    def add(self, item):
        node = Node(item)
        node.next = self.__head
        self.__head = node
    
    def size(self):
        current = self.__head
        count = 0
        while not current is None:
            current = current.next
            count += 1
        return count

    def search(self, item):
        current = self.__head
        while not current is None:
            if current.data == item:
                return True
            current = current.next
        return False

    def remove(self, item):
        current = self.__head
        prev = None
        while True:
            if current.data == item:
                break
            prev = current
            current = current.next
        if prev is None:
            self.__head = current.next
        else:
            prev.next = current.next