#include "the3.h"

// do not add extra libraries, but you can define helper functions below.




/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/

int call_counter = 0;
int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count) {
    call_counter++;
    if (call_counter >= 1000000) {
        possible_alignment = "STACK LIMIT REACHED";
        return INT_MIN;
    }

        int len_A = sequence_A.length();
        int len_B = sequence_B.length();

        // Base cases
        if(len_A == 0 && len_B == 0){
            if(possible_alignment == "STACK LIMIT REACHED"){
                return INT_MIN;
            }
            return 0;
        }
        if (len_A <= 0) {
            if(possible_alignment == "STACK LIMIT REACHED"){
                return INT_MIN;
            }
            return -len_B * gap;
        }
    
        if (len_B <= 0) {
            if(possible_alignment == "STACK LIMIT REACHED"){
                return INT_MIN;
            }
            return -len_A * gap;
        }
    
        char char_A = sequence_A.back();
        char char_B = sequence_B.back();
    
        int match_score = (char_A == char_B) ? match : -mismatch;
    
        std::string alignment1, alignment2, alignment3;
        int score1 = recursive_alignment(sequence_A.substr(0, len_A - 1), sequence_B.substr(0, len_B - 1), gap, mismatch, match, alignment1, call_count) + match_score;
        if(score1 == INT_MIN){ 
            possible_alignment = "STACK LIMIT REACHED";
            return INT_MIN;
            
        }
        int score2 = recursive_alignment(sequence_A.substr(0, len_A - 1), sequence_B, gap, mismatch, match, alignment2, call_count) - gap;
        if(score2 == INT_MIN){
            possible_alignment = "STACK LIMIT REACHED";
            return INT_MIN;
        }
        int score3 = recursive_alignment(sequence_A, sequence_B.substr(0, len_B - 1), gap, mismatch, match, alignment3, call_count) - gap;
        if(score3 == INT_MIN){
            possible_alignment = "STACK LIMIT REACHED";
            return INT_MIN;
        }
        
        int max_score = std::max({score1, score2, score3});
        
        if (max_score == score1) {
            possible_alignment = alignment1 + (char_A == char_B ? char_A : '!');
            return score1;
        } else if (max_score == score2) {
            possible_alignment = alignment2 + '.';
            return score2;
        
        } else {
            possible_alignment = alignment3 + '_';
            return score3;
                
        }
    
    
}


int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment) {
    int m = sequence_A.length();
    int n = sequence_B.length();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        dp[i][0] = -i * gap;
    }

    for (int j = 1; j <= n; ++j) {
        dp[0][j] = -j * gap;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int match_score = (sequence_A[i - 1] == sequence_B[j - 1]) ? match : -mismatch;

            dp[i][j] = std::max({dp[i - 1][j - 1] + match_score, dp[i - 1][j] - gap, dp[i][j - 1] - gap});
        }
    }

    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + ((sequence_A[i - 1] == sequence_B[j - 1]) ? match : -mismatch)) {
            possible_alignment = (sequence_A[i - 1] == sequence_B[j - 1]) ? sequence_A[i - 1] + possible_alignment : "!" + possible_alignment;
            --i;
            --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] - gap) {
            possible_alignment = "." + possible_alignment;
            --i;
        } else {
            possible_alignment = "_" + possible_alignment;
            --j;
        }
    }

    return dp[m][n];
}