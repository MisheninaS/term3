#include <iostream>
#include <vector>

using namespace std;

class Graph{
public:
    int n;
    vector<vector<int>> matrix;
    Graph(){};

    Graph(int n1, vector<vector<int>> arr) : matrix(n1, vector<int>(n1, 0)) {
        n = n1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = arr[i][j];
            }
        }
    }

    void add_vertex() {
        for (int i = 0; i < n; i++) {
            matrix[i].push_back(0); // каждой текущей вершине нужно добавить один нолик, обозначающий
                                    // отсутствие ребра с новой вершиной
        }
        matrix.push_back(vector<int>(n + 1, 0)); // это строка для новой вершины, тоже вся из нулей, так как она не соединена ни с какой другой пока
    }

    void add_edge(int v1, int v2) {
        matrix[v1][v2] = 1;
        matrix[v2][v1] = 1;
    }

    void print_graph() {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

};

void dfs(Graph& graph, int* used, int a) {
    used[a] = 1;
    for (int i = 0; i < graph.n; i++) {
        if ((graph.matrix[a][i] == 1) && (used[i] == 0)){
            dfs(graph, used, i);
        }
    }

}

 int main(){
    vector <vector <int>> a(3, vector<int>(3, 0));
    Graph graph(3, a);
    graph.add_vertex();
    graph.add_edge(0, 1);
    graph.add_edge(1, 3);
    graph.print_graph();
    int* used = new int[graph.n];
    for (int i = 0; i < graph.n; i++) {
        used[i] = 0;
    }
    dfs(graph, used, 0);

 }

