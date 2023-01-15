/*
 * 1519. Number of Nodes in the Sub-Tree With the Same Label
 *
 * https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
 *
 * This version uses the following approach for an O(n) solution, which got
 * accepted:
 * - Use DFS for traversal
 * - Each node to return an array of size 26 to the parent, containing count of
 *   all labels in the subtree of that node.
 * - Store count for each node label in the output array
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

int *
traverse(struct node *cur, char *labels, bool *visited, int *ans)
{
	int *neighbor_counts, *total_counts;
	int node_id, node_label;
	struct node *neighbor;
	int i, j, idx;

	visited[cur->id] = true;

#define NUM_LABELS 26
	total_counts = (int *)calloc(NUM_LABELS, sizeof(*total_counts));
	assert(total_counts);

	node_id = cur->id;
	node_label = labels[node_id];
	idx = node_label - 'a';

	for (i = 0; i < cur->num_neighbors; i++) {
		neighbor = cur->neighbors[i];

		if (!visited[neighbor->id]) {
			neighbor_counts = traverse(neighbor, labels, visited,
						   ans);

			/* Update the counts for neighboring nodes */
			ans[node_id] += neighbor_counts[idx];
			for (j = 0; j < NUM_LABELS; j++)
				total_counts[j] += neighbor_counts[j];

			free(neighbor_counts);
		}
	}

	/* Lastly, update counts for current node */
	ans[node_id]++;
	total_counts[idx]++;

	return total_counts;
}

struct node *
build_graph(int n, int **edges, int edgesSize)
{
	struct node *graph, *a, *b;
	int i;

	graph = (struct node *)calloc(n, sizeof(*graph));
	assert(graph);

	for (i = 0; i < n; i++) {
		graph[i].id = i;
		graph[i].num_neighbors = 0;
	}

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
int *
countSubTrees(int n, int **edges, int edgesSize, int *edgesColSize,
	      char *labels, int *returnSize)
{
	struct node *graph;
	int *counts, *ans;
	bool *visited;

	ans = (int *)calloc(n, sizeof(*ans));
	assert(ans);
	*returnSize = n;

	graph = build_graph(n, edges, edgesSize);
	visited = (bool *)calloc(n, sizeof(*visited));

	counts = traverse(&graph[0], labels, visited, ans);
	free(counts);
	free(graph);

	return ans;
}

void
test_case1(void)
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

void
test_case2(void)
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

void
test_case3(void)
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

	for (i = 0; i < returnSize; i++)
		assert(ret[i] == answer[i]);
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
