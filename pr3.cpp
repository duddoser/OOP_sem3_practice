#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>

using namespace std;

class Edge
{
public:
    int from, to, weight;
    Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
    Edge(const Edge& E)
    {
        from = E.from;
        to = E.to;
        weight = E.weight;
    }
    int operator<(Edge& E)
    {
        return (weight < E.weight);
    }
    friend ostream& operator<<(ostream& s, Edge& e);
};

ostream& operator<<(ostream& s, Edge& e)
{
    s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
    return s;
}


// Поиск в глубину
void DFS_min_distance(vector<vector<int>> matrix) {
    vector<int> used(matrix.size(), 0);
    vector<int> dist(matrix.size(), 0);

    stack<int> s; s.push(0); int step = 0;
    while (!s.empty()) {
        int cur_vertex = s.top(); s.pop(); // обрабатываем и удаляем из очереди вершину

        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[cur_vertex][i] > 0 && used[i] != 2) {
                s.push(i);
                used[i] = 1;
            }
        }
        if (used[cur_vertex] != 2)
            dist[cur_vertex] = step++;
        used[cur_vertex] = 2;
    }

    cout << "\nDFS result: ";
    for (int i = 0; i < matrix.size(); i++)
        cout << dist[i] << " ";
    cout << endl;
}

bool arr_check(int i, set<int> s) {
    if (auto search = s.find(i); search != s.end())
        return true;
    return false;
}

void DFS(int node, vector<vector<int>> matrix, set<int> &used_, set<int> &vertices_) {
    used_.insert(node);
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[node][i] != 0 && !arr_check(i, used_)) {
            vertices_.insert(i);
            DFS(i, matrix, used_, vertices_);
        }
    }
}

#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <stack>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

class Edge {
public:
    int from, to, weight;

    Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}

    Edge(const Edge &E) {
        from = E.from;
        to = E.to;
        weight = E.weight;
    }

    int operator<(Edge &E) {
        return (weight < E.weight);
    }

    friend ostream &operator<<(ostream &s, Edge &e);
};

ostream &operator<<(ostream &s, Edge &e) {
    s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
    return s;
}

vector<int> BFS(vector<vector<int>> &mat) {
    vector<int> dist(mat.size(), INFINITY);

    queue<int> q;
    q.push(0);
    dist[0] = 0;

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        for (int i = 0; i < mat.size(); i++) {
            //есть ребро vertex->i, в i не заходили
            if (mat[vertex][i] > 0 && (dist[vertex] + mat[vertex][i] < dist[i])) {
                dist[i] = dist[vertex] + mat[vertex][i];
                q.push(i);
            }
        }
    }
    return dist;
}

// Минимальный остов через алгоритм Прима
vector<Edge> Prima_alg(vector<vector<int>> matrix) {
    vector<int> used(matrix.size(), 0);
    int mst_weight = 0;     // Текущий вес остова.

    vector<Edge> edges;     //рассматриваемые ребра
    vector<Edge> tree_edges;    //ребра в минимальном остове

    edges.push_back(Edge(0, 0, 0));     //Начнём с вершины 0

    while (!edges.empty())
    {
        int min_index = 0;
        Edge min_edge = edges[0];
        for (int i = 1; i < edges.size(); i++) {
            if (edges[i] < min_edge) {
                min_index = i;
                min_edge = edges[i];
            }
        }

        edges.erase(edges.begin() + min_index);
        if (used[min_edge.to]) continue;
        used[min_edge.to] = 1;

        int to = min_edge.to;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[to][i] > 0 && !used[i])
                edges.push_back(Edge(to, i, matrix[to][i]));
        }
        tree_edges.push_back(min_edge);
        mst_weight += min_edge.weight;
    }

    cout << mst_weight << endl;
    return tree_edges;
}

void BFS_Degrees(vector<vector<int>>& matrix) {
    vector<Edge> minspan = Prima_alg(matrix);

    vector<int> dsum(matrix.size());
    for (int i = 0; i < minspan.size(); i++) {
        dsum[minspan[i].from]++;
        dsum[minspan[i].to]++;
    }

    int suum = 0;
    for (int i = 0; i < dsum.size(); i++) {
        cout << "Degree of vertex {" << i + 1 << "} = " << dsum[i] << '\n';
        suum += dsum[i];
    }

    // Все степени вершин
    cout << "\nVertex degrees sum: " << suum / 2 << '\n';

    // Средняя степень вершин
    int mean_value = suum / dsum.size();
    cout << "Mean value:" << mean_value << '\n';

}


