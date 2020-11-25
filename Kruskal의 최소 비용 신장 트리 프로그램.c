// kruskal의 최소 비용 신장 트리 프로그램
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // 부모노드

void setInit(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int setFind(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void setUnion(int a, int b) {
    int root1 = setFind(a);
    int root2 = setFind(b);
    if (root1 != root2)
        parent[root1] = root2;
}

// 간선을 나타내는 구조체
struct Edge {
    int start, end, weight;
};

typedef struct GraphType {
    int n;
    struct Edge edges[2 * MAX_VERTICES];
} graphType;

void initGraph(graphType *g) {
    g->n = 0;
    for(int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void insertEdge(graphType *g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge *)a;
    struct Edge* y = (struct Edge *)b;
    return (x->weight - y->weight);
}

void kruskal(graphType *g) {
    int edgeAccepted = 0;
    int uset, vset;
    struct Edge e;

    setInit(g->n);
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("크루스칼 최소 신장 트리 알고리즘 \n");
    int i = 0;
    while (edgeAccepted < (g->n - 1)) {
        e = g->edges[i];
        uset = setFind(e.start);
        vset = setFind(e.end);

        if (uset != vset) {
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            edgeAccepted++;
            setUnion(uset, vset);
        }
        i++;
    }
}

int main() {
    graphType *g;
    g = (graphType *)malloc(sizeof(graphType));
    initGraph(g);

    insertEdge(g, 0, 1, 29);
    insertEdge(g, 1, 2, 16);
    insertEdge(g, 2, 3, 12);
    insertEdge(g, 3, 4, 22);
    insertEdge(g, 4, 5, 27);
    insertEdge(g, 5, 0, 10);
    insertEdge(g, 6, 1, 15);
    insertEdge(g, 6, 3,18);
    insertEdge(g, 6, 4, 25);

    kruskal(g);
    free(g);

    return 0;
}
