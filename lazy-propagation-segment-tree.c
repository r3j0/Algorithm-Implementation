#include <stdio.h>
#define SIZE 1000000

long long int arr[SIZE];
long long int tree[SIZE * 4];
long long int lazy[SIZE * 4];

long long int init(int start, int end, int idx) {
	if (start == end) {
		tree[idx] = arr[start];
		return tree[idx];
	}
	else {
		int mid = (start + end) / 2;
		tree[idx] = init(start, mid, idx * 2) + init(mid + 1, end, idx * 2 + 1);
		return tree[idx];
	}
}

void update_lazy(int start, int end, int idx) {
	if (lazy[idx] != 0) {
		tree[idx] += (end - start + 1) * lazy[idx];
		if (start != end) {
			lazy[idx * 2] += lazy[idx];
			lazy[idx * 2 + 1] += lazy[idx];
		}
		lazy[idx] = 0;
	}
}

void update_range(int start, int end, int idx, int left, int right, long long int value) {
	update_lazy(start, end, idx);
	if (end < left || right < start) return;
	if (left <= start && end <= right) {
		tree[idx] += (end - start + 1) * value;
		if (start != end) {
			lazy[idx * 2] += value;
			lazy[idx * 2 + 1] += value;
		}
		return;
	}

	int mid = (start + end) / 2;
	update_range(start, mid, idx * 2, left, right, value);
	update_range(mid + 1, end, idx * 2 + 1, left, right, value);
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

long long int query(int start, int end, int idx, int left, int right) {
	update_lazy(start, end, idx);

	if (end < left || right < start) return 0;
	if (left <= start && end <= right) return tree[idx];

	int mid = (start + end) / 2;
	return query(start, mid, idx * 2, left, right) + query(mid + 1, end, idx * 2 + 1, left, right);
}

int main(void) {
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);

	init(0, n - 1, 1);

	for (int i = 0; i < q; i++) {
		int mode = 0;
		scanf("%d", &mode);
		if (mode == 1) {
			int n1, n2;
			long long int n3;
			scanf("%d %d %lld", &n1, &n2, &n3);
			update_range(0, n - 1, 1, n1 - 1, n2 - 1, n3);
		}
		else {
			int n1, n2;
			scanf("%d %d", &n1, &n2);
			printf("%lld\n", query(0, n - 1, 1, n1 - 1, n2 - 1));
		}
	}
	return 0;
}