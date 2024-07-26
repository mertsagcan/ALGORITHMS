#include "the4.h"

using namespace std;
// do not add extra libraries here

int divide_land(int X, int Y, bool** possible_plots) {
    
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int i = 0; i <= X; ++i) {
        for (int j = 0; j <= Y; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (possible_plots[i][j]) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = i * j;  
            }
        }
    }

    
    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            for (int k = 1; k < i; ++k) {
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j]);
            }
            for (int k = 1; k < j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
        }
    }

    return dp[X][Y];
}