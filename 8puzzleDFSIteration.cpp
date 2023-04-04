#include <bits/stdc++.h>
using namespace std;

struct puzzle
{
    vector<vector<int>> grid;
    int x, y;
    string ans;
    long long s;
};

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

bool dfs(vector<vector<int>> gridinit)
{
    stack<puzzle> s;
    int n = gridinit.size();
    int m = gridinit[0].size();
    int x, y;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            x = i;
            y = j;
        }
    }
    unordered_map<string, bool> vis;
    vis[hashstr(gridinit)] = true;
    puzzle start = {gridinit, x, y, "", 0};
    s.push(start);
    int delrow[4] = {-1, 0, 1, 0};
    int delcol[4] = {0, 1, 0, -1};
    char dir[4] = {'U', 'R', 'D', 'L'};
    while (!s.empty())
    {
        puzzle curr = s.top();
        s.pop();
        curr.s++;
        string h = hashstr(curr.grid);
        if (h == "123456780")
        {
            cout << "FOUND" << endl;
            cout << "No of steps = " << curr.s << endl;
            cout << curr.ans << endl;
            return true;
        }
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
                swap(next.grid[curr.x][curr.y], next.grid[nrow][ncol]);
                next.ans += dir[i];
                string h = hashstr(next.grid);
                // if the current state is not visited put it in queue
                if (!vis[h])
                {
                    vis[h] = true;
                    s.push(next);
                }
            }
        }
    }
    return false;
}
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

int main()
{

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
    if (!solvable(gridinit))
    {
        cout << "Puzzle is not solvable" << endl;
        return 0;
    }
    dfs(gridinit);
    return 0;
}