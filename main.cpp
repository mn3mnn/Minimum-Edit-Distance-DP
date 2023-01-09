// minimum number of operations to convert str1 into str2
// print the best alignment of two strings

// Time and Space:  O(m * n), for min_edit_distance()


#include <iostream>
#include <string>
#include <vector>

using namespace std;

int min(int a, int b, int c){
    return min(min(a, b), c);
}

// alignment1 and alignment2 store the aligning result of str1 and str2
// i and j are the indices of last node in the dp table
void outputAlignment(vector<vector<int>>& dp, string& str1, string& str2, string& alignment1, string& alignment2, int i, int j){
    // index of resulting string
    static int k = max(str1.length() + 1, str2.length());

    // base case
    if (i == 0 && j == 0){
        return;
    }

    // if backtrace arrow coming form up
    // and if coming both from up and diagonal choose the diagonal one
    if (i > 0 && dp[i][j] == dp[i - 1][j] + 1 && dp[i][j] != dp[i - 1][j - 1] + 1){
        alignment1[k--] = str1[i - 1];
        outputAlignment(dp, str1, str2, alignment1, alignment2, i - 1, j);
    }

    // if backtrace arrow coming form left
    // and if coming both from left and diagonal choose the diagonal one
    else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1 && dp[i][j] != dp[i - 1][j - 1] + 1){
        alignment2[k--] = str2[j - 1];
        outputAlignment(dp, str1, str2, alignment1, alignment2, i, j - 1);
    }

    // if backtrace arrow coming diagonal
    else{
        alignment1[k] = str1[i - 1];
        alignment2[k] = str2[j - 1];
        k--;
        outputAlignment(dp, str1, str2, alignment1, alignment2, i - 1, j - 1);
    }
}

// return minimum edit distance
// return minimum cost of aligning two strings
int min_edit_distance(string str1, string str2, vector<vector<int>>& dp){

    int len1 = str1.length();
    int len2 = str2.length();

    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            // number of ops (cost) = the len of the other string
            if (i == 0){
                dp[i][j] = j;
            }
            // number of ops (cost) = the len of the other string
            else if (j == 0)
            {
                dp[i][j] = i;
            }
            else {
                // 0 cost for match, 1 for mismatch
                int matchingCost = (str1[i - 1] == str2[j - 1] ? 0 : 1);

                dp[i][j] = min(dp[i - 1][j - 1] + matchingCost,// diagonal (replace)
                               dp[i - 1][j] + 1, // (delete)
                               dp[i][j - 1] + 1); // (insert)
            }
        }
    }
    return dp[len1][len2];
}


int main(){

    string str1 = "editing";
    string str2 = "distance";

    // table of costs
    vector<vector<int>> dp(str1.length() + 1, vector<int>(str2.length() + 1));

    // initialize two strings to use them as a result of aligning
    string alignment1(max(str1.length(), str2.length()) + 1, '_');
    string alignment2(max(str1.length(), str2.length()) + 1, '_');

    cout << min_edit_distance(str1, str2, dp) << '\n';

    outputAlignment(dp, str1, str2, alignment1, alignment2, str1.length(), str2.length());

    cout << alignment1 << '\n';
    cout << alignment2 << '\n';

    return 0;
}
