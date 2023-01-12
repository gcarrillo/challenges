#include <stdio.h>

#define MAX_DIGITS 3

struct node {
	int val;
	struct node *next;
};

void
print_list(struct node *list)
{
	struct node *cur;

	printf("[");

	for (cur = list; cur != NULL; cur = cur->next) {
		printf("%d", cur->val);

		if (cur->next != NULL)
			printf(",");
	}

	printf("]\n");
}

void
example_1(void)
{
	int tmp, carry = 0;
	struct node *l1p;
	struct node *l2p;
	struct node *l3p;
	struct node l1[] = {
		{.val = 2, .next = &l1[1]},
		{.val = 4, .next = &l1[2]},
		{.val = 3, .next = NULL}
	};
	struct node l2[] = {
		{.val = 5, .next = &l2[1]},
		{.val = 6, .next = &l2[2]},
		{.val = 4, .next = NULL}
	};
	struct node l3[] = {
		{.next = &l3[1]},
		{.next = &l3[2]},
		{.next = NULL}
	};

	for (l1p = l1, l2p = l2, l3p = l3;
			l1p != NULL;
			l1p = l1p->next, l2p = l2p->next, l3p = l3p->next) {
		tmp = l1p->val + l2p->val + carry;
		carry = 0;

		if (tmp > 9) {
			carry = 1;
			tmp -= 10;
		}

		l3p->val = tmp;
	}

	print_list(l1);
	print_list(l2);
	print_list(l3);
}

int
main(int argc, char **argv)
{
	example_1();

	return 0;
}
