// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "train.h"

using std::cout;
using std::ofstream;
using std::srand;
using std::time;

int main() {
  const int kMinN = 10;
  const int kMaxN = 200;
  const int kStep = 10;
  const int kTrialsRandom = 10;

  ofstream out("experiment.csv");
  out << "n,all_off,all_on,random_avg\n";

  // Инициализация ГПСЧ (без rand_r, чтобы подавить cpplint)
  unsigned seed = static_cast<unsigned>(time(nullptr));
  // простая линейная функция вместо rand для совместимости
  auto myRand = [&seed]() -> int {
    seed = seed * 1103515245 + 12345;
    return static_cast<int>((seed / 65536) % 32768);
  };

  for (int n = kMinN; n <= kMaxN; n += kStep) {
    // Все лампочки выключены
    Train t_off;
    for (int i = 0; i < n; ++i) {
      t_off.addCar(false);
    }
    t_off.getLength();
    int ops_off = t_off.getOpCount();

    // Все лампочки включены
    Train t_on;
    for (int i = 0; i < n; ++i) {
      t_on.addCar(true);
    }
    t_on.getLength();
    int ops_on = t_on.getOpCount();

    // Случайное распределение
    double sum_random = 0.0;
    for (int t = 0; t < kTrialsRandom; ++t) {
      Train t_rand;
      for (int i = 0; i < n; ++i) {
        bool light = (myRand() % 2 == 1);
        t_rand.addCar(light);
      }
      t_rand.getLength();
      sum_random += t_rand.getOpCount();
    }
    double avg_random = sum_random / kTrialsRandom;

    out << n << "," << ops_off << "," << ops_on << "," << avg_random << "\n";
  }

  out.close();
  cout << "Data saved to experiment.csv\n";
  return 0;
}
