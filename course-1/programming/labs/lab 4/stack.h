/*
	This header file is a library of functionality on stack
	data types.
*/

#ifndef STACK_H
#define STAFF_H

struct stackNode
{
	char data;
	struct stackNode * next;
};

//Initialize a struct
void stackInit(struct stackNode* head)
{
    head = NULL;
}

//push an element into stack
struct stackNode * stackPush(struct stackNode * head, char data)
{
	//Create a temporary node
	struct stackNode * tmp = (struct stackNode*)malloc(sizeof(struct stackNode));

	//If memory is not allocated, exit
	if(tmp == NULL)
		exit(0);
	//set data
	tmp->data = data;
	//point to the last element of the stack	
	tmp->next = head;
	//make the tmp variable the new head	
	head = tmp;
	return head;
};

//Pop an element from stack
struct stackNode * stackPop(struct stackNode *head, char *element)
{
	//Setting the tmp variable to index the last element
	struct stackNode* tmp = head;
	//Read the data into element
	*element = head->data;
	//Make the next item as last
	head = head->next;
	//Free the element that was the last one
	free(tmp);
	return head;
};

//Get the length of a stack
int stackLength(struct stackNode * head)
{
	//Initialize the working variable
	struct stackNode * current;
	//Index to the first value
	current = head;
	int size = 0;
	//If the stack is not empty
	if(current!= NULL)
	{
		do
		{
			size++;
			current = current->next;
		}
		while (current!= NULL);
	}
	return size;

};

//Show the elements of stack
void stackDisplay(struct stackNode * head)
{
	//Initialize the working variable
	struct stackNode * current;
	//Index to the first value
	current = head;
	//If the stack is not empty
	if(current!= NULL)
	{
		do
		{
			printf("%c", current->data);
			current = current->next;
		}
		while (current!= NULL);
		printf("\n");
	}
};

#endif