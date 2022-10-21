#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 100
#define MAXL 100

struct Node {
    int i;
    ll freq;
    Node* left, * right;
    
    Node(int i, ll freq): freq(freq), i(i), left(NULL), right(NULL) {}
};
bool freq_cmp(Node* lhs, Node* rhs)
{
    return lhs->freq >= rhs->freq;
}

void traverse_tree(Node* root, char code[MAXN][MAXL], char path[MAXL], int l, int N)
{
    if(!root)   return;
    if(root->i < N) {
        strcpy(code[root->i], path);
    }
    path[l] = '0';
    traverse_tree(root->left, code, path, l + 1, N);
    path[l] = '1';
    traverse_tree(root->right, code, path, l + 1, N);
    path[l] = '\0';
}

void huffman_code(ll freq[], int N, char code[MAXN][MAXL])
{
    Node* nds[MAXN] = {0};
    pair<Node*, Node*> merge_pair;
    for(int n = 0; n < N; n++)
        nds[n] = new Node(n, freq[n]);
    for(int n = N; n > 1; n--) {
        sort(nds, nds+n, freq_cmp);

        //debug
        if(nds[n - 1] == NULL || nds[n - 2] == NULL) {
            cout << "NULL error\n";
            return;
        }

        merge_pair = make_pair(nds[n - 1], nds[n - 2]);
        ll newfreq = nds[n - 1]->freq + nds[n - 2]->freq;
        nds[n - 1] = NULL;
        nds[n - 2] = new Node(N, newfreq);
        nds[n - 2]->left = merge_pair.first;
        nds[n - 2]->right = merge_pair.second;
    }

    char path[MAXL] = {};
    traverse_tree(nds[0], code, path, 0, N);
}

int main()
{
    int N;
    cin >> N;
    ll freq[MAXN];
    for(int n = 0; n < N; n++)
        cin >> freq[n];
    char code[MAXN][MAXL] = {};
    huffman_code(freq, N, code);
    for(int n = 0; n < N; n++) {
        printf("%s\n", code[n]);
    }
    return 0;
}