#include "the6.h"

// do not add extra libraries here

using namespace std;

struct Edge {
    int from, to, weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
    
    
    bool operator>(const Edge& other) const {
        return weight > other.weight || (weight == other.weight && from > other.from);
    }
};

int find_structure(std::vector<std::vector<std::pair<int, int>>> &bond_energies,
                   std::vector<std::vector<std::pair<int, int>>> &lowest_energy_structure) {
                       
    int n = bond_energies.size();
    vector<bool> visited(n, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    visited[0] = true;
    for (const auto &edge : bond_energies[0]) {
        pq.push(Edge(0, edge.first, edge.second));
    }

    int lowest_total_energy = 0;

    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        if (visited[current.to]) {
            continue;
        }

        visited[current.to] = true;
        lowest_total_energy += current.weight;
        lowest_energy_structure[current.from].emplace_back(current.to, current.weight);
        lowest_energy_structure[current.to].emplace_back(current.from, current.weight);


        for (const auto &edge : bond_energies[current.to]) {
            if (!visited[edge.first]) {
                pq.push(Edge(current.to, edge.first, edge.second));
            }
        }
    }

    return lowest_total_energy;
}


int find_longest_chain(std::vector<std::vector<std::pair<int, int>>> &molecule_structure,
                       std::vector<int> &chain) {
                           
    int n = molecule_structure.size();
    std::vector<int> dist(n, -1);
    std::queue<int> q;

    q.push(0);
    dist[0] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &neighbor : molecule_structure[u]) {
            int v = neighbor.first;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }


    int farthest_vertex = std::max_element(dist.begin(), dist.end()) - dist.begin();


    q.push(farthest_vertex);
    std::fill(dist.begin(), dist.end(), -1);
    dist[farthest_vertex] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &neighbor : molecule_structure[u]) {
            int v = neighbor.first;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    chain.clear();
    int current_vertex = std::max_element(dist.begin(), dist.end()) - dist.begin();
    int chain_length = dist[current_vertex];
    chain.resize(chain_length + 1);

    for (int i = chain_length; i >= 0; --i) {
        chain[i] = current_vertex;
        for (auto &neighbor : molecule_structure[current_vertex]) {
            int v = neighbor.first;
            if (dist[v] == dist[current_vertex] - 1) {
                current_vertex = v;
                break;
            }
        }
    }

    return chain_length + 1;
}
























