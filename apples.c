#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_EDGES 3

struct node {
	int id;
	struct node *edges[MAX_EDGES];
	int num_edges;
};

bool visit(struct node *n, struct node *nodes, bool *hasApple, bool *visited,
	   int *seconds)
{
	struct node *next_node;
	int i;
	bool ret, subgraph_has_apple = false;

	visited[n->id] = true;

	for (i = 0; i < n->num_edges; i++) {
		next_node = n->edges[i];

		if (!visited[next_node->id]) {
			ret = visit(next_node, nodes, hasApple, visited,
				    seconds);
			if (ret)
				*seconds += 2;

			subgraph_has_apple |= ret;
		}
	}

	return (subgraph_has_apple || hasApple[n->id]) ? true : false;
}

int
minTime(int n, int **edges, int edgesSize, int *edgesColSize, bool *hasApple,
	int hasAppleSize)
{
	struct node *nodes, *node_a, *node_b;
	int seconds = 0;
	bool *visited;
	int i;

	nodes = (struct node *)malloc(n * sizeof(*nodes));

	for (i = 0; i < n; i++) {
		nodes[i].id = i;
	}

	for (i = 0; i < edgesSize; i++) {
		node_a = &nodes[edges[i][0]];
		node_b = &nodes[edges[i][1]];

		node_a->edges[node_a->num_edges++] = node_b;
		node_b->edges[node_b->num_edges++] = node_a;
	}

	visited = (bool *)calloc(n, sizeof(*visited));
	visit(&nodes[0], nodes, hasApple, visited, &seconds);

	return seconds;
}

void test_case1(void)
{
	int edge1[] = {0, 1};
	int edge2[] = {0, 2};
	int edge3[] = {1, 4};
	int edge4[] = {1, 5};
	int edge5[] = {2, 3};
	int edge6[] = {2, 6};
	int* edges[] = {edge1, edge2, edge3, edge4, edge5, edge6};
	bool hasApple[] = {false, false, true, false, true, true, false};
	int edgesColSize = 2;
	int ret;

	ret = minTime(7, edges, 6, &edgesColSize, hasApple, 7);
	assert(ret == 8);
}

void test_case2(void)
{
	int edge1[] = {0, 1};
	int edge2[] = {0, 2};
	int edge3[] = {1, 4};
	int edge4[] = {1, 5};
	int edge5[] = {2, 3};
	int edge6[] = {2, 6};
	int* edges[] = {edge1, edge2, edge3, edge4, edge5, edge6};
	bool hasApple[] = {false, false, true, false, false, true, false};
	int edgesColSize = 2;
	int ret;

	ret = minTime(7, edges, 6, &edgesColSize, hasApple, 7);
	assert(ret == 6);
}

void test_case3(void)
{
	int edge1[] = {0, 1};
	int edge2[] = {0, 2};
	int edge3[] = {1, 4};
	int edge4[] = {1, 5};
	int edge5[] = {2, 3};
	int edge6[] = {2, 6};
	int* edges[] = {edge1, edge2, edge3, edge4, edge5, edge6};
	bool hasApple[] = {false, false, false, false, false, false, false};
	int edgesColSize = 2;
	int ret;

	ret = minTime(7, edges, 6, &edgesColSize, hasApple, 7);
	assert(ret == 0);
}

void test_case4(void)
{
	int edge1[] = {0, 2};
	int edge2[] = {0, 3};
	int edge3[] = {1, 2};
	int* edges[] = {edge1, edge2, edge3};
	bool hasApple[] = {false, true, false, false};
	int edgesColSize = 2;
	int ret;

	ret = minTime(4, edges, 3, &edgesColSize, hasApple, 4);
	assert(ret == 4);
}

int
main(int argc, char **argv)
{
	test_case1();
	test_case2();
	test_case3();
	test_case4();

	printf("All tests passed.\n");

	return 0;
}
