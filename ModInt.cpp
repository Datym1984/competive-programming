struct modint {
    static const int mod = 1e9 + 7;
    int val;

    modint(int val=0) : val(val) {}

    friend modint operator+(modint a, modint b) {
        modint res(a.val + b.val);
        res.val -= (res.val >= modint::mod) * modint::mod;
        return res;
    }

    friend modint operator-(modint a, modint b) {
        modint res(a.val - b.val);
        res.val += (res.val < 0) * modint::mod;
        return res;
    }

    friend modint operator*(modint a, modint b) {
        return modint((ll) a.val * b.val % modint::mod);
    }

    friend istream& operator>>(istream& i, modint& a) {
        return i >> a.val;
    }

    friend ostream& operator<<(ostream& o, modint a) {
        return o << a.val;
    }

    operator int() {
        return val;
    }
};
