class Node:
	#initialization function
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None
		self.parent = None

	#add a node to left branch
	def add(self, data, branch):
		setattr(self, branch, Node(data))
		getattr(self, branch).parent = self

	#remove branch, if none of the branch is specified,
	#remove both
	def rm_node(self, node = "both"):
		if node == "both":
			self.left = None
			self.right = None
		else:
			setattr(self, node, None)

	#traverse the tree in inorderNone
	def inorder(self, result = []):
		if self.left != None:
			self.left.inorder(result)
		result.append(self.data)
		if self.right != None:
			self.right.inorder(result)
		return result

	#traverse the tree in preorder
	def preorder(self, result = []):
		result.append(self.data)
		if self.left != None:
			self.left.preorder(result)
		if self.right != None:
			self.right.preorder(result)
		return result

	#traverse the tree in postorder
	def postorder(self, result = []):
		if self.left != None:
			self.left.postorder(result)
		if self.right != None:
			self.right.postorder(result)
		result.append(self.data)
		return result

	#this function checks whether a data element
	#is present in the binary tree
	def contains(self, data):
		return (data in self.preorder())

	#this function recursively searches for an element
	#and returns a the path, by creating the array of
	#its parents and inversing the array
	def path(self, data):
		if (data == self.data):
			return self
		if self.left != None:
			return self.left.path(data)
		if self.right != None:
			return self.right.path(data)

	def getNode():
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
			else:
				self.right.add(data)
		if data < self.data:
			if (self.left == None):
				self.left = Node_BST(data)
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