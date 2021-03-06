#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#define LL long long
using namespace std;
using Skills = vector<pair<int, int>>;

void PrintPairs(const Skills &pairs)
{
    for (auto pair : pairs)
    {
        cout << pair.first << ", ";
        // cout << '(' << pair.first << ", " << pair.second << "), ";
    }
    cout << endl;
}

void PrintVec(const vector<LL> &vec)
{
    for (auto v : vec)
    {
        cout << v << ", ";
        // cout << '(' << pair.first << ", " << pair.second << "), ";
    }
    cout << endl;
}

int MinOptUB(const Skills &a, const vector<LL> &mincost, int l, int r, LL m)
{
    int ub = (l + r) / 2;

    // ub = 5 -> l = 6 -> ub = 8 -> r = 8 -> ub = 7 -> r = 7
    // -> ub = 6 -> r = 6 (l = 6) ->

    // l = 6, r = 9 -> ub = 7 -> l = 7 -> ub = 8 -> l = 8 -> l = 9
    while (l < r) {
        if (m >= mincost[ub])
            l = ub + 1;
        else
            r = ub;
        ub = (l + r) / 2;
    }
    return ub - 1;
}

int main()
{
    int n, x, A, B;
    LL m, sum = 0, S = 0;

    cin >> n >> x >> A >> B >> m;
    Skills a(n + 1), sol(n + 1);
    vector<LL> mincost(n + 1);

    // Prep
    for (int i = 1; i <= n; i++)
    {
        int buf;
        cin >> buf;
        a[i] = {buf, i};
    }
    sort(a.begin(), a.end());
    for (int i = 1; i <= n; i++) {
        sum += a[i].first;
        mincost[i] = a[i].first * (LL)i - sum;
    }

    // cout << "a: ";
    // PrintPairs(a);
    // cout << "mincost: ";
    // PrintVec(mincost);

    // Real Shit
    for (int i = 0; i <= n; i++)
    {
        // cout << "\niteration " << i + 1 << ":\n";
        if (i > 0)
        {
            if (m < x - a[n - i + 1].first)
                break;
            int diff = x - a[n - i + 1].first;
            m -= diff;
            a[n - i + 1].first = x;
            mincost.pop_back();
        }
        // cout << "a: ";
        // PrintPairs(a);
        // cout << "mincost: ";
        // PrintVec(mincost);
        // cout << "remaining m: " << m << endl;

        int ub = MinOptUB(a, mincost, 0, n - i, m);
        // cout << "upperbound: " << ub << endl;
        LL m_tmp = m - mincost[ub];
        int min = a[ub].first + (m_tmp / ub);
        LL S_tmp = (LL)A * i + (LL)B * min; // LL
        if (S < S_tmp) {
            // cout << "S is updated!!!\n";
            S = S_tmp;
            sol = a;
            for (int j = 1; j <= ub; j++)
                sol[j].first = min;
        }
        // cout << "S = " << S << endl;

        // cout << "sol: ";
        // PrintPairs(sol);
    }

    sort(sol.begin(), sol.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.second < b.second; });

    cout << S << endl;
    for (int i = 1; i < n; i++)
        cout << sol[i].first << ' ';
    cout << sol[n].first << endl;

    return 0;
}