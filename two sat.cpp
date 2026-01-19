//#pragma GCC optimize("Ofast","unroll-loops")
#include <bits/stdc++.h>
#define ld long double
#define ll long long
//#define int long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define rep(n) for (int (i) = 0; (i) < (n); (i)++)

using namespace std;

struct TwoSat {
    vector<vector<int>> g, gr;
    vector<int> comp, order;
    vector<bool> used;
    int n;

    TwoSat(int n) : n(n) {
        g.resize(n * 2), gr.resize(n * 2);
        comp.resize(n * 2), used.resize(n * 2);
    }

private:
    void add_edge(int v, int u) {
        g[v].push_back(u);
        gr[u].push_back(v);
    }

public:
    void add_or(int v, int u) {
        add_edge(v ^ 1, u);
        add_edge(u ^ 1, v);
    }

    vector<int> get() {
        auto dfs = [&](auto &&self, int v)->void {
            used[v] = true;
            for (int u : g[v]) {
                if (!used[u])
                    self(self, u);
            }
            order.push_back(v);
        };
        for (int v = 0; v < 2 * n; v++) {
            if (!used[v])
                dfs(dfs, v);
        }
        reverse(all(order));
        auto dfs2 = [&](auto &&self, int v, int c)->void {
            comp[v] = c;
            for (int u : gr[v]) {
                if (comp[u] == 0)
                    self(self, u, c);
            }
        };
        int c = 0;
        for (int v : order) {
            if (comp[v] == 0)
                dfs2(dfs2, v, ++c);
        }
        vector<int> ans(n);
        for (int v = 0; v < 2 * n; v += 2) {
            if (comp[v] == comp[v ^ 1]) {
                fill(all(ans), -1);
                return ans;
            }
            if (comp[v] > comp[v ^ 1])
                ans[v >> 1] = 1;
        }
        return ans;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    TwoSat helper(n);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        helper.add_or(v, u);
    }
    auto ans = helper.get();
    for (int i : ans)
        cout << i << ' ';
    cout << '\n';
}

signed main() {
    //ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(20);
    solve();
}
