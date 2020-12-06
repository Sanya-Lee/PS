#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double MPI = 3.141592653589793238462643383279502884;

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
typedef complex<double> base;
 
void fft(vector <base> &a, bool invert)
{
    int n = sz(a);
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(a[i],a[j]);
    }
    for (int len=2;len<=n;len<<=1){
        double ang = 2*MPI/len*(invert?-1:1);
        base wlen(cos(ang),sin(ang));
        for (int i=0;i<n;i+=len){
            base w(1);
            for (int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (invert){
        for (int i=0;i<n;i++) a[i] /= n;
    }
}
 
void multiply(const vector<ll> &a,const vector<ll> &b,vector<ll> &res)
{
    vector <base> fa(all(a)), fb(all(b));
    int n = 1;
    while (n < max(sz(a),sz(b))) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false); fft(fb,false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa,true);
    res.resize(n);
    for (int i=0;i<n;i++) res[i] = ll(round(fa[i].real()));
}

vector<ll> a(131072), b(131072), res, chk;
const ll sft = 30005;
ll ans;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n;
    for (int i=0; i<n; i++){
        int t; cin >> t;
        a[t+sft]++;
    }   
    cin >> m;
    chk.resize(m);
    for (int i=0; i<m; i++){
        cin >> chk[i];
        chk[i] *= 2;
        chk[i] += sft*2;
    }
    cin >> k;
    for (int i=0; i<k; i++){
        int t; cin >> t; b[t+sft]++;
    }
    multiply(a, b, res);
    for (int i : chk) ans += res[i];
    cout << ans << endl;
}