#include <stdio.h>
#define SIZE 100000

long long int arr[SIZE];
long long int tree[SIZE * 4];

long long int init(int start, int end, int idx) {
    if(start == end) {
        tree[idx] = arr[start];
        return tree[idx];
    }

    int mid = (start + end) / 2;
    tree[idx] = init(start, mid, idx * 2) + init(mid + 1, end, idx * 2 + 1);
    return tree[idx];
}

long long int interval_sum(int start, int end, int idx, int left, int right) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[idx];

    int mid = (start + end) / 2;
    return interval_sum(start, mid, idx * 2, left, right) + interval_sum(mid + 1, end, idx * 2 + 1, left, right);
}

void update(int start, int end, int idx, int what, int value) {
    if(what < start || what > end) return;
    if(start == end) {
        tree[idx] += value;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, idx * 2, what, value);
    update(mid + 1, end, idx * 2 + 1, what, value);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

int main(void) {
    int n;
    scanf("%d", &n);

    // Input Array Data
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);

    init(0, n - 1, 1);

    int q;
    scanf("%d", &q);

    for(int i = 0; i < q; i++) {
        int mode;
        long long int n1, n2;
        scanf("%d %lld %lld", &mode, &n1, &n2);
        if(mode == 1) // Sum
            printf("%lld\n", interval_sum(0, n - 1, 1, n1 - 1, n2 - 1));
        else // Update
            update(0, n - 1, 1, n1 - 1, n2);
    }
    return 0;
}