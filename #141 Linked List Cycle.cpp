/**
 * Given a linked list, determine if it has a cycle in it.
 *
 * Follow up:
 * Can you solve it without using extra space?
 *
 * Tags: Linkedlist, Two pointers
 */

#include <iostream>

using namespace std;

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <queue>
#include "RNGV.cpp"
#include "RNGVFloat.cpp"
#include "ArraysIntersection.cpp"

using namespace std;

class TreeNode{
public:
    int val;
    TreeNode *left, *right;
    
    TreeNode(int n){
        val = n;
        left = right = NULL;
    }
};

TreeNode* copySymmetric(TreeNode *p){
    if(!p)
        return nullptr;
    TreeNode *t = new TreeNode(p->val);
    t->left = copySymmetric(p->right);
    t->right = copySymmetric(p->left);
    return t;
}

double eatBean(int white, int red){
    // if w = 0, then p = 0;
    // if r = 0, and w is not 0, then p = 1
    // else, p = (w/ (r + w))(p(r, w - 1)) + (r/ (r + w))((w/ (r + w))(p(r, w - 1)) + (r/ (r + w)(p(r - 1, w)))
    vector<vector<double>> dp(white + 1, vector<double>(red + 1, 0));
    for(int i = 0; i <= white; i++)
        dp[i][0] = 1;
    for(int j = 1; j <= red; j++)
        dp[0][j] = 0;
    for(int i = 1; i <= white; i++){
        for(int j = 1; j <= red; j++){
            double p1 = ((double)i / (i + j)), p2 = ((double)j / (i + j));
            dp[i][j] = p1 * dp[i - 1][j] + p2 * (p1 * dp[i - 1][j] + p2 * dp[i][j - 1]);
        }
    }
    return dp[white][red];
}

int numDistinct(string s, string t) {
    int m = s.length(), n = t.length();
    int dp[m + 1][n + 1];
    // dp[i + 1][j + 1] means the numebr of ways s[0..i] could match t[0..j]
    for(int j = 0; j <= n; j++)
        dp[0][j] = 0;
    for(int i = 0; i <= m; i++)
        dp[i][0] = 1;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(s[i] == t[j])
                dp[i + 1][j + 1] = dp[i][j] + dp[i][j + 1];
            else
                dp[i + 1][j + 1] = dp[i][j + 1];
        }
    }
    return dp[m][n];
}

bool isMatch(string s, string p) {
    int m = s.length(), n = p.length();
    // dp[i][j] means if s[0..i] can match p[0..j]
    // if p[j] is a character, dp[i][j] = dp[i - 1][j - 1] && s[i] == p[j]
    // if p[j] is '.', dp[i][j] = dp[i - 1][j - 1]
    // if p[j] is '*':
    // dp[i][j] = dp[i][j - 2], '*' matches 0 times
    // dp[i][j] = dp[i][j - 1], '*' matches 1 time
    // dp[i][j] = dp[i - 1][j] && (s[i] == p[j - 1] && || p[j - 1] is '.'), '*' matches 2 or more times
    bool dp[m + 1][n + 1];
    dp[0][0] = true;
    for(int i = 1; i <= m; i++)
        dp[i][0] = false;
    for(int j = 1; j <= n; j++)
        dp[0][j] = p[j - 1] == '*' && dp[0][j - 2] == true;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(p[j] != '*')
                dp[i + 1][j + 1] = dp[i][j] && (s[i] == p[j] || p[j] == '.');
            else
                dp[i + 1][j + 1] = dp[i + 1][j - 1] || dp[i + 1][j] ||
                                        (dp[i][j + 1] && (s[i] == p[j - 1] || p[j - 1] == '.'));
        }
    }
    return dp[m][n];
}

unordered_map<int, int> inorder_rec;
TreeNode* constructTree(vector<int>& inorder, int l, int r, vector<int>& postorder, int p){
    if(l > r)
        return nullptr;
    int n = postorder[p], index = inorder_rec[n];
    TreeNode *root = new TreeNode(n);
    root->left = constructTree(inorder, l, index - 1, postorder, p - r + index - 1);
    root->right = constructTree(inorder, index + 1, r, postorder, p - 1);
    return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder){
    int n = inorder.size();
    for(int i = 0; i < n; i++)
        inorder_rec[inorder[i]] = i;
    TreeNode *root = constructTree(inorder, 0, n - 1, postorder, n - 1);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildHelper(preorder, 0, inorder, 0, inorder.size() - 1);
}

