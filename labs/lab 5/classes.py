class Node:
	#initialization function
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None
		self.parent = None

	def add_left(self, data):
		self.left = Node(data)

	def add_right(self, data):
		self.right = Node(data)

	def rm_node(self, node = "both"):
		if node == "both":
			delattr(self, "left")
			delattr(self, "right")
		else:
			delattr(self, node)

	#traverse the tree in inorder
	def inorder(self):
		if self.left != None:
			self.left.inorder()
		print(self.data)
		if self.right != None:
			self.right.inorder()

	#traverse the tree in preorder
	def preorder(self):
		print(self.data)
		if self.left != None:
			self.left.preorder()
		if self.right != None:
			self.right.preorder()

	#traverse the tree in postorder
	def postorder(self):
		if self.left != None:
			self.left.postorder()
		if self.right != None:
			self.right.postorder()
		print(self.data)