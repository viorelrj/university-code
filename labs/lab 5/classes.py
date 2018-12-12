from copy import deepcopy as deepcopy

class Node:
	#initialization function
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None
		self.parent = None
		self.branch = None
		self.depth = 0

	def has_left(self):
		return self.left != None

	def has_right(self):
		return self.right != None

	def has_both(self):
		return self.has_left() and self.has_right()

	def has_no_children(self):
		return (not self.has_left()) and (not self.has_right())

	def is_left_child(self):
		if self.depth > 0 and self.parent.left != None:
			return self.parent.left.data == self.data
		else:
			return None

	def is_right_child(self):
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
			if self.has_left():
				self.left.get_level(level, result, False)
			if self.has_right():
				self.right.get_level(level, result, False)
		else:
			result.append(self.data)
		return result

	def get_length(self):
		level = 0
		while (len(self.get_level(level))):
			level += 1
		return level

	#this function checks whether a data element
	#is present in the binary tree
	def contains(self, data):
		return (data in self.preorder())

	#this function recursively searches for an element
	#and returns sthe path, by creating the array of
	#its parents and inversing the array
	def path(self, data):
		if self.data == data:
			result = []
			result.append(data)
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

	def print(self):
		row = []

		# row = []
		# total_layers = self.get_length()
		# max_characters = 2 ** (total_layers - 1)
		# max_spaces = (max_characters - 1) * 3
		# max_width = max_characters + max_spaces
		# row.insert(0, object)


		# for i in range(total_layers):
		# 	if total_layers - i > 1:
		# 		dash_counter = 2**(total_layers - i - 1) - 2
		# 	chars = []
		# 	space_before = 2**(total_layers - i) - 2 - dash_counter
		# 	line = " " * space_before
		# 	slashes = " " * ( 2**(total_layers - i) - 2 - dash_counter - 1) + "/"

		# 	self.get_level(i, chars, True)
		# 	for char in chars:
		# 		line += "_" * dash_counter + str(char) + "_" * dash_counter + " " * (2**(total_layers - i + 1) - 1 - dash_counter * 2)
		# 		slashes += " " * (dash_counter * 2 + 1) + "/"
		# 	print(line)
		# 	print(slashes)


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

		if node.has_no_children():
			setattr(node.parent, node.branch, None)
		elif node.has_both():
			temp = node.right.find_min()
			node.data = temp.data
			node.right.rm_node(temp.data)
		else:
			child = node.left if node.has_left() else node.right
			setattr(node.parent, node.branch, child)
