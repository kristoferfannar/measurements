#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std::chrono;

duration<double> test1(const int N);
duration<double> test2(const int N);

void perform_test(duration<double> (*test_func)(int), const int N,
                  std::string name);

int main() {
  const int N = 100'000'000;

  /* part 1 */
  perform_test(test1, N, "T1 - Vector");
  perform_test(test2, N, "T2 - Vector");
}

void perform_test(duration<double> (*test_func)(int), const int N,
                  std::string name) {
  auto total = test_func(N);

  std::cout << name << ": " << total.count() << " seconds\n";
}

duration<double> test1(const int N) {
  std::vector<int> vec(N, 8);
  vec[N / 2] = 7;

  auto start = high_resolution_clock::now();
  auto result = std::find(vec.begin(), vec.end(), 7);
  auto end = high_resolution_clock::now();

  return end - start;
}

duration<double> test2(const int N) {
  std::vector<int> vec(N, 8);

  auto start = high_resolution_clock::now();
  auto result = std::find(vec.begin(), vec.end(), 7);
  auto end = high_resolution_clock::now();

  return end - start;
}
