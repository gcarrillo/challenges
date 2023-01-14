/*
 * 1519. Number of Nodes in the Sub-Tree With the Same Label
 *
 * https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
 */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EDGES 100

struct node {
	int id;
	struct node *neighbors[MAX_EDGES];
	int num_neighbors;
};

int count_nodes_r(struct node *cur, char *labels, char match, bool *visited,
		  int *count)
{
	struct node *neighbor;
	int i;

	visited[cur->id] = true;

	for (i = 0; i < cur->num_neighbors; i++) {
		neighbor = cur->neighbors[i];

		if (!visited[neighbor->id]) 
			count_nodes_r(neighbor, labels, match, visited, count);
	}

	//printf("%s: looking for %c, node %d has label %c\n", __func__, match, cur->id, labels[cur->id]);
	if (labels[cur->id] == match) {
		//printf("%s: bumping count\n", __func__);
		(*count)++;
	}
}

int count_nodes(int n, struct node *cur, char *labels, char match,
		bool *visited)
{
	int i, count = 0;
	bool *visited_copy;

	visited_copy = (bool *)calloc(n, sizeof(*visited_copy));
	memcpy(visited_copy, visited, n * sizeof(*visited));

	//printf("%s: count nodes that match %c\n", __func__, match);
	count_nodes_r(cur, labels, match, visited_copy, &count);

	free(visited_copy);

	return count;
}

void traverse(struct node *cur, int n, char *labels, bool *visited, int *ans)
{
	struct node *neighbor;
	int i;

	visited[cur->id] = true;

	ans[cur->id] = count_nodes(n, cur, labels, labels[cur->id], visited);

	for (i = 0; i < cur->num_neighbors; i++) {
		neighbor = cur->neighbors[i];

		if (!visited[neighbor->id])
			traverse(neighbor, n, labels, visited, ans);
	}
}

struct node *
build_graph(int n, int **edges, int edgesSize)
{
	struct node *graph, *a, *b;
	int i;

	graph = (struct node *)malloc(n * sizeof(*graph));
	assert(graph);

	for (i = 0; i < n; i++)
		graph[i].id = i;

	for (i = 0; i < edgesSize; i++) {
		a = &graph[edges[i][0]];
		b = &graph[edges[i][1]];

		a->neighbors[a->num_neighbors++] = b;
		b->neighbors[b->num_neighbors++] = a;
	}

	return graph;
}

/**
 * Note: the returned array must be malloced, assume caller calls free().
 */
int *countSubTrees(int n, int **edges, int edgesSize, int *edgesColSize,
		   char *labels, int *returnSize)
{
	int *ans;
	struct node *graph;
	int i;
	bool *visited;

	ans = (int *)malloc(n * sizeof(*ans));
	assert(ans);
	*returnSize = n;

	graph = build_graph(n, edges, edgesSize);
	visited = (bool *)calloc(n, sizeof(*visited));

	traverse(&graph[0], n, labels, visited, ans);

	return ans;
}

void test_case1(void)
{
	int edge1[] = {0, 1};
	int edge2[] = {0, 2};
	int edge3[] = {1, 4};
	int edge4[] = {1, 5};
	int edge5[] = {2, 3};
	int edge6[] = {2, 6};
	int *edges[] = {edge1, edge2, edge3, edge4, edge5, edge6};
	char *labels = "abaedcd";
	int answer[] = {2, 1, 1, 1, 1, 1, 1};
	int edgesColSize = 2;
	int returnSize;
	int *ret;
	int i;

	ret = countSubTrees(7, edges, 6, &edgesColSize, labels, &returnSize);

	for (i = 0; i < returnSize; i++) {
		//printf("ret[%d] = %d, answer[%d] = %d\n", i, ret[i], i, answer[i]);
		assert(ret[i] == answer[i]);
	}
}

void test_case2(void)
{
	int edge1[] = {0, 1};
	int edge2[] = {1, 2};
	int edge3[] = {0, 3};
	int *edges[] = {edge1, edge2, edge3};
	char *labels = "bbbb";
	int answer[] = {4, 2, 1, 1};
	int edgesColSize = 2;
	int returnSize;
	int *ret;
	int i;

	ret = countSubTrees(4, edges, 3, &edgesColSize, labels, &returnSize);

	for (i = 0; i < returnSize; i++) {
		//printf("ret[%d] = %d, answer[%d] = %d\n", i, ret[i], i, answer[i]);
		assert(ret[i] == answer[i]);
	}
}

void test_case3(void)
{
	int edge1[] = {0, 1};
	int edge2[] = {0, 2};
	int edge3[] = {1, 3};
	int edge4[] = {0, 4};
	int *edges[] = {edge1, edge2, edge3, edge4};
	char *labels = "aabab";
	int answer[] = {3, 2, 1, 1, 1};
	int edgesColSize = 2;
	int returnSize;
	int *ret;
	int i;

	ret = countSubTrees(5, edges, 4, &edgesColSize, labels, &returnSize);

	for (i = 0; i < returnSize; i++) {
		//printf("ret[%d] = %d, answer[%d] = %d\n", i, ret[i], i, answer[i]);
		assert(ret[i] == answer[i]);
	}
}

int
main(int argc, char **argv)
{
	test_case1();
	test_case2();
	test_case3();

	printf("All tests passed.\n");

	return 0;
}
