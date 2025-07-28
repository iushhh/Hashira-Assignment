#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <jsoncpp/json/json.h> // Requires jsoncpp library

using namespace std;

using bigint = __int128; // For large numbers

// Helper to print __int128
ostream& operator<<(ostream& os, const bigint& value) {
    if (value == 0) return os << "0";
    bigint tmp = value;
    string result;
    while (tmp > 0) {
        result += (char)('0' + tmp % 10);
        tmp /= 10;
    }
    reverse(result.begin(), result.end());
    return os << result;
}

// Convert base string to bigint
bigint base_to_bigint(const string& val, int base) {
    bigint result = 0;
    for (char c : val) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = tolower(c) - 'a' + 10;
        else continue;
        result = result * base + digit;
    }
    return result;
}

// Lagrange interpolation to find constant term f(0)
bigint lagrange_interpolation(const vector<pair<bigint, bigint>>& points) {
    bigint result = 0;
    for (int i = 0; i < points.size(); ++i) {
        bigint xi = points[i].first;
        bigint yi = points[i].second;

        bigint num = 1, den = 1;
        for (int j = 0; j < points.size(); ++j) {
            if (i == j) continue;
            bigint xj = points[j].first;
            num *= -xj;
            den *= (xi - xj);
        }
        // Multiply yi * (num / den)
        result += yi * num / den;
    }
    return result;
}

int main() {
    ifstream file("testcase2.json");
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(file, root)) {
        cerr << "Failed to parse JSON file" << endl;
        return 1;
    }

    int n = root["keys"]["n"].asInt();
    int k = root["keys"]["k"].asInt();

    vector<pair<bigint, bigint>> points;

    for (const auto& key : root.getMemberNames()) {
        if (key == "keys") continue;
        int x = stoi(key);
        string base_str = root[key]["base"].asString();
        string val_str = root[key]["value"].asString();

        int base = stoi(base_str);
        bigint y = base_to_bigint(val_str, base);
        points.emplace_back(x, y);
    }

    // Use first k points (or use combinations to validate if needed)
    vector<pair<bigint, bigint>> selected_points(points.begin(), points.begin() + k);

    bigint secret = lagrange_interpolation(selected_points);
    cout << "Secret = " << secret << endl;

    return 0;
}
