#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 1000001

int graph_vertexes, graph_edges, mst_edges;
unsigned long long int min_cost = 0; 
int parent[MAX_VERTEX], rank[MAX_VERTEX];

void Kruskals_Algorithm(int edges[][3]);
int Comparitor_4_Edges(const void* a, const void* b);
void Initial_sets(int vertex_num);
int Find_Parent(int target);
void Union(int target1, int target2);

int main(int argc, char* argv[]) {
    //Handling input 將edges建起來
    scanf("%d%d", &graph_vertexes, &graph_edges);
    int edges[graph_edges+1][3];
    mst_edges = graph_vertexes - 1;
    for(int i=0; i<graph_edges; i++){
        int source, destination, cost;
        scanf("%d%d%d", &source, &destination, &cost);
        edges[i][0] = source, edges[i][1] = destination, edges[i][2] = cost;
    }
    //資料讀完後， 將每筆資料（{source, destination, cost}）依照cost由小排到大
    qsort(edges, graph_edges, sizeof(edges[0]), Comparitor_4_Edges);
    //開始進行Kruskal's Algorithm
    Kruskals_Algorithm(edges);
    printf("%llu", min_cost);
    return 0;
}

void Kruskals_Algorithm(int edges[][3]){
    //初始化 共graph_vertexes個 僅含一個元素的set 
    Initial_sets(graph_vertexes);
    //開始進行Kruskal's method 一個一個邊找 共找vertex數量 - 1個邊
    for(int i=0; i<mst_edges;i++){
        //因為已經排序過了 index越小 cost就會越小 所以可以用for迴圈從index = 0開始找
        int tmp_source = Find_Parent(edges[i][0]), tmp_destination = Find_Parent(edges[i][1]), tmp_cost = edges[i][2];
        //如果這兩個的parent不同 代表他們在不同的disjoint set 這條edge就是可以使用的
        //如果這兩個parent相同 就代表他們已經在同一個set 又因set經過path compression（若n個node 一定是n-1條edges）所以再加一條邊就一定會變cycle
        if(tmp_source != tmp_destination){
            Union(tmp_source, tmp_destination);
            min_cost += tmp_cost;
            continue;
        } 
        mst_edges++;
    }
}

int Comparitor_4_Edges(const void* a, const void* b){
    return (((int *)a)[2] - ((int *)b)[2]);
}

void Initial_sets(int vertex_num){
    //rank用以紀錄Disjoint set Tree的高度，用來決定在Union時誰要當新的parent 
    for(int i=0; i<vertex_num; i++) parent[i] = i,rank[i] = 0;
}

int Find_Parent(int target){
    return((parent[target] == target) ? target : (parent[target] = Find_Parent(parent[target])));
}

void Union(int target1, int target2){
    int root1 = Find_Parent(target1), root2 = Find_Parent(target2);
    if(root1 == root2)                   return;
    if(rank[root1] < rank[root2])        parent[root1] = root2;
    else if(rank[root1] > rank[root2])   parent[root2] = root1;
    else                                 parent[root2] = root1, rank[root1]++;
}