TreeNode* buildHelper(vector<int>& preorder, int p, vector<int>& inorder, int start, int end){
    if(start > end)
        return NULL;
    TreeNode *root = new TreeNode(preorder[p]);
    int pos = 0;
    for(int i = start; i <= end; i++)
        if(inorder[i] == preorder[p])
            pos = i;
    root->left = buildHelper(preorder, p + 1, inorder, start, pos - 1);
    root->right = buildHelper(preorder, p + pos - start + 1, inorder, pos + 1, end);
    return root;
}

class RNG{
private:
    double sum = 0;
    map<double, int> rec;
public:
    RNG(vector<double> nums){
        int i = 0;
        for(auto n : nums){
            sum += n;
            rec[sum] = i++;
        }
        srand(time(0));
    }
    
    int generate(){
        double num = ((double)rand() / RAND_MAX);
        return rec.upper_bound(num)->second;
    }
};

class RNGV{
private:
    int sum;
    map<int, char> rec;
    
public:
    RNGV(vector<pair<char, int>>& nums){
        sum = 0;
        for(auto p : nums){
            sum += p.second;
            rec[sum] = p.first;
        }
        srand(time(0));
    }
    
    char generateRandom(){
        int num = rand() % sum;
        return rec.upper_bound(num)->second;
    }
};

class NestedIterator {
    stack<NestedInteger> rec;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        int n = nestedList.size(); 
        for(int i = n - 1; i >= 0; i--)
            rec.push(nestedList[i]);
    }

    int next() {
        if(!rec.empty()){
            int n = rec.top().getInteger();
            rec.pop();
            return n;
        }
        return -1;
    }

    bool hasNext() {
        while(!rec.empty()){
            if(rec.top().isInteger())
                return true;
            else{
                auto t = rec.top();
                rec.pop();
                auto list = t.getList();
                int n = list.size(); 
                for(int i = n - 1; i >= 0; i--)
                    rec.push(list[i]);
            }
        }
        return false;
    }
};

string transform(vector<int>& ans){
    string ret = to_string(ans[0]);
    for(int i = 1; i < ans.size(); i++)
        ret += "->" + to_string(ans[i]);
    return ret;
}

void dfsFind(vector<int>& nodes, vector<int>& ans, unordered_map<int, vector<int>>& rec, unordered_set<int>& pathChecking, vector<string>& ret){
    ret.push_back(transform(ans));
    for(auto n : nodes){
        if(!pathChecking.count(n)){
            ans.push_back(n);
            pathChecking.insert(n);
            dfsFind(rec[n], ans, rec, pathChecking, ret);
            ans.pop_back();
            pathChecking.erase(n);
        }
    }
}

vector<string> dfsFindPath(vector<pair<int, int>> links, int start){
    unordered_map<int, vector<int>> rec;
    for(auto p : links)
        rec[p.first].push_back(p.second);
    vector<string> ret;
    vector<int> ans = {start};
    unordered_set<int> pathChecking = {start};
    dfsFind(rec[start], ans, rec, pathChecking, ret);
    return ret;
}

