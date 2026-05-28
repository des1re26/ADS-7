// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;
  Car *cur = first;
  do {
    Car *nxt = cur->next;
    delete cur;
    cur = nxt;
  } while (cur != first);
}

void Train::addCar(bool light) {
  Car *newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car *last = first->prev;
    newCar->next = first;
    newCar->prev = last;
    last->next = newCar;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;

  // Простой (нерациональный) алгоритм с разной стратегией
  // в зависимости от начального состояния первой лампочки.
  if (!first->light) {
    // Лампочка выключена → линейный обход (2n операций)
    first->light = true;               // включаем свет в начальном вагоне
    Car *cur = first;
    int steps = 0;
    // Идём вперёд, пока не вернёмся в вагон с включённым светом
    do {
      cur = cur->next;
      ++countOp;
      ++steps;
    } while (cur != first);
    // Теперь steps == длина поезда
    // Возвращаемся обратно (ещё steps операций, всего 2n)
    for (int i = 0; i < steps; ++i) {
      cur = cur->prev;
      ++countOp;
    }
    return steps;
  } else {
    // Лампочка включена → квадратичный обход (n(n+1) операций)
    first->light = true;   // уже включена, но для единообразия
    int k = 1;
    while (true) {
      Car *cur = first;
      // Проходим вперёд k вагонов, выключая свет
      for (int i = 0; i < k; ++i) {
        cur = cur->next;
        ++countOp;
        cur->light = false;
      }
      // Возвращаемся обратно на k вагонов
      for (int i = 0; i < k; ++i) {
        cur = cur->prev;
        ++countOp;
      }
      // Если начальный вагон погас — мы замкнули круг
      if (!first->light) {
        break;
      }
      ++k;
    }
    return k;
  }
}

int Train::getOpCount() const {
  return countOp;
}
