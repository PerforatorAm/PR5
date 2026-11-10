#include <iostream>

using namespace std;

const int M = 10000;

struct s_t {
    long long a = 0;
    long long b = 0;
    long long c = 0;
    int d = 0;
};

void a(const int x[], int y[], int z) {
    for (int w = 0; w < z; w++) {
        y[w] = x[w];
    }
}

void b(const int x[], int y) {
    for (int z = 0; z < y; z++) {
        cout << x[z] << " ";
    }
    cout << endl;
}

void c(const int x[], int y, int z) {
    for (int w = y; w <= z; w++) {
        cout << x[w] << " ";
    }
    cout << endl;
}

void d(int x[], int y, int z, s_t& w) {
    if (y != z) {
        int v = x[y];
        x[y] = x[z];
        x[z] = v;
        w.b++;
    }
}

int e(int x[], int y, int z, s_t& w) {
    int v = x[z];
    int u = y;
    for (int t = y; t < z; t++) {
        w.a++;
        if (x[t] <= v) {
            d(x, u, t, w);
            u++;
        }
    }
    d(x, u, z, w);
    return u;
}

void f(int x[], int y, int z, s_t& w, int v = 1, bool u = false) {
    while (y < z) {
        w.c++;
        if (v > w.d) {
            w.d = v;
        }
        int t = e(x, y, z, w);
        if (u) {
            cout << "Lomuto: depth=" << v
                 << ", range=[" << y << "," << z << "]"
                 << ", pivot=" << x[t]
                 << ", pivotIndex=" << t
                 << ", segment: ";
            c(x, y, z);
        }
        if (t - y < z - t) {
            f(x, y, t - 1, w, v + 1, u);
            y = t + 1;
        } else {
            f(x, t + 1, z, w, v + 1, u);
            z = t - 1;
        }
        v++;
        if (v > w.d) {
            w.d = v;
        }
    }
}

int g(int x[], int y, int z, s_t& w) {
    int v = x[y + (z - y) / 2];
    int u = y - 1;
    int t = z + 1;
    while (true) {
        do {
            u++;
            w.a++;
        } while (x[u] < v);
        do {
            t--;
            w.a++;
        } while (x[t] > v);
        if (u >= t) {
            return t;
        }
        d(x, u, t, w);
    }
}

void h(int x[], int y, int z, s_t& w, int v = 1, bool u = false) {
    if (y >= z) {
        return;
    }
    w.c++;
    if (v > w.d) {
        w.d = v;
    }
    int t = g(x, y, z, w);
    if (u) {
        cout << "Hoare: depth=" << v
             << ", range=[" << y << "," << z << "]"
             << ", boundary=" << t
             << ", segment: ";
        c(x, y, z);
    }
    h(x, y, t, w, v + 1, u);
    h(x, t + 1, z, w, v + 1, u);
}

bool i(const int x[], int y) {
    for (int z = 1; z < y; z++) {
        if (x[z - 1] > x[z]) {
            return false;
        }
    }
    return true;
}

long long j(const int x[], int y) {
    long long z = 0;
    for (int w = 0; w < y; w++) {
        z += x[w];
    }
    return z;
}

long long k(const int x[], int y) {
    long long z = 0;
    for (int w = 0; w < y; w++) {
        z += 1LL * x[w] * x[w];
    }
    return z;
}

bool l(const int x[], const int y[], int z) {
    return j(x, z) == j(y, z) && k(x, z) == k(y, z);
}

void m(const int x[], int y, const char* z, bool w, int& v, int& u) {
    int t[M];
    a(x, t, y);
    s_t s;
    if (w) {
        f(t, 0, y - 1, s);
    } else {
        h(t, 0, y - 1, s);
    }
    bool r = i(t, y) && l(x, t, y);
    cout << (w ? "Lomuto" : "Hoare")
         << " | " << z
         << " | " << (r ? "OK" : "ERROR") << endl;
    u++;
    if (r) {
        v++;
    }
}

void n(const int x[], int y, const char* z, int& w) {
    int v[M];
    a(x, v, y);
    s_t s;
    if (y == 0) {
        cout << "Lomuto partition | " << z << " | OK" << endl;
        w++;
        return;
    }
    int u = e(v, 0, y - 1, s);
    bool t = u >= 0 && u < y;
    for (int r = 0; r < u; r++) {
        if (v[r] > v[u]) {
            t = false;
        }
    }
    for (int r = u + 1; r < y; r++) {
        if (v[r] <= v[u]) {
            t = false;
        }
    }
    cout << "Lomuto partition | " << z << " | " << (t ? "OK" : "ERROR") << endl;
    if (t) {
        w++;
    }
}

void o(const int x[], int y, const char* z, int& w) {
    int v[M];
    a(x, v, y);
    s_t s;
    if (y < 2) {
        cout << "Hoare partition | " << z << " | OK" << endl;
        w++;
        return;
    }
    int u = g(v, 0, y - 1, s);
    bool t = u >= 0 && u < y - 1;
    for (int r = 0; r <= u; r++) {
        for (int q = u + 1; q < y; q++) {
            if (v[r] > v[q]) {
                t = false;
            }
        }
    }
    cout << "Hoare partition | " << z << " | " << (t ? "OK" : "ERROR") << endl;
    if (t) {
        w++;
    }
}