vector<pair<int, int>> backChain(unordered_map<int, int>& reachedFrom, int p, int m, int n){
    vector<pair<int, int>> ret;
    while(p != -1){
        ret.push_back(make_pair(p / n, p % n));
        p = reachedFrom[p];
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

vector<pair<int, int>> breakMaze(vector<vector<int>>& maze){
    int m = maze.size(), n = m ? maze[0].size() : 0;
    queue<int> q;
    unordered_set<int> rec;
    unordered_map<int, int> reachedFrom;
    vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    rec.insert(0);
    reachedFrom[0] = {-1};
    q.push(0);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        int x = p / n, y = p % n;
        if(x == m - 1 && y == n - 1)
            return backChain(reachedFrom, p, m, n);
        for(auto d : dirs){
            if(x + d[0] >= 0 && x + d[0] < m && y + d[1] >= 0 && y + d[1] < n && maze[x + d[0]][y + d[1]] != 1){
                int pos = (x + d[0]) * n + y + d[1];
                if(!rec.count(pos)){
                    rec.insert(pos);
                    reachedFrom[pos] = p;
                    q.push(pos);
                }
            }
        }
    }
    return {};
}

int breakMaze_II(vector<vector<int>>& maze){
    int m = maze.size(), n = m ? maze[0].size() : 0;
    int steps = 0;
    queue<int> q;
    unordered_set<int> rec;
    vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    rec.insert(0);
    q.push(0);
    while(!q.empty()){
        int l = q.size();
        for(int i = 0; i < l; i++){
            int p = q.front();
            q.pop();
            int x = p / n, y = p % n;
            if(x == m - 1 && y == n - 1)
                return steps;
            for(auto d : dirs){
                int x1 = x + d[0], y1 = y + d[1];
                if(x1 >= 0 && x1 < m && y1 >= 0 && y1 < n && maze[x1][y1] != 1){
                    int pos = x1 * n + y1;
                    if(!rec.count(pos)){
                        rec.insert(pos);
                        q.push(pos);
                    }
                }
            }
        }
        steps++;
    }
    return -1;
}


string removeParen(string s){
    int n = 0;
    string ret = "", tmp = "";
    for(auto c : s){
        if(c == '('){
            n++;
            tmp += '(';
        }else if(n > 0){
            n--;
            tmp += ')';
        }
    }
    n = 0;
    for(int i = tmp.size() - 1; i >= 0; i--){
        if(tmp[i] == ')'){
            ret += ')';
            n++;
        }else if(n > 0){
            ret += '(';
            n--;
        }
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

struct compareWordFrequency{
    bool operator()(pair<int, string>& a, pair<int, string>& b){
        return a.first > b.first;
    }
};

vector<string> topKWords(string s, int k){
    vector<string> ret;
    istringstream ss(s);
    string word;
    unordered_map<string, int> rec;
    priority_queue<pair<int, string>, vector<pair<int, string>>, compareWordFrequency> topKList;
    while(ss >> word)
        rec[word]++;
    for(auto it = rec.begin(); it != rec.end(); it++){
        if(topKList.size() < k){
            auto p = make_pair(it->second, it->first);
            topKList.push(p);
        }else if(it->second > topKList.top().first){
            topKList.pop();
            auto p = make_pair(it->second, it->first);
            topKList.push(p);
        }
    }
    while(!topKList.empty()){
        auto p = topKList.top();
        topKList.pop();
        ret.push_back(p.second);
    }
    return ret;
}

string LongestAscendingSubstring(string s){
    int i = 1, j = 0;
    string ret = "";
    while(i <= s.length()){
        if(i == s.length() || s[i] < s[i - 1]){
            if(ret.length() < i - j)
                ret = s.substr(j, i - j);
            j = i;
        }
        i++;
    }
    return ret;
}

void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    reverse(nums.begin(), nums.begin() + n - k);
    reverse(nums.begin() + n - k, nums.end());
    reverse(nums.begin(), nums.end());
}

bool wordBreak(string s, unordered_set<string>& wordDict) {
    int m = s.length();
    if(m == 0)
        return false;
    vector<bool> dp(m + 1, false);
    dp[0] = true;
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < i; j++){
            if(dp[j] && wordDict.count(s.substr(j, i - j))){
                dp[i] = true;
                break;
            }
        }
    }
    return dp[m];
}

