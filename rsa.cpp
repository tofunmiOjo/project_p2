#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int get_e(int phi_n) {
    int e = phi_n - 1; // start with the largest possible value of e
    while (e > 1) {
        if (gcd(e, phi_n) == 1) {
            return e;
        }
        e--;
    }
    return -1; // no suitable value of e found
}


vector<int> find_primes(int start, int end) {
    vector<int> primes;
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) primes.push_back(i);
    }
    return primes;
}

int get_n(int p, int q){
  int n = p*q;
  return n;
}


int main() {
    int Lbound = 10000;
    int Ubound = 100000;

    vector<int> pAndq;
    while (pAndq.size() < 2) {
        pAndq = find_primes(Lbound, Ubound);
        Lbound = Ubound + 1;
        Ubound *= 2; // increase the range for the next iteration
    }
    int p = pAndq[0];
    int q = pAndq[1];

    int n = get_n(p,q);
    int phi_n = get_n ((p-1), (q-1));
    int e = get_e(phi_n);


    double d = (e-1)%phi_n;

    cout << "The two prime numbers in the given range are " << p << " and " << q << endl;
    cout << n << endl;
    cout << phi_n << endl;
    cout << e << endl;
    cout << d << endl;


    return 0;
}




   