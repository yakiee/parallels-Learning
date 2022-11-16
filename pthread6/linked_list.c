#include <stdio.h>
#include <stdlib.h>

char order;
int number;
struct list_node_s *head_p = NULL;
int result;
int flag = 1;

struct list_node_s
{
	int data;
	struct list_node_s *next;
};

int insert(int value, struct list_node_s **head_p)
{
	struct list_node_s *curr_p = *head_p;
	struct list_node_s *pred_p = NULL;
	struct list_node_s *temp_p;

	while (curr_p != NULL && curr_p->data < value)
	{
		pred_p = curr_p;
		curr_p = curr_p->next;
	}

	if (curr_p == NULL || curr_p->data > value)
	{
		temp_p = malloc(sizeof(struct list_node_s));
		temp_p->data = value;
		temp_p->next = curr_p;
		if (pred_p == NULL)
		{
			*head_p = temp_p;
		}
		else
		{
			pred_p->next = temp_p;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int delete (int value, struct list_node_s **head_p)
{
	struct list_node_s *curr_p = *head_p;
	struct list_node_s *pred_p = NULL;

	while (curr_p != NULL && curr_p->data < value)
	{
		pred_p = curr_p;
		curr_p = curr_p->next;
	}

	if (curr_p != NULL && curr_p->data == value)
	{
		if (pred_p == NULL)
		{
			*head_p = curr_p->next;
			free(curr_p);
		}
		else
		{
			pred_p->next = curr_p->next;
			free(curr_p);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int member(int value, struct list_node_s *head_p)
{
	struct list_node_s *curr_p = head_p;

	while (curr_p != NULL && curr_p->data < value)
	{
		curr_p = curr_p->next;
	}

	if (curr_p == NULL || curr_p->data > value)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main()
{
	struct list_node_s *tempo;
	while (1)
	{
		printf("Enter an order (i for insert, d for delete, m for member, q for quit): ");
		scanf("%s", &order);
		if (order != 'i' && order != 'd' && order != 'm' && order != 'q' && order != 'p')
		{
			printf("Invalid order.\n");
			continue;
		}

		if (order == 'i')
		{
			printf("Enter a number: ");
			scanf("%d", &number);
			result = insert(number, &head_p);
			if (result == 1)
			{
				printf("%d inserted\n", number);
			}
			else
			{
				printf("%d already in list\n", number);
			}
		}
		else if (order == 'd')
		{
			printf("Enter a number: ");
			scanf("%d", &number);
			result = delete (number, &head_p);
			if (result == 1)
			{
				printf("%d deleted\n", number);
			}
			else
			{
				printf("%d not in list\n", number);
			}
		}
		else if (order == 'm')
		{
			printf("Enter a number: ");
			scanf("%d", &number);
			result = member(number, head_p);
			if (result == 1)
			{
				printf("%d is in list\n", number);
			}
			else
			{
				printf("%d is not in list\n", number);
			}
		}
		else if (order == 'q')
		{
			break;
		}
		else if (order == 'p')
		{
			if (head_p == NULL)
			{
				printf("List is empty\n");
			}
			else
			{
				printf("List is: ");
				tempo = head_p;
				while (tempo != NULL)
				{
					printf("%d ", tempo->data);
					tempo = tempo->next;
				}
				printf("\n");
			}
		}
	}
}
