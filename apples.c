#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

bool visit(int start_vertex, int **edges, int edgesSize, int *seconds,
	   bool *hasApple, bool *visited)
{
	int vertex_a, vertex_b, next_vertex;
	bool ret, subgraph_has_apple = false;
	int i;

	visited[start_vertex] = true;

	for (i = 0; i < edgesSize; i++) {
		vertex_a = edges[i][0];
		vertex_b = edges[i][1];

		if (vertex_a == start_vertex && !visited[vertex_b])
			next_vertex = vertex_b;
		else if (vertex_b == start_vertex && !visited[vertex_a])
			next_vertex = vertex_a;
		else
			continue;

		ret = visit(next_vertex, edges, edgesSize, seconds, hasApple,
			    visited);
		if (ret)
			*seconds += 2;

		subgraph_has_apple |= ret;
	}

	if (subgraph_has_apple || hasApple[start_vertex])
		return true;
}

int
minTime(int n, int **edges, int edgesSize, int *edgesColSize, bool *hasApple,
	int hasAppleSize)
{
	int seconds = 0;
	bool *visited;

	visited = (bool *)calloc(n, sizeof(*visited));
	visit(0, edges, edgesSize, &seconds, hasApple, visited);

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
