#include <cstdio>

const int oo = 0x3f3f3f3f;
int a, b, c, ans = oo, anx, any;

bool input()
{
    scanf("%d %d %d", &a, &b, &c);
    if(c == 0) return false;
}

void swap(int& a, int& b)
{
    a ^= b; b ^= a; a ^= b;
    return;
}

int exgcd(int a, int b, int& x, int& y)
{
    if(!b)
    {
        x = 1; y = 0;
        return a;
    }
    int ret = exgcd(b, a%b, x, y);
    int t = x; x = y; y = t - a/b*y;
    return ret;
}

int abs(int x) { return x < 0 ? -x : x; }


void solve()
{
    bool flg = false;
    ans = oo;
    if(a < b) swap(a, b), flg = true;
    int x, y, gcd = exgcd(a, b, x, y);
    x *= c / gcd;
    y *= c / gcd;
    int t = y * gcd / a;
    for(int i = t-1; i <= t+1; ++i)
    {
        if(abs(x + b/gcd*i) + abs(y - a/gcd*i) < ans)
        {
            ans = abs(x + b/gcd*i) + abs(y - a/gcd*i);
            anx = abs(x + b/gcd*i); any = abs(y - a/gcd*i);
        }
    }
    if(flg) printf("%d %d\n", any, anx);
    else printf("%d %d\n", anx, any);
    return;
}

int main()
{
    freopen("2142.in", "r", stdin);
    while(input()) solve();
    return 0;
}
