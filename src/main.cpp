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
  const int kMaxN = 200;       // можно увеличить при необходимости
  const int kStep = 10;
  const int kTrialsRandom = 10;  // число случайных конфигураций для усреднения

  ofstream out("experiment.csv");
  out << "n,all_off,all_on,random_avg\n";

  srand(static_cast<unsigned>(time(nullptr)));

  for (int n = kMinN; n <= kMaxN; n += kStep) {
    // 1. Все лампочки выключены
    Train t_off;
    for (int i = 0; i < n; ++i) {
      t_off.addCar(false);
    }
    t_off.getLength();
    int ops_off = t_off.getOpCount();

    // 2. Все лампочки включены
    Train t_on;
    for (int i = 0; i < n; ++i) {
      t_on.addCar(true);
    }
    t_on.getLength();
    int ops_on = t_on.getOpCount();

    // 3. Случайное распределение (среднее по нескольким попыткам)
    double sum_random = 0.0;
    for (int t = 0; t < kTrialsRandom; ++t) {
      Train t_rand;
      for (int i = 0; i < n; ++i) {
        bool light = (rand() % 2 == 1);
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