void p() {
    cout << "=== AUTOMATED SORT TESTS ===" << endl;
    const int a1[] = { 7 };
    const int a2[] = { 1, 2 };
    const int a3[] = { 2, 1 };
    const int a4[] = { 1, 2, 3, 4, 5 };
    const int a5[] = { 5, 4, 3, 2, 1 };
    const int a6[] = { 4, 1, 5, 2, 3 };
    const int a7[] = { 3, 1, 3, 2, 1 };
    const int a8[] = { 0, -5, 8, -2, 4 };
    const int a9[] = { 6, 6, 6, 6 };
    const int a10[] = { 9, -1, 9, 0, -1, 5 };
    const int a11[] = { 3, 2, 1, 4, 5 };
    const int a12[] = { 10, 0, -10, 5 };
    const int a13[] = { 2, 2, 1, 3, 1, 2 };

    const int* x[] = {
        nullptr, a1, a2, a3, a4, a5, a6,
        a7, a8, a9, a10, a11, a12, a13
    };
    const int y[] = {
        0, 1, 2, 2, 5, 5, 5,
        5, 5, 4, 6, 5, 4, 6
    };
    const char* z[] = {
        "empty", "one element", "two sorted",
        "two reversed", "ascending", "descending",
        "mixed", "duplicates", "negative values",
        "all equal", "combined", "partly sorted",
        "own test 1", "own test 2"
    };

    int w = 0;
    int v = 0;
    for (int u = 0; u < 14; u++) {
        m(x[u], y[u], z[u], true, w, v);
        m(x[u], y[u], z[u], false, w, v);
    }
    cout << "Sort tests: " << w << "/" << v << endl;

    cout << "\n=== PARTITION TESTS ===" << endl;
    int t = 0;
    n(a3, 2, "two reversed", t);
    n(a4, 5, "ascending", t);
    n(a5, 5, "descending", t);
    n(a9, 4, "all equal", t);

    o(a3, 2, "two reversed", t);
    o(a4, 5, "ascending", t);
    o(a5, 5, "descending", t);
    o(a9, 4, "all equal", t);

    cout << "Partition tests: " << t << "/8" << endl;
}

void q(const char* x, const s_t& y) {
    cout << x
         << ": comparisons=" << y.a
         << ", swaps=" << y.b
         << ", calls=" << y.c
         << ", maxDepth=" << y.d << endl;
}

void r() {
    cout << "\n=== TRACE DEMO ===" << endl;
    int x[] = { 9, 3, 7, 1, 8, 2, 6, 4 };
    int y[8];

    a(x, y, 8);
    s_t l1;
    cout << "-- Lomuto --" << endl;
    f(y, 0, 7, l1, 1, true);
    cout << "Sorted: ";
    b(y, 8);
    q("Lomuto", l1);

    a(x, y, 8);
    s_t h1;
    cout << "-- Hoare --" << endl;
    h(y, 0, 7, h1, 1, true);
    cout << "Sorted: ";
    b(y, 8);
    q("Hoare", h1);
}

void s() {
    cout << "\n=== VARIANT 5 ===" << endl;
    int x[] = { 23, 2, 28, 11, 6, 31, 9, 19, 4, 26, 14, 7, 30, 1, 17 };
    const int y = 15;
    int z[15];
    s_t l1, h1;

    cout << "Initial: ";
    b(x, y);

    a(x, z, y);
    f(z, 0, y - 1, l1);
    cout << "Lomuto sorted: ";
    b(z, y);
    q("Lomuto", l1);

    a(x, z, y);
    h(z, 0, y - 1, h1);
    cout << "Hoare sorted: ";
    b(z, y);
    q("Hoare", h1);
}

void t(int x[], int y, int z) {
    for (int w = 0; w < y; w++) {
        if (z == 0) {
            x[w] = w;
        } else if (z == 1) {
            x[w] = y - w;
        } else if (z == 2) {
            x[w] = (w * 37LL) % y;
        } else {
            x[w] = w % 5;
        }
    }
}

void u() {
    cout << "\n=== EXPERIMENT ===" << endl;
    const int x[] = { 100, 1000, 10000 };
    const char* y[] = { "ascending", "descending", "mixed", "duplicates" };
    cout << "n,type,algorithm,comparisons,swaps,calls,maxDepth" << endl;

    for (int z = 0; z < 3; z++) {
        int w = x[z];
        int v[M];
        int q1[M];
        for (int r1 = 0; r1 < 4; r1++) {
            t(v, w, r1);

            a(v, q1, w);
            s_t l1;
            f(q1, 0, w - 1, l1);
            cout << w << "," << y[r1] << ",Lomuto,"
                 << l1.a << "," << l1.b << ","
                 << l1.c << "," << l1.d << endl;

            a(v, q1, w);
            s_t h1;
            h(q1, 0, w - 1, h1);
            cout << w << "," << y[r1] << ",Hoare,"
                 << h1.a << "," << h1.b << ","
                 << h1.c << "," << h1.d << endl;
        }
    }
}

int main() {
    p();
    r();
    s();
    u();
    return 0;
}
