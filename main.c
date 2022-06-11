#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
} Node;

/* Function Declarations */
Node* insert_first(int, Node*);
Node* insert_last(int, Node*);
Node* insert_index(int, int, Node*);
Node* delete_first(Node*);
Node* delete_last(Node*);
Node* delete_index(int, Node*);
void search_data(int, Node*);
void print(Node*);

int main(void) { 
	Node* head = NULL;
	int choice, num, index;
	char* temp;

	while (1) {
		printf("===================\n");
		printf("1> Display \n");
		printf("2> Insert First \n");
		printf("3> Insert Last \n");
		printf("4> Insert Anywhere \n");
		printf("5> Delete First \n");
		printf("6> Delete Last \n");
		printf("7> Delete Anywhere \n");
		printf("8> Search \n");
		printf("0> Exit \n");
		printf("Enter your Choice : ");

		if (scanf_s("%d", &choice) != 1) {
			printf("Error!!! Invalid input");
			scanf_s("%s", &temp);
			continue;
		}


		switch (choice) {
			case 0:
				return (0);
				break;
			case 1:
				printf("Elements in the list: \n [");
				print(head);
				printf("] \n insert any key to continue...\n");
				getch();
				break;
			case 2:
				printf("Enter a number to insert : ");
				if (scanf_s("%d", &num) != 1) { 
					printf("Error!!!! Invalid input \n");
					scanf_s("%s", &temp);
					continue;
				}
				head = insert_first(num, head);
				printf("added to the first of the list \n");
				printf("insert any key to continue...\n");
				getch();
				break;
			case 3:
				printf("Enter a number to insert : ");
				if (scanf_s("%d", &num) != 1) {
					printf("Error!!! Invalid input \n");
					scanf_s("%s", &temp);
					continue;
				}
				head = insert_last(num, head);
				printf("added to the last of the list \n");
				printf("insert any key to continue...\n");
				getch();
				break;
			case 4:
				printf("Enter a index number you want to insert(first order starts at 0) : ");
				if (scanf_s("%d", &index) != 1) {
					printf("Error!!! Invalid input \n");
					scanf_s("%s", &temp);
					continue;
				}

				printf("Etner a number to insert: ");
				if (scanf_s("%d", &num) != 1) {
					printf("Error!!! Invalid input \n");
					scanf_s("%s", &temp);
					continue;
				}

				if (head != NULL) {
					head = insert_index(index, num, head);
				}
				else {
					printf("The list is empty \n");
				}

				printf("insert any key to continue...\n");
				getch();
				break;
			case 5:
				head = delete_first(head);
				printf("deleted first node ! \n");
				break;
			case 6:
				head = delete_last(head);
				printf("deleted last node ! \n");
				break;
			case 7:
				printf("Enter a index number you want to delete(first order starts at 0) : ");
				if (scanf_s("%d", &index) != 1) {
					printf("Error!!! Invalid input \n");
					scanf_s("%s", &temp);
					continue;
				}
				head = delete_index(index, head);
				break;
			case 8:
				printf("Enter a data(number) you want to find : ");
				if (scanf_s("%d", &num) != 1) {
					printf("Error!!! Invalid input \n");
					scanf_s("%s", &temp);
					continue;
				}
				search_data(num, head);
				break;
			default:
				printf("Invalid Option. Please Try again.");
				getch();

		}
	}

	return 0;
}

Node* insert_first(int num, Node* head) {
	Node* new_node;
	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = num;
	new_node->next = head;
	head = new_node;
	return head;
}

Node* insert_last(int num, Node* head) {
	Node* current_node = head;
	Node* new_node;
	
	while (current_node != NULL && current_node->next != NULL) {
		current_node = current_node->next;
	}

	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = num;
	new_node->next = NULL;
	if (current_node != NULL) current_node->next = new_node;
	else head = new_node;
	return head;
}

void print(Node* head) {
	Node* current_node = head;
	while (current_node != NULL) {
		printf("%d ", current_node->data);
		current_node = current_node->next;
	}
}

Node* insert_index(int index, int num, Node* head){
	int temp_idx = 0;
	Node* current_node = head;
	Node* new_node;

	if (index == 0) {
		return insert_first(num, head);
	}

	while (temp_idx + 1 != index) {
		if (current_node == NULL) {
			printf("list is empty! you can only insert data to index at 0");
			return head;
		}
			
		if (current_node->next == NULL) {
			printf("last index is %d !!!", temp_idx);
			return head;
		}

		current_node = current_node->next;
		temp_idx++;
	}

	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = num;
	new_node->next = current_node->next;
	current_node->next = new_node;
	return head;
}

Node* delete_first(Node* head) {
	Node* temp = head;
		
	if (temp == NULL) {
		printf("list is empty!");
		return head;
	}

	head = head->next;
	free(temp);
	return head;
}

Node* delete_last(Node* head) {
	Node* temp = head;

	if (temp == NULL) {
		printf("list is empty!");
		return NULL;
	}
	
	if (temp->next == NULL) {
		free(head);
		head = NULL;
		return head;
	}

	while (temp->next->next != NULL) {
		temp = temp->next;
	}
	
	free(temp->next);
	temp->next = NULL;

	return head;
}

Node* delete_index(int index, Node* head) {

	int temp_idx = 0;
	Node* delete_node = head;
	Node* prev_node = head;

	if (index == 0) {
		return delete_first(head);
	}

	while (temp_idx != index) {
		
		if (delete_node == NULL) {
			printf("list is empty !!! \n");
			return head;
		}

		if (delete_node->next == NULL) {
			printf("Last index is %d !!! \n", temp_idx);
			return head;
		}

		delete_node = delete_node->next;

		temp_idx++;
	}

	while (1) {
		if (prev_node->next == delete_node) {
			prev_node->next = delete_node->next;
			delete_node->next = NULL;
			free(delete_node);
			break;
		}
		prev_node = prev_node->next;
	}

	return head;
}

void search_data(int num, Node* head) {
	Node* current_node = head;
	int idx = 0;
	
	if (current_node == NULL) {
		printf("list is empty!!!");
		return;
	}

	while (current_node->data != num) {
		current_node = current_node->next;
		idx++;

		if (current_node == NULL) {
			printf("There is no matched data \n");
			return;
		}
	}

	printf("Data you searched : %d \n", current_node->data);
	printf("Data Founded at index %d(index starts from 0) \n", idx);
	
}