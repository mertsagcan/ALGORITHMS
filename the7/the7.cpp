#include "the7.h"

// do not add extra libraries here

using namespace std;

void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<float>& infection_scores){
    int max_dist = INT_MIN;
    int number_of_nodes = network.size();
    vector<vector<int>> distances(number_of_nodes,vector<int>(number_of_nodes, INT_MAX));
    
    for (int i = 0; i < number_of_nodes; ++i) {
            for (const auto& neighbor : network[i]) {
                int j = neighbor.first;
                int w = neighbor.second;
                distances[i][j] = w;
            }
        }
        
    for (int i = 0; i < number_of_nodes; ++i) {
            distances[i][i] = 0;
        }
        
    for (int k = 0; k < number_of_nodes; ++k) {
        for (int i = 0; i < number_of_nodes; ++i) {
            for (int j = 0; j < number_of_nodes; ++j) {
                if (distances[i][k] != INT_MAX && distances[k][j] != INT_MAX &&
                    distances[i][k] + distances[k][j] < distances[i][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }
    
    for(int src = 0; src < number_of_nodes; src++){
        for(int dst = 0; dst < number_of_nodes; dst++){
            if(distances[src][dst] != INT_MAX && distances[src][dst] > max_dist){
                max_dist = distances[src][dst];
            }
        }
    }
        
    
        
    for(int src = 0; src < number_of_nodes; src++){
        float infection_score = 0;
        for(int dst = 0; dst < number_of_nodes; dst++){
            if(distances[src][dst] == INT_MAX){
                infection_score += max_dist + 1;
            }
            else{
                infection_score += distances[src][dst];
            }
        }
        infection_score /= (number_of_nodes - 1);
        infection_score = 1.0 / infection_score;
        infection_scores.push_back(infection_score);
    }
    
    
}