void findCombinations(string& digits, int index, string ans, string buttons[], vector<string>& ret){
    if(index == digits.length()){
        ret.push_back(ans);
        return;
    }
    for(int i = 0; i < buttons[digits[index] - '0'].length(); i++){
        ans += buttons[digits[index] - '0'][i];
        findCombinations(digits, index + 1, ans, buttons, ret);
        ans.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    string buttons[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ret;
    string ans = "";
    if(!digits.empty())
        findCombinations(digits, 0, ans, buttons, ret);
    return ret;
}

class fakeStack{
private:
    struct ListNode{
        int val;
        ListNode *next;
        
        ListNode(int val){
            this->val = val;
            next = nullptr;
        }
    };
    
    ListNode *root = nullptr;
    int stk_size = 0;
    
public:
    void push(int n){
        ListNode *node = new ListNode(n);
        node->next = root;
        root = node;
        stk_size++;
    }
    
    int top(){
        if(root == nullptr){
            cout << "NO more elements" << endl;
            return -1;
        }
        return root->val;
    }
    
    void pop(){
        if(root != nullptr){
            ListNode *t = root;
            root = root->next;
            delete t;
            stk_size--;
        }
    }
    
    int size(){
        return stk_size;
    }
    
    bool empty(){
        return stk_size;
    }
    
    ~fakeStack(){
        while(root){
            ListNode *t = root;
            root = root->next;
            delete t;
        }
    }
    
};

vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> ret;
        int n = words.size(), i = 0;
        while(i < n){
            int width = 0, space = 0, start = i;
            while(i < n && width + space + words[i].length() <= maxWidth){
                width += words[i++].length();
                space++;
            }
            int avg_space = i == n ? 1 : i - start > 1 ? (maxWidth - width) / (i - start - 1) : 0;
            space = maxWidth - width - avg_space * (i - start - 1);
            string line = words[start++];
            while(start < i){
                if(i != n)
                    line += string(avg_space + (space-- > 0 ? 1 : 0), ' ') + words[start++]; 
                else
                    line += " " + words[start++];
            }
            if(space > 0)
                line += string(space, ' ');
            ret.push_back(line);
        }
        return ret;
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow=head;
        ListNode *fast=head;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast)
                return true;
        }
        return false;
    }
};

#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
using namespace std;

class Task;
class Scheduler;
typedef std::chrono::milliseconds MillisecondsTime;
typedef std::pair<MillisecondsTime, Task*> undoTask;

class Task{
private:
    Scheduler *s;
    MillisecondsTime waitTime;
    void addSelf(MillisecondsTime t);
public:
    
    Task(Scheduler *scheduler, MillisecondsTime interval){
        this->s = scheduler;
        this->waitTime = interval;
    }
    
    void doTask(){
        std::cout << "Hello, world: " << std::endl;
        addSelf(waitTime);
    }
};

class Scheduler{
private:
    struct compare{
        bool operator()(undoTask& a, undoTask& b){
            return a.first > b.first;
        }
    };
    
    std::priority_queue<undoTask, std::vector<undoTask>, compare> scheduleList;
    
public:
    void addTask(MillisecondsTime time, Task *a){
        MillisecondsTime currentTime = std::chrono::duration_cast<MillisecondsTime>(std::chrono::system_clock::now().time_since_epoch());
        undoTask p = make_pair(currentTime + time, a);
        scheduleList.push(p);
    }
    
    void runTasks(){
        while(!scheduleList.empty()){
            auto t = scheduleList.top();
            scheduleList.pop();
            MillisecondsTime currentTime = std::chrono::duration_cast<MillisecondsTime>(std::chrono::system_clock::now().time_since_epoch());
            // pthread_t task_thread;
            // int pid = pthread_create(&task_thread, NULL, t.second->doTask(), (void *)i);
            // std::thread tt(&Scheduler::threadRunTask, t.second);
            if(currentTime >= t.first)
                t.second->doTask();
            else{
                MillisecondsTime waitTime = t.first - currentTime;
                std::this_thread::sleep_for(waitTime);
                std::cout << "wait time: " << waitTime.count() << std::endl;
                t.second->doTask();
            }
        }
    }
    
    void threadRunTask(Task *t){
        t->doTask();
    }
};

void Task::addSelf(MillisecondsTime t){
    this->s->addTask(t, this);
}

int main(int argc, const char * argv[]) {
    
    Scheduler *scheduler = new Scheduler();
    
    Task *t1 = new Task(scheduler, MillisecondsTime(1000));
    Task *t2 = new Task(scheduler, MillisecondsTime(1000));
    
    scheduler->addTask(MillisecondsTime(5000), t1);
    scheduler->addTask(MillisecondsTime(2000), t2);
    
    scheduler->runTasks();
    
    return 0;
}

