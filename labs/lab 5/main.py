from classes import Node, Node_BST

root = Node(1)
root.add(2, "left")
root.add(3, "right")
root.left.add(4, "left")
root.left.add(5, "right")
root.right.add(6, "left")
root.right.add(7, "right")

print(root.get_level(2))