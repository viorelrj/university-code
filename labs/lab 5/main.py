from classes import Node

root = Node(1)

root.add_left(2)
root.add_right(3)
root.left.add_left(4)
root.left.add_right(5)
root.right.add_left(6)
root.right.add_right(7)
