#include "the5.h"

// do not add extra libraries here

using namespace std;

void depth_first_search(const vector<vector<int>> &dependencyMatrix, int current,
         vector<int> &order, vector<int> &visited,
         vector<int> &currentPath, bool &isCompilable,
         vector<vector<int>> &cyclicDependencies) {
    visited[current] = 1;
    currentPath.push_back(current);

    for (int next = 0; next < dependencyMatrix.size(); ++next) {
        if (dependencyMatrix[current][next] == 1) {
            bool isCyclic = false;
            for (int node : currentPath) {
                if (node == next) {
                    isCyclic = true;
                    break;
                }
            }

            if (isCyclic) {
                isCompilable = false;
                cyclicDependencies.push_back(currentPath);
            } else if (!visited[next]) {
                depth_first_search(dependencyMatrix, next, order, visited, currentPath, isCompilable, cyclicDependencies);
            }
        }
    }

    currentPath.pop_back();
    order.push_back(current);
}


void run(const std::vector<std::vector<int>>& dependencyMatrix, 
         bool& isCompilable,
         std::vector<int>& compileOrder, 
         std::vector<std::vector<int>>& cyclicDependencies){
             
             
    int numFiles = dependencyMatrix.size();
    isCompilable = true;
    cyclicDependencies.clear();

    vector<int> order;
    vector<int> visited(numFiles, 0);
    vector<int> currentPath;

    for (int file = 0; file < numFiles; ++file) {
        if (!visited[file]) {
            depth_first_search(dependencyMatrix, file, order, visited, currentPath, isCompilable, cyclicDependencies);
        }
    }
    
    if (!isCompilable) {
        compileOrder.clear();
        return;
    }
    
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        compileOrder.push_back(*it);
    }
}