class LRUCache{
private:
    int capacity;
    list<int> history;
    unordered_map<int, pair<int, list<int>::iterator>> cache;
    
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        auto it = cache.find(key);
        if(it != cache.end()){
            update(it);
            return it->second.first;
        }
        return -1;
    }
    
    void set(int key, int value) {
        auto it = cache.find(key);
        if(it != cache.end())
            update(it);
        else{
            if(cache.size() == capacity){
                cache.erase(history.back());
                history.pop_back();
            }
            history.push_front(key);
        }
        cache[key] = make_pair(value, history.begin());
    }
    
    void update(unordered_map<int, pair<int, list<int>::iterator>>::iterator it){
        int key = it->first;
        auto p = it->second.second;
        history.erase(p);
        history.push_front(key);
        it->second.second = history.begin();
    }
};

unordered_map<string, vector<string>> m;

    vector<string> combine(string word, vector<string> prev){
        for(int i=0;i<prev.size();++i){
            prev[i]+=" "+word;
        }
        return prev;
    }

public:
    vector<string> wordBreak(string s, unordered_set<string>& dict) {
        if(m.count(s)) return m[s]; //take from memory
        vector<string> result;
        if(dict.count(s)){ //a whole string is a word
            result.push_back(s);
        }
        for(int i=1;i<s.size();++i){
            string word=s.substr(i);
            if(dict.count(word)){
                string rem=s.substr(0,i);
                vector<string> prev=combine(word,wordBreak(rem,dict));
                result.insert(result.end(),prev.begin(), prev.end());
            }
        }
        m[s]=result; //memorize
        return result;
    }
    
    int trap(vector<int>& height) {
        int ret = 0, l = 0, r = 0;
        int p = 0, q = height.size() - 1;
        while(p <= q){
            if(l <= r){
                if(height[p] >= l)
                    l = height[p];
                else
                    ret += l - height[p];
                p++;
            }else{
                if(height[q] >= r)
                    r = height[q];
                else
                    ret += r - height[q];
                q--;
            }
        }
        return ret;
    }
    
     string alienOrder(vector<string>& words) {
        unordered_map<char, set<char>> dict;
        unordered_map<char, int> nums;
        string ret = "", s = "";
        for(auto word : words){
            for(auto c : word)
                if(!nums.count(c))
                    nums[c] = 0;
            for(int i = 0; i < min(s.length(), word.length()); i++){
                if(s[i] != word[i] && !dict[s[i]].count(word[i])){
                    dict[s[i]].insert(word[i]);
                    nums[word[i]]++;
                    break;
                }
            }
            s = word;
        }
        queue<char> q;
        for(auto it : nums)
            if(it.second == 0)
                q.push(it.first);
        while(!q.empty()){
            char prev = q.front();
            q.pop();
            ret += prev;
            for(auto c : dict[prev])
                if(nums[c]-- == 1)
                    q.push(c);
        }
        return ret.length() == nums.size() ? ret : "";
    }

vector<int> findIntersection_I(vector<int>& nums1, vector<int>& nums2){
        vector<int> ret;
        unordered_set<int> rec;
        for(auto n : nums1)
            rec.insert(n);
        for(auto n : nums2){
            if(rec.count(n)){
                ret.push_back(n);
                rec.erase(n);
            }
        }
        return ret;
    }
    
    vector<int> findIntersection_II(vector<int>& nums1, vector<int>& nums2){
        vector<int> ret;
        int start = 0, end = nums2.size() - 1;
        for(auto n : nums1){
            int index = binary_search(nums2, start, end, n);
            if(index != -1)
                ret.push_back(n);
            if(start > end)
                break;
        }
        return ret;
    }
    
    int binary_search(vector<int>& nums, int& start, int end, int target){
        while(start <= end){
            int mid = start + (end - start) / 2;
            if(nums[mid] < target)
                start = mid + 1;
            else if(nums[mid] > target)
                end = mid - 1;
            else
                return mid;
        }
        return -1;
    }
