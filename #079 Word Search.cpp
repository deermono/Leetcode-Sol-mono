/**
 * Given a 2D board and a word, find if the word exists in the grid.
 *
 * The word can be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring. The
 * same letter cell may not be used more than once.
 *
 * For example,
 * Given board =
 * [
 *   ["ABCE"],
 *   ["SFCS"],
 *   ["ADEE"]
 * ]
 *
 * word = "ABCCED", -> returns true,
 * word = "SEE", -> returns true,
 * word = "ABCB", -> returns false.
 *
 * Tags: Array, Backtracking
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        for(int i=0;i<board.size();i++)
            for(int j=0;j<board[i].size();j++)
                if(searchHelper(board, word, 0, i, j))
                    return true;
        return false;
    }
    
    bool searchHelper(vector<vector<char> > &board, string word, int index, int i, int j){
        if(index==word.length())
            return true;
        if(i<0 || i>=board.size() || j<0 || j>=board[0].size() || board[i][j]!=word[index] || board[i][j]=='\0')
            return false;
        char c=board[i][j];
        board[i][j]='\0';
        if(searchHelper(board, word, index+1, i-1, j)
           || searchHelper(board, word, index+1, i, j-1)
           || searchHelper(board, word, index+1, i+1, j)
           || searchHelper(board, word, index+1, i, j+1))
            return true;
        board[i][j]=c;
        return false;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<vector<char>> board;
    board.push_back(vector<char>({'A', 'B', 'C', 'E'}));
    board.push_back(vector<char>({'S', 'F', 'E', 'S'}));
    board.push_back(vector<char>({'A', 'D', 'E', 'E'}));
    Solution s;
    if(s.exist(board, "ABCESEEEFS"))
        std::cout << "Hello, World!\n";
    return 0;
}
