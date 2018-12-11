class Node:
	#initialization function
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None
		self.parent = None
		self.branch = None
		self.depth = 0

	def __has_left(self):
		return self.left != None

	def __has_right(self):
		return self.right != None

	def __has_both(self):
		return self.__has_left() and self.__has_right()

	def __has_no_children(self):
		return (not self.__has_left()) and (not self.__has_right())

	def __is_left_child(self):
		if self.depth > 0 and self.parent.left != None:
			return self.parent.left.data == self.data
		else:
			return None

	def __is_right_child(self):
		if self.depth > 0 and self.parent.right != None:
			return self.parent.right.data == self.data
		else: 
			return None

	#add a node to left branch
	def add(self, data, branch):
		setattr(self, branch, Node(data))
		getattr(self, branch).parent = self
		getattr(self, branch).depth = self.depth + 1
		getattr(self, branch).branch = branch

	#remove branch, if none of the branch is specified,
	#remove both
	def rm_node(self, node = "both"):
		if node == "both":
			self.left = None
			self.right = None
		else:
			setattr(self, node, None)

	#traverse the tree in inorderNone
	def inorder(self, result = [], reset = True):
		if reset:
			del result[:]
		if self.left != None:
			self.left.inorder(result, False)
		result.append(self.data)
		if self.right != None:
			self.right.inorder(result, False)
		return result

	#traverse the tree in preorder
	def preorder(self, result = [], reset = True):
		if reset:
			del result[:]
		result.append(self.data)
		if self.left != None:
			self.left.preorder(result, False)
		if self.right != None:
			self.right.preorder(result, False)
		return result

	#traverse the tree in postorder
	def postorder(self, result = [], reset = True):
		if reset:
			del result[:]
		if self.left != None:
			self.left.postorder(result, False)
		if self.right != None:
			self.right.postorder(result, False)
		result.append(self.data)
		return result

	def get_level(self, level, result = [], reset = True):
		if reset:
			del result[:]

		if self.depth < level:
			if self.__has_left():
				self.left.get_level(level, result, False)
			if self.__has_right():
				self.right.get_level(level, result, False)
		else:
			result.append(self.data)
		return result

	#this function checks whether a data element
	#is present in the binary tree
	def contains(self, data):
		return (data in self.preorder())

	#this function recursively searches for an element
	#and returns sthe path, by creating the array of
	#its parents and inversing the array
	def path(self, data):
		if (data == self.data):
			result = []
			while (self != None):
				result.append(self.data)
				self = self.parent
			result.reverse()
			return result
		else:
			if self.left != None:
				return self.left.path(data)
			if self.right != None:
				return self.right.path(data) 

	def get_node():
		if (data == self.data):
			result = []
			while (self != None):
				result.append(self.data)
				self = self.parent
			result.reverse()
			return result
		if self.left != None:
			return self.left.path(data)
		if self.right != None:
			return self.right.path(data)

#Binary Search Tree class
class Node_BST(Node):

	#The function to add binary search tree node, according to the rules
	def add(self, data):
		if data > self.data:
			if (self.right == None):
				self.right = Node_BST(data)
				self.right.depth = self.depth + 1
				self.right.parent = self
				self.right.branch = "right"
			else:
				self.right.add(data)
		if data < self.data:
			if (self.left == None):
				self.left = Node_BST(data)
				self.left.depth = self.depth + 1
				self.left.parent = self
				self.left.branch = "left"
			else:
				self.left.add(data)

	#This function returns the node with given value
	def search(self, data):
		if data < self.data:
			if self.left != None:
				return self.left.search(data)
			else:
				return None
		elif data > self.data:
			if self.right != None:
				return self.right.search(data)
			else:
				return None
		else:
			return self

	def find_min(self):
		while self.left != None:
			self = self.left
		return self


	def find_max(self):
		while self.right != None:
			self = self.right
		return self

	def rm_node(self, data):
		node = self.search(data)

		if node == None:
			return None

		if node.__has_no_children():
			setattr(node.parent, node.branch, None)
		elif node.__has_both():
			temp = node.right.find_min()
			node.data = temp.data
			node.right.rm_node(temp.data)
		else:
			child = node.left if node.__has_left() else node.right
			setattr(node.parent, node.branch, child)
