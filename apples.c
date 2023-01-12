#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_EDGES 3

struct node {
	int id;
	struct node *neighbors[MAX_EDGES];
	int num_neighbors;
};

bool traverse(struct node *graph, struct node *n, bool *hasApple, bool *visited,
	      int *seconds)
{
	bool ret, subgraph_has_apple = false;
	struct node *neighbor;
	int i;

	visited[n->id] = true;

	for (i = 0; i < n->num_neighbors; i++) {
		neighbor = n->neighbors[i];

		if (!visited[neighbor->id]) {
			ret = traverse(graph, neighbor, hasApple, visited,
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
	struct node *graph, *a, *b;
	int seconds = 0;
	bool *visited;
	int i;

	graph = (struct node *)malloc(n * sizeof(*graph));

	for (i = 0; i < n; i++) {
		graph[i].id = i;
	}

	for (i = 0; i < edgesSize; i++) {
		a = &graph[edges[i][0]];
		b = &graph[edges[i][1]];

		a->neighbors[a->num_neighbors++] = b;
		b->neighbors[b->num_neighbors++] = a;
	}

	visited = (bool *)calloc(n, sizeof(*visited));

	traverse(graph, &graph[0], hasApple, visited, &seconds);

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
