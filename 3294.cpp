#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int read()
{
    int x = 0, k = 1; char c = getchar();
    while(c < '0' || c > '9') k = c == '-' ? -1 : 1, c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * k;
}

const int Maxn = 1001;
int n, len = -1, k, hi[Maxn * 104], time[Maxn * 104], c[400];
int sa[Maxn * 104], rank[Maxn * 104], tmp[Maxn * 104], t[Maxn * 104], t2[Maxn * 104];
char s[Maxn], str[Maxn * 104];
bool flg[104], enter = false;

bool cmp(int a, int b)
{
    if(rank[a] != rank[b]) return rank[a] < rank[b];
    int ra = a + k < len ? rank[a+k] : -1;
    int rb = b + k < len ? rank[b+k] : -1;
    return ra < rb;
}

void getsa()
{
    for(int i = 0; i < len; ++i) sa[i] = i, rank[i] = str[i];

    bool flg = 0;
    for(k = 1; k <= len; k <<= 1)
    {
        sort(sa, sa+len, cmp);

        tmp[sa[0]] = 0;
        for(int i = 1; i < len; ++i)
            tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i]) ?  1 : flg = 0);
        for(int i = 0; i < len; ++i) rank[i] = tmp[i];
        if(flg) break;
    }
    return ;
}

// void getsa()
// {
//     memset(c, 0, sizeof(c));
//     memset(t2, 0, sizeof(t2));
//     int i, *x = rank, *y = t2, m = 'z' + n, n = len;
//     char *s = str;
//     for (i = 0; i < m; i++) c[i] = 0;
//     for (i = 0; i < n; i++) c[x[i] = s[i]]++;
//     for (i = 1; i < m; i++) c[i] += c[i - 1];
//     for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
//     for (int k = 1; k <= n; k <<= 1)
//     {
//         int p = 0;
//         for (i = n - k; i < n; i++) y[p++] = i;
//         for (i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
//         for (i = 0; i < m; i++) c[i] = 0;
//         for (i = 0; i < n; i++) c[x[y[i]]]++;
//         for (i = 0; i < m; i++) c[i] += c[i - 1];
//         for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
//         swap(x, y);
//         p = 1; x[sa[0]] = 0;
//         for (i = 1; i < n; i++)
//         x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
//         if (p >= n) break;
//         m = p;
//     }
// }


void gethi()
{
    int k = 0;
    for(int i = 0; i < len; ++i) rank[sa[i]] = i;
    for(int i = 1; i < len; ++i)
    {
        if(k) --k;
        int j = sa[rank[i]-1];
        while(str[i+k] == str[j+k]) ++k;
        hi[i] = k;
    }
    return;
}

int main()
{
    freopen("11107.in", "r", stdin);
    freopen("11107.out", "w", stdout);
    while((n = read()) != 0)
    {
        if(enter) puts("");
        enter = true;
        for(int i = 1; i <= n; ++i)
        {
            scanf("%s", s);
            int slen = strlen(s);
            for(int j = 0; j < slen; ++j) str[++len] = s[j], time[len] = i;
            str[++len] = i + 'z';
        }

        getsa();
        gethi();
        // for(int i = 0; i < len; ++i)
        //     printf("%s hi = %d, time = %d\n", str+sa[i], hi[sa[i]], time[sa[i]]);

        int l = 0, r = len, p;
        while(l < r)
        {
            int mid = ((l+r) >> 1) + 1, k = 0, lp, maxn = 0;
            memset(flg, 0, sizeof(flg));

            for(int i = 0; i < len; ++i)
            if(hi[sa[i]] < mid)
            {
                for(int j = 1; j <= n; ++j) k += flg[j];
                memset(flg, 0, sizeof(flg));
                flg[time[sa[i]]] = true;
                if(k > maxn) maxn = k;
                k = 0;
            }
            else flg[time[sa[i]]] = true;

            if(maxn > n/2) l = mid;
            else r = mid - 1;
        }
        // printf("%d\n", l);
        if(!l) { printf("?\n"); continue; }

        int k = 0;
        for(int i = 0; i < len; ++i)
        {
            if(hi[sa[i]] < l)
            {
                for(int j = 1; j <= n; ++j) k += flg[j];
                memset(flg, 0, sizeof(flg));
                flg[time[sa[i]]] = true;
                if(k > n/2)
                {
                    for(int j = 0; j < l; ++j) printf("%c", str[sa[i-1]+j]);
                    printf("\n");
                }
                k = 0;
            }
            else flg[time[sa[i]]] = true;
        }

        memset(str, 0, sizeof(str));
        memset(sa, 0, sizeof(sa));
        memset(rank, 0, sizeof(rank));
        len = -1;
        // printf("%s\n", str);
        // for(int i = 0; i < len; ++i) printf("%d ", rank[i]);
        // for(int i = 0; i < len; ++i) printf("%d ", sa[i]);
    }
    return 0;
}
