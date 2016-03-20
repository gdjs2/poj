#include <cstdio>

typedef long long ll;

ll x, y, m, n, L;
ll a, b, gcd, t, ans = 0;

ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if(!b)
    { x = 1; y = 0; return a; }
    ll g = exgcd(b, a%b, x, y);
    ll t = x; x = y; y = t - a/b*y;
    return g;
}

int main()
{
    scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &L);
    gcd = exgcd(n-m, L, a, b);
    if((x-y)%gcd)
    { printf("Impossible\n"); return 0; }
    a *= (x-y)/gcd;// b *= gcd/(x-y);
    t = -a * gcd/L;
    ans = a + L/gcd*t;
    while(ans < 0) ans += L/gcd;
    printf("%lld\n", ans);
    return 0;
}
