#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <json/json.h>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, ll> Point;

// Convert number from a given base to decimal
ll convertToDecimal(const string &value, int base) {
    ll result = 0;
    for (char c : value) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = tolower(c) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}

// Compute constant term using Lagrange interpolation at x = 0
ll lagrangeInterpolationConstant(const vector<Point> &points) {
    ll result = 0;
    int k = points.size();

    for (int i = 0; i < k; ++i) {
        ll xi = points[i].first;
        ll yi = points[i].second;
        ll term = yi;

        for (int j = 0; j < k; ++j) {
            if (i == j) continue;
            ll xj = points[j].first;
            term *= -xj;
            term /= (xi - xj);
        }
        result += term;
    }
    return result;
}

int main() {
    ifstream file("testcase2.json");
    Json::Value root;
    file >> root;

    int n = root["keys"]["n"].asInt();
    int k = root["keys"]["k"].asInt();

    vector<Point> shares;
    for (const auto &key : root.getMemberNames()) {
        if (key == "keys") continue;
        int x = stoi(key);
        int base = stoi(root[key]["base"].asString());
        string value = root[key]["value"].asString();
        ll y = convertToDecimal(value, base);
        shares.push_back({x, y});
    }

    map<ll, int> secretFrequency;
    map<ll, vector<Point>> secretExamples;

    vector<int> indices(shares.size());
    iota(indices.begin(), indices.end(), 0);

    vector<int> combo(k);
    vector<Point> selected;

    for (int i = 0; i < (1 << shares.size()); ++i) {
        if (__builtin_popcount(i) != k) continue;
        selected.clear();
        for (int j = 0; j < shares.size(); ++j) {
            if (i & (1 << j)) selected.push_back(shares[j]);
        }
        try {
            ll secret = lagrangeInterpolationConstant(selected);
            secretFrequency[secret]++;
            if (secretExamples.find(secret) == secretExamples.end()) {
                secretExamples[secret] = selected;
            }
        } catch (...) {
            continue;
        }
    }

    ll bestSecret = 0;
    int maxFreq = 0;
    for (const auto &pair : secretFrequency) {
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
            bestSecret = pair.first;
        }
    }

    cout << "Secret (constant term): " << bestSecret << endl;
    cout << "Used shares:" << endl;
    for (auto [x, y] : secretExamples[bestSecret]) {
        cout << "(x=" << x << ", y=" << y << ")" << endl;
    }

    return 0;
}
