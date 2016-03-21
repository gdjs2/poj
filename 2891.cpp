#include <cstdio>

typedef long long ll;
ll n, a, c, b;
ll x, y, c1;

ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if(!b)
    { x = 1; y = 0; return a; }
    ll ret = exgcd(b, a%b, x, y);
    ll t = x; x = y; y = t - a/b*y;
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("2891.in", "r", stdin);
#endif
    while(scanf("%lld", &n) != EOF)
    {
        bool flg = false;
        scanf("%lld %lld", &a, &c);
        if(n == 1)
        { printf("%lld\n", a+c); continue; }
        for(int i = 1; i < n; ++i)
        {
            scanf("%lld %lld", &b, &c1);
            if(flg) continue;
            ll gcd = exgcd(a, b, x, y);
            if((c1 - c) % gcd)
            { printf("-1\n"); flg = true; continue;}
            x = x * (c1-c)/gcd;
            // printf("%lld %lld\n", x, y);
            int x0 = x - x*gcd/b*b/gcd;
            if(x0 < 0) x0 += b/gcd;
            c = a*x0 + c;
            a = a * b / gcd;
        }
        if(!flg) printf("%lld\n", c);
    }
    return 0;
}
