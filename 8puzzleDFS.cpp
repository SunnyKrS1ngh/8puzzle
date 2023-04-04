#include <bits/stdc++.h>
using namespace std;

// structure of puzzle
struct puzzle
{
    vector<vector<int>> grid;
    int x, y;
    string ans;
    long long s;
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

// applying dfs. Maintaining an unordered map - vis which keeps track of states which are visited
bool dfs(puzzle curr, unordered_map<string, bool> &vis, long long states)
{
    int n = curr.grid.size();
    int m = curr.grid[0].size();
    states++;

    // checking whether the solution has arrived.
    // This is the target state.
    string hash = hashstr(curr.grid);
    if (hash == "123456780")
    {
        cout << "FOUND" << endl;
        cout << curr.ans << endl;
        cout << states << endl;
        return true;
    }

    int delrow[4] = {-1, 0, 1, 0};
    int delcol[4] = {0, 1, 0, -1};
    char dir[4] = {'U', 'R', 'D', 'L'};
    for (int i = 0; i < 4; i++)
    {
        // checking neighbouring tiles
        int nrow = curr.x + delrow[i];
        int ncol = curr.y + delcol[i];
        // checking if neighbouring tiles are not out of range
        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m)
        {
            puzzle next = curr;
            next.x = nrow;
            next.y = ncol;
            cout << next.s << " " << next.ans << endl;
            next.s++;
            // swapping the neighbouring tile with current tile
            swap(next.grid[curr.x][curr.y], next.grid[nrow][ncol]);
            next.ans += dir[i];
            string h = hashstr(next.grid);
            // if the current state is not visited perform dfs on it.
            if (!vis[h])
            {
                vis[h] = true;
                if (dfs(next, vis, states))
                {
                    return true;
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
    // this is the initial state.
    // vector<vector<int>> gridinit{{3, 2, 1}, {4, 5, 6}, {8, 7, 0}};
    vector<vector<int>> gridinit(3, vector<int>(3, 0));
    cout << "Enter the matrix" << endl;
    // NOTE : Enter blank as 0
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

    int x, y;
    // code to find the location of blank tile
    for (int i = 0; i < gridinit.size(); i++)
    {
        for (int j = 0; j < gridinit[0].size(); j++)
        {
            if (gridinit[i][j] == 0)
            {
                x = i;
                y = j;
                break;
            }
        }
    }
    long long states = 0;
    // maintaing a visited array that keeps track of visited states.
    unordered_map<string, bool> vis;
    string h = hashstr(gridinit);
    vis[h] = true;
    puzzle start = {gridinit, x, y, ""};
    // performing dfs from intitial state.
    dfs(start, vis, states);
    return 0;
}
