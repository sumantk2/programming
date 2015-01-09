#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct single_list {
	int data;
	struct single_list *next;
}*head = NULL;

void print(char *i)
{
	printf("\n 1. add to a list			\	
		\n 2, Delete				\
		\n 3. print the list elements		\
		\n 4. exit the program\n");		
	scanf(" %c", i);
	
}

/*Add an element at the tail of the list */
int add()
{
	struct single_list *temp, *list;
	temp = (struct single_list *)malloc(sizeof(struct single_list));
	if(!temp)
		return -ENOMEM;
	printf("\n enter the data for this element");
	/* validation is not done here */
	scanf("%d", &temp->data);
	if(!head) {
		head = temp;
		head->next = NULL;
	} else {
		list = head;
		while(list->next)
			list = list->next;
		list->next = temp;
		temp->next = NULL;
	}
	return 0;
		
}

/* Delete from the end.In next version, we will find an element an delete from the list */
int delete()
{
	struct single_list *list, *prev;
	list = head;
	prev = list;
	if(!list) {
		printf("\n linked list doesnt contain anything. Add an element");
		return 1;
	}
	while(list->next) {
		prev = list;
		list = list->next;
	}

	prev->next = NULL;
	if(list == head) {
		free(list);
		head = NULL;
		return 0;
	}
	free(list);
	return 0;
}

void traverse()
{
	struct single_list *list;
	list = head;
	while(list) {
		printf("---> %d", list->data);
		list = list->next;
	}

}

int main()
{
	int rc = 0;
	char i;
	for(;;) {
		print(&i);
		switch(i) {
			case '1': 
				rc = add();
				break;
			case '2': 
				rc = delete();
				break;
			case '3': 
				traverse();
				break;
			case '4': 
				exit(0);
				break;
			default: 
				printf("\n not a valid value");
		}
	}
	return 0;
}
