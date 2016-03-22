#include <cstdio>

typedef long long ll;

const int mod = 9901;
const int Maxn = 10010;
ll prime[1240], num[1240];
ll A, B, ans = 1;
bool vis[Maxn];

ll q_m (ll a, ll b, ll m)
{
    ll ret = 0; a %= m;
    while(b)
    {
        if(b&1) ret += a;
        ret %= m;
        b >>= 1; a <<= 1;
    }
    return ret;
}

void get_prime()
{
    for(int i = 2; i <= Maxn; ++i)
    {
        if(!vis[i]) prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0] && i * prime[j] <= Maxn; ++j)
        {
            vis[i*prime[j]] = true;
            if(i % prime[j] == 0) break;
        }
    }
    return;
}

ll q_pow(ll a, ll k, ll m = mod)
{
    if(!k) return 1;
    ll p = q_pow(a, k/2, m) % m;
    return (k&1) ? q_m(q_m(p, p, m), a, m)%m : q_m(p, p, m)%m;
}

int main()
{
    get_prime();
    scanf("%lld %lld", &A, &B);
    for(int i = 1; prime[i] * prime[i] <= A, i <= prime[0]; ++i)
    {
        while(A % prime[i] == 0)
        { ++num[i]; A /= prime[i]; }
        if(!num[i]) continue;
        if( (prime[i]-1) % 9901 == 0 ) ans *= ((q_pow(prime[i], num[i]*B+1, mod*(prime[i]-1))) / (prime[i] - 1)) % mod;
        else ans *= ( (q_pow(prime[i], num[i]*B+1)-1) * (q_pow(prime[i]-1, mod-2)) ) % mod;
        ans %= mod;
    }
    if(A > 1)
    {
        if( (A-1) % mod == 0) ans *= ((q_pow(A, B+1, mod*(A-1))) / (A-1)) % mod;
        else ans *= ( (q_pow(A, B+1)-1) * (q_pow(A-1, mod-2))) % mod;
        ans %= mod;
    }
    printf("%lld\n", (ans+mod) % mod);
    return 0;
}
