#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>

#define INF INFINITY

using namespace std;

int find_path(vector<vector<int> >& flows_current, vector<vector<int> >& flows_max, int source, int target, int n) {
    int i;
    int vertex_current;
    vector<int> flows_extra(n, 0);
    vector<int> predecessors(n, -1);
    flows_extra[source] = INF;

    queue<int> vertices_path;
    vertices_path.push(source);
    while (!vertices_path.empty()) {
        vertex_current = vertices_path.front();
        vertices_path.pop();
        if (vertex_current == target) break;
        for (i = 0; i < n; i++) {
            if (flows_max[vertex_current][i] - flows_current[vertex_current][i] > 0 && flows_extra[i] == 0) {
                vertices_path.push(i);
                flows_extra[i] =
                        flows_extra[vertex_current] < flows_max[vertex_current][i] - flows_current[vertex_current][i] ?
                        flows_extra[vertex_current] : flows_max[vertex_current][i] - flows_current[vertex_current][i];

                predecessors[i] = vertex_current;
            }
        }
    }

    if (predecessors[target] == -1) return 0;
    vertex_current = target;
    while (vertex_current != source) {
        flows_current[predecessors[vertex_current]][vertex_current] += flows_extra[target];
        vertex_current = predecessors[vertex_current];
    }
    return flows_extra[target];
}

// Максимальный поток
int Max_Stream(vector<vector<int> >& matrix, int source, int target) {
    int n = (int)matrix.size();

    vector<vector<int>> flows(n, vector<int>(n, 0));

    int flow = 0;
    int flow_extra;

    do {
        flow_extra = find_path(flows, matrix, source, target, n);
        flow += flow_extra;
    } while (flow_extra > 0);

    return flow;
}

int Hamilton_check(vector<vector<int>>& matrix, vector<int>& path, vector<bool>& visited, int vertex) {
    path.push_back(vertex);

    if (path.size() == matrix.size())
        return 1;

    visited[vertex] = true;
    int zeros = 0;

    for (int to = 0; to < matrix.size(); ++to) {
        if (matrix[vertex][to] == 0 && matrix[to][vertex] == 0)
            ++zeros;

        if (matrix[vertex][to] > 0 && !visited[to])
            if (Hamilton_check(matrix, path, visited, to) == 1)
                return 1;
    }

    visited[vertex] = false;
    path.pop_back();

    if (zeros == matrix.size())
        return 0;

    return -1;
}

vector<int> Hamilton(vector<vector<int>>& matrix) {
    int n = (int)matrix.size();

    vector<bool> visited(n, false);
    vector<int> path;

    for (int i = 0; i < n; ++i) {
        int found = Hamilton_check(matrix, path, visited, i);

        if (found == 0)
            return {};

        if (found == 1)
            return path;
    }

    return {};
}

void show_vector(vector<int>& vertices) {
    int n = (int)vertices.size();
    cout << endl << "{";
    for (int i = 0; i < n - 1; ++i) {
        cout << vertices[i] << ", ";
    }

    if (n > 0)
        cout << vertices[n - 1] << "}" << endl;
    else cout << "}" << endl;
}

int main() {
    vector<vector<int>> matrix = {
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

    int n = (int)matrix.size();

    int maxFlow = Max_Stream(matrix, 0, n - 1);
    cout << "Max flow: " << maxFlow << endl;

    vector<int> ham_way = Hamilton(matrix);
    cout << "Hamilton way: ";
    show_vector(ham_way);
}