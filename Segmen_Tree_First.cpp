#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define LL long long
#define el "\n"
#define nl cout << "\n";
#define stp setprecision
#define fixed_stp fixed << setprecision
#define vec_print(v) for  (auto itr : v) cout << itr << " "; nl;
#define fio ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
#define pi 2 * acos(0.0)
ll const Mod = 1e18;
const ll N = 1000000000 + 7;
vector <int> v; 
vector <int> segment_tree(100);

void build(int node, int left, int right) 
{
    if(left == right) {
        segment_tree[node] = v[left];
        return;
    }
    
    int mid = (left + right) / 2;
    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    segment_tree[node] = segment_tree[2*node] + segment_tree[2*node + 1];
    return;
}

int query(int node, int begin, int end, int i, int j) {
    // tree er baire chole gese
    if(i > end || j < begin) return 0; 
    // relevant sengment ey ase
    if(begin >= i && end <= j) return segment_tree[node];
    // aro vange te hobe
    
    int mid = (begin + end) / 2;
    int left = 2 * node;
    int right = 2 * node + 1;
    int q1 = query(left, begin, mid, i, j);
    int q2 = query(right, mid + 1, end, i, j);
    return q1 + q2;
}

void update(int node, int begin, int end, int i, int newvalue) {
    if(i > end || i < begin) return;
    if(begin >= i && end <= i ) {
        segment_tree[node] = newvalue;
        return;
    }
    
    int mid = (begin + end) / 2;
    int left = 2 * node;
    int right = 2 * node + 1;
    update(left, begin, mid, i,newvalue);
    update(right, mid+1, end, i,newvalue);

    segment_tree[node] = newvalue;
    return;
}
int main()
{
    fio;
    int t = 1;
    cin >> t;
    while (t--)
    {
        int n; cin >> n;
        v.clear();
        v.resize(n+1);
        for(auto &i : v) cin >> i;
        v.insert(v.begin(), 0);
        build(1, 1, n);
        int x = 1, y = 1;
        for(int i = 1; i < 16; i++) {
            if(y % x == 0) {
                nl;
                x *= 2;
            } y++;
            // cout << "node " << i << " = " << segment_tree[i] << " ";
            cout << segment_tree[i] << " ";
        }
        nl;
        cout << query(1 , 1, n, 3, 5) << el;
        update(1, 1, n, 5, 10);
        x = 1, y =1;
         for(int i = 1; i < 16; i++) {
            if(y % x == 0) {
                nl;
                x *= 2;
            } y++;
            // cout << "node " << i << " = " << segment_tree[i] << " ";
            cout << segment_tree[i] << " ";
        }
        nl;
        cout << query(1 , 1, n, 3, 5) << el;
    }
    return 0;
}