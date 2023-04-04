#include <bits/stdc++.h>
using namespace std;

// structure of puzzle
struct puzzle
{
    vector<vector<int>> puzzle;
    int x, y;
    string ans;
    int steps;
};

// the hashstr function here converts the matrix to linear string
// here the whole array has been converted to linear string which helps to check visited states easily instead of storing the whole grid as a 2d matrix
string hashstr(vector<vector<int>> curr)
{
    string hash;
    for (int i = 0; i < curr.size(); i++)
    {
        for (int j = 0; j < curr[0].size(); j++)
        {
            hash += to_string(curr[i][j]);
        }
    }
    return hash;
}

// Here bfs is applied.
void bfs(vector<vector<int>> grid)
{
    queue<puzzle> q;
    // Maintaining an unordered map - vis which keeps track of states which are visited
    unordered_map<string, bool> vis;

    int x, y;
    int n = grid.size();
    int m = grid[0].size();
    // finding the location of blank tile
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 0)
            {
                x = i;
                y = j;
                break;
            }
        }
    }

    puzzle start = {grid, x, y, "", 0};
    // pushing the initial state in queue
    q.push(start);
    vis[hashstr(grid)] = true;
    int delrow[4] = {0, -1, 0, 1};
    int delcol[4] = {-1, 0, 1, 0};
    char dir[4] = {'L', 'U', 'R', 'D'};
    long long states = 0;
    while (!q.empty())
    {
        // taking out the element in front of queue.
        puzzle curr = q.front();
        q.pop();
        vector<vector<int>> temp = curr.puzzle;

        // checking if the target state is reached
        if (hashstr(temp) == "123456780")
        {
            cout << "FOUND" << endl;
            cout << curr.ans << endl;
            cout << "States explored = " << states << endl;
            cout << "No. of steps = " << curr.steps << endl;
            return;
        }
        curr.steps++;
        // checking all the neighbouring tiles U,D,L,R
        for (int i = 0; i < 4; i++)
        {
            int nrow = curr.x + delrow[i];
            int ncol = curr.y + delcol[i];
            // only tiles which are in range will be considered.
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m)
            {
                puzzle next = curr;
                next.x = nrow;
                next.y = ncol;
                // swap the current blank posn with neighbouring tile
                swap(next.puzzle[curr.x][curr.y], next.puzzle[nrow][ncol]);
                next.ans += dir[i];
                string h = hashstr(next.puzzle);
                // if the current state is not visited put it in queue
                if (!vis[h])
                {
                    states++;

                    vis[h] = true;
                    q.push(next);
                }
            }
        }
    }
    cout << "NOT FOUND" << endl;
    cout << "No. of states visited : " << vis.size() << endl;
}

// Function to check whether the puzzle is solvable or not by no. of inversions method
bool solvable(vector<vector<int>> grid)
{
    vector<int> flat;

    int inverse = 0;
    // flattening the grid
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {

            flat.push_back(grid[i][j]);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (flat[i] != 0 && flat[j] != 0 && flat[i] > flat[j])
            {
                inverse++;
            }
        }
    }
    // if no of inversions is odd -> not solvable else solvable
    if (inverse % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int man(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int manh(vector<vector<int>> grid)
{
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int x, y;
            int val = grid[i][j];
            if (val == 0)
            {
                continue;
            }
            x = (val - 1) / 3;
            y = (val - 1) % 3;
            sum += man(i, j, x, y);
        }
    }
    return sum;
}

int main()
{
    // This is the initial state.
    // vector<vector<int>> gridinit{{3, 2, 1}, {4, 5, 6}, {8, 7, 0}};
    vector<vector<int>> gridinit(3, vector<int>(3, 0));
    cout << "Enter the initial state: " << endl;
    // NOTE: Enter blank as 0

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> gridinit[i][j];
        }
    }
    cout << manh(gridinit) << endl;
    // if (!solvable(gridinit))
    // {
    //     cout << "Puzzle is not solvable" << endl;
    //     return 0;
    // }

    // bfs(gridinit);

    return 0;
}