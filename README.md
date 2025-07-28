# Hashira-Assignment
Complete codes with both test cases and output
# Shamir's Secret Sharing Solver

This project solves a simplified version of Shamir's Secret Sharing problem from the Catalog Placements Assignment.

## 📁 Files

- `test_case_1.cpp`: Solver for Test Case 1 (basic version)
- `test_case_2.cpp`: Solver for Test Case 2 (filters out wrong shares)
- `testcase1.html`: Input file for Test Case 1
- `testcase2.html`: Input file for Test Case 2

## ✅ Final Output

- **Secret for Test Case 1**: `3`
- **Secret for Test Case 2**: '79836264049890'

## 🔧 How to Compile & Run

Make sure `jsoncpp` is installed.

```bash
g++ main1.cpp -ljsoncpp -std=c++17 -o solver1
./solver1

g++ main2.cpp -ljsoncpp -std=c++17 -o solver2
./solver2

