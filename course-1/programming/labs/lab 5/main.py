from classes import Node, Node_BST
import platform
import os
import keyboard

root = Node_BST(1)

root.add(0)
root.add(2)

root.print()

def clear():
	os.system('cls')
	os.system('clear')

def print_menu():
	clear()
	print("#" * 80)
	print()
	print("    Introduce following buttons to interact:")
	print("")
	print("    0 - cancel")
	print("    1 - initialize tree")
	print("    2 - add node")
	print("    3 - remove node")
	print("    4 - traverse the tree")
	print("    5 - print by a level")
	print("    6 - search a node")
	print()

def print_traverse():
	clear()
	print("#" * 80)
	print()
	print("    Introduce following buttons to interact:")
	print("")
	print("    0 - cancel")
	print("    1 - preorder")
	print("    2 - inorder")
	print("    3 - postorder")
	print()

def print_params():
	clear()
	print("#" * 80)
	print()
	print("    Input the value:")
	print("")



print_menu()
key = input("    Your input: ")
key = int(key)

while(key != 0):
	if (key == 1):
		print_params()
		key = input("    Your input: ")
		key = int(key)
		root = Node_BST(key)
		key = None

	if (key == 2):
		print_params()
		key = input("    Your input: ")
		key = int(key)
		root.add(key)
		key = None

	if (key == 3):
		print_params()
		key = input("    Your input: ")
		key = int(key)
		root.rm_node(key)
		key = None

	if (key == 4):
		print_traverse()
		key = input("    Your input: ")
		key = int(key)

		if key == 1:
			clear()
			print("#" * 80)
			print()
			print(root.preorder())
			key = input("Any key to return: ")
			key = 0
			key = None
		if key == 2:
			clear()
			print("#" * 80)
			print()
			print(root.inorder())
			key = input("Any key to return: ")
			key = 0
			key = None
		if key == 3:
			clear()
			print("#" * 80)
			print()
			print(root.postorder())
			key = input("Any key to return: ")
			key = 0
			key = None

	if (key == 5):
		print_params()
		key = input("    Your input: ")
		key = int(key)
		clear()
		print("#" * 80)
		print("    The result")
		print()
		print("    ", end="")
		print()
		print(root.get_level(key))
		key = input("Any key to return: ")
		key = 0
		key = None

	if (key == 6):
		print_params()
		key = input("    Your input: ")
		key = int(key)
		clear()
		print("#" * 80)
		print("    The result")
		print()
		print("    ", end="")
		print(root.path(key))
		key = input("Any key to return: ")
		key = 0
		key = None


	print_menu()
	key = input("    Your input: ")
	key = int(key)

clear()