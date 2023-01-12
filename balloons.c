#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

void print_points(int **points, int pointsSize, int *pointsColSize)
{
	int i, j;

	for (i = 0; i < pointsSize; i++) {
		for (j = 0; j < *pointsColSize; j++) {
			printf("points[%d][%d] == %d\n", i, j, points[i][j]);
		}
	}
}

int compar_x_start(const void *p1, const void *p2)
{
	int **point1 = (int **)p1;
	int **point2 = (int **)p2;

	if ((*point1)[0] < (*point2)[0])
		return -1;

	if ((*point1)[0] > (*point2)[0])
		return 1;

	return 0;

}

int findMinArrowShots(int **points, int pointsSize, int *pointsColSize)
{
	int cur_start, cur_end, min_end = INT_MAX;
	int arrow_shots = 0;
	int i, j;

	/* Sort the points by their x_start value */
	qsort(points, pointsSize, sizeof(*points), compar_x_start);

	for (i = 0; i < pointsSize; i++) {
		cur_start = points[i][0];
		cur_end = points[i][1];

		if (cur_end < min_end)
			min_end = cur_end;

		if (min_end < cur_start) {
			arrow_shots++;
			min_end = cur_end;
		}
	}

	/* burst the remaining balloons */
	++arrow_shots;

	return arrow_shots;
}


void test_case1(void)
{
	int a1[] = {10, 16};
	int a2[] = {2, 8};
	int a3[] = {1, 6};
	int a4[] = {7, 12};
	int *ex_1[] = {a1, a2, a3, a4};
	int points_col_size = 2;
	int ret;

	ret = findMinArrowShots(ex_1, 4, &points_col_size);
	assert(ret == 2);
}

void test_case2(void)
{
	int a1[] = {1, 2};
	int a2[] = {3, 4};
	int a3[] = {5, 6};
	int a4[] = {7, 8};
	int *ex_1[] = {a1, a2, a3, a4};
	int points_col_size = 2;
	int ret;

	ret = findMinArrowShots(ex_1, 4, &points_col_size);
	assert(ret == 4);
}

void test_case3(void)
{
	int a1[] = {1, 2};
	int a2[] = {2, 3};
	int a3[] = {3, 4};
	int a4[] = {4, 5};
	int *ex_1[] = {a1, a2, a3, a4};
	int points_col_size = 2;
	int ret;

	ret = findMinArrowShots(ex_1, 4, &points_col_size);
	assert(ret == 2);
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
