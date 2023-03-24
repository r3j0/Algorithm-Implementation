import sys
from collections import deque
input = sys.stdin.readline

n, m = map(int, input().split())

# 진입 차수
indegree = [0] * (n+1)
# 그래프
graph = [[] for _ in range(n+1)]

for i in range(m):
    a, b = map(int, input().split())
    graph[a].append(b)
    indegree[b] += 1
    
def topology_sort():
    result = []
    q = deque()

    # 1. 진입 차수가 0인 노드 먼저 방문
    for i in range(1, n+1):
        if indegree[i] == 0:
            q.append(i)

    while q:
        now = q.popleft()
        result.append(now)

        # 2. 해당 노드랑 연결된 노드의 진입차수 1씩 제거
        for k in graph[now]:
            indegree[k] -= 1
            # 3. 제거된 노드의 진입차수가 0이라면 큐에 추가
            if indegree[k] == 0:
                q.append(k)
    
    # +. 만약 모든 노드를 방문하지 않았다 = 중간에 끊긴 노드가 있다.
    if len(result) != n:
        print(0)
        return
    
    for i in result:
        print(i)

topology_sort()
