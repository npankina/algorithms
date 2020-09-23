class Node:
    def __init__(self, data):
        self.__data = data
        self.__next = None

    def set_data(self, data):
        self.__data = data
    
    def get_data(self):
        return self.__data

    data = property(get_data, set_data)

    def set_next(self, node):
        self.__next = node

    def get_next(self):
        return self.__next
    
    next = property(get_next, set_next)