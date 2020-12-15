/** 
    Source: kactl
    Usage:
        add(k, m): add line kx + m to container
        query(x): find maximum of kx + m over all lines (y = kx + m) in container
    To query min, maintain another container with negative value of coefficient
    NOTE: don't call query if container is empty!
**/

struct Line {
  mutable ll k, m, p;
  bool operator< (const Line& o) const { return k < o.k; }
  bool operator< (ll x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<>> {
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if(y == end()) { x->p = inf; return false; }
    if(x->k == y->k) { x->p = (x->m > y->m) ? inf : -inf; }
    else { x->p = div(y->m - x->m, x->k - y->k); }
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while(isect(y, z)) { z = erase(z); }
    if(x != begin() && isect(--x, y)) { isect(x, y = erase(y)); }
    while((y = x) != begin() && (--x)->p >= y->p) { isect(x, erase(y)); }    
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};