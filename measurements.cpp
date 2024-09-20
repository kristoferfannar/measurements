/*
 * Author: Kristofer Fannar Bjornsson
 *         kfb2117
 *
 * System: Apple M3 Pro
 *         arm64
 *         macOS Sonoma 14.3.1
 */

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <stdio.h>
#include <vector>

using namespace std::chrono;

duration<double> test1(const int N);
duration<double> test2(const int N);
duration<double> test3(const int N);
duration<double> test4(const int N);
duration<double> test5(const int N);
duration<double> test6(const int N);

std::string rnd_str();

void perform_test(duration<double> (*test_func)(int), const int N,
                  std::string name);

int main() {
  const int N = 400'000'000;

  /* part 1 */
  perform_test(test1, N, "T1 - Vector");
  perform_test(test2, N, "T2 - Vector");

  /* part 2 */
  perform_test(test3, N, "T3 - Vector");
  perform_test(test4, N, "T4 - Vector");

  /* part 3 */
  perform_test(test5, N, "T5 - Vector");
  perform_test(test6, N, "T6 - Vector");
}

void perform_test(duration<double> (*test_func)(int), const int N,
                  std::string name) {

  std::vector<duration<double>> results(0);

  const int TRIES = 3;
  for (int i = 0; i < TRIES; i++) {
    auto total = test_func(N);
    results.push_back(total);
  }

  std::sort(results.begin(), results.end());

  /* get the median index
   * (3 / 2) == 1*/
  auto median = results[(TRIES / 2)];

  std::cout << name << ": " << duration_cast<milliseconds>(median).count()
            << "ms\n";
}

duration<double> test1(const int N) {
  std::vector<int> vec(N, 8);
  vec[N / 2] = 7;

  /* high_resolution_clock vs system_clock? */
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

/* Returns integers >= 7 */
std::default_random_engine int_engine;
/* random upper bound selected */
std::uniform_int_distribution<> int_dist{7, 10000};

duration<double> test3(const int N) {
  std::vector<int> vec(0);

  for (int i = 0; i < N; i++) {
    vec.push_back(int_dist(int_engine));
  }
  vec[N / 2] = 2;

  auto start = high_resolution_clock::now();
  auto result =
      std::find_if(vec.begin(), vec.end(), [](int i) { return i < 7; });
  auto end = high_resolution_clock::now();

  return end - start;
}

duration<double> test4(const int N) {
  std::vector<int> vec(0);

  for (int i = 0; i < N; i++) {
    vec.push_back(int_dist(int_engine));
  }

  auto start = high_resolution_clock::now();
  auto result =
      std::find_if(vec.begin(), vec.end(), [](int i) { return i < 7; });
  auto end = high_resolution_clock::now();

  return end - start;
}

const std::string chars =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::default_random_engine re;
std::uniform_int_distribution<> dist{0, (int)chars.length() - 1};

std::string rnd_str() {
  std::string rs;

  for (int i = 0; i < 20; i++) {
    auto rnd_char = chars[dist(re)];
    rs.push_back(rnd_char);
  }

  return rs;
}

duration<double> test5(const int N) {
  std::vector<std::string> vec(N, rnd_str());

  const std::string target = "XXXXXXXXXXXXXXXXXXXX";

  if (target.length() != 20) {
    perror("Target string not composed of 20 chars\n");
    exit(1);
  }

  auto start = high_resolution_clock::now();
  auto result = std::find(vec.begin(), vec.end(), target);
  auto end = high_resolution_clock::now();

  if (result == vec.end()) {
    std::cout << "nothing found\n";
  } else {
    std::cout << "found something\n";
  }

  return end - start;
}

duration<double> test6(const int N) {
  std::vector<std::string> vec(N, rnd_str());

  const std::string target = "XXXXXXXXXXXXXXXXXXXX";

  if (target.length() != 20) {
    perror("Target string not composed of 20 chars\n");
    exit(1);
  }

  vec[N / 2] = target;

  auto start = high_resolution_clock::now();
  auto result = std::find(vec.begin(), vec.end(), target);
  auto end = high_resolution_clock::now();

  return end - start;
}