int main() {
    vector<vector<int>> matrix =
            {
                    {0, 8, 2, 0, 5, 1, 7, 3, 5, 9, 3, 7},
                    {8, 0, 7, 5, 7, 1, 9, 1, 1, 6, 6, 9},
                    {2, 7, 0, 9, 3, 5, 1, 9, 1, 0, 8, 0},
                    {0, 5, 9, 0, 8, 8, 4, 0, 3, 5, 7, 8},
                    {5, 7, 3, 8, 0, 1, 7, 3, 0, 6, 8, 9},
                    {1, 1, 5, 8, 1, 0, 7, 0, 0, 8, 6, 9},
                    {7, 9, 1, 4, 7, 7, 0, 0, 7, 2, 5, 8},
                    {3, 1, 9, 0, 3, 0, 0, 0, 1, 8, 8, 1},
                    {5, 1, 1, 3, 0, 0, 7, 1, 0, 8, 6, 9},
                    {9, 6, 0, 5, 6, 8, 2, 8, 8, 0, 2, 7},
                    {3, 6, 8, 7, 8, 6, 5, 8, 6, 2, 0, 4},
                    {7, 9, 0, 8, 9, 9, 8, 1, 9, 7, 4, 0}
            };

    // Реализация BFS от 1 вершины
    vector<int> dist = BFS(matrix);
    for (int i = 0; i < matrix.size(); i++)
        cout << " Vertex: " << i + 1 << " Distance: " << dist[i] << '\n';

    // Минимальное Остовное дерево
    cout << "\nMinimal spanning tree weight: " << endl;

    vector<Edge> mst = Prima_alg(matrix);
    for (auto & i : mst)
        cout << i << endl;

    // Степени вершин остовного дерева
    cout << endl;
    BFS_Degrees(matrix);
    return 0;
}

vector<int> BFS_Degree_count(vector<vector<int>> &matrix) {
    vector<int> used(matrix.size(), 0);
    vector<int> dist(matrix.size(), 0);

    vector<int> degrees(matrix.size());


    queue<int> q; q.push(0);
    while (!q.empty()) {
        int cur_vertex = q.front(); q.pop(); // обрабатываем и удаляем из очереди вершину
        int count = 0;
        for (int i = 0; i < matrix.size(); i++) {

            // проверяем есть ли сосед у вершины,
            //  проверка посетили ли мы вершину или нет,
            //  а если мы там были то мы были там уже по более короткому пути
            if (matrix[cur_vertex][i] > 0 && used[i] == 0) {
                q.push(i);
                used[i] = 1;
                dist[i] = dist[cur_vertex] + 1; // стоимость
                for (auto &edge : matrix[cur_vertex])
                    if (edge != 0)
                        count++;
            }
        }
        degrees[cur_vertex] = count;
        used[cur_vertex] = 2;
    }
    return degrees;
}

int Mean_Degrees(const vector<int> &degrees) {
    int sum = 0;
    for (auto &i : degrees) {
        sum = sum + i;
    }
    return (sum/(int)degrees.size());
}

int main() {
    vector<vector<int>> matrix = {
            { 0, 8, 2, 0, 5, 1, 7, 3, 5, 9, 3, 7 },
            { 8, 0, 7, 5, 7, 1, 9, 1, 1, 6, 6, 9 },
            { 2, 7, 0, 9, 3, 5, 1, 9, 1, 0, 8, 0 },
            { 0, 5, 9, 0, 8, 8, 4, 0, 3, 5, 7, 8 },
            { 5, 7, 3, 8, 0, 1, 7, 3, 0, 6, 8, 9 },
            { 1, 1, 5, 8, 1, 0, 7, 0, 0, 8, 6, 9 },
            { 7, 9, 1, 4, 7, 7, 0, 0, 7, 2, 5, 8 },
            { 3, 1, 9, 0, 3, 0, 0, 0, 1, 8, 8, 1 },
            { 5, 1, 1, 3, 0, 0, 7, 1, 0, 8, 6, 9 },
            { 9, 6, 0, 5, 6, 8, 2, 8, 8, 0, 2, 7 },
            { 3, 6, 8, 7, 8, 6, 5, 8, 6, 2, 0, 4 },
            { 7, 9, 0, 8, 9, 9, 8, 1, 9, 7, 4, 0 }
    };

    // ---- 1 ---- Остовное дерево
    vector<Edge> tree_edges = Prima_alg(matrix);

    cout << "\n-----Min skeleton-----\n";
    for (auto &edge : tree_edges) {
        cout << edge << endl;
    }

    // ---- 2 ----
    cout << "\n------Min distance-----\nMatrix:";
    DFS_min_distance(matrix);

    cout << "\n------All vertices DFS------\n";
    set<int> used;
    set<int> vertices;
    DFS(0, matrix, used, vertices);
    for (auto &i : vertices) {
        cout << i << " ";
    } cout << endl;

    cout << "\n------BFS Degrees------\n";
    vector<int> degrees = BFS_Degree_count(matrix);

    for (int i = 0; i < degrees.size(); i++)
        cout << i << ": " << degrees[i] << endl;

    cout << "\n------Mean Degrees------\n";

    int mean_degree = Mean_Degrees(degrees);
    cout << mean_degree << endl;
}