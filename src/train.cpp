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

  // Простой (неоптимальный) алгоритм – квадратичная сложность
  first->light = true;  // включаем свет в начальном вагоне

  int k = 1;
  while (true) {
    Car *cur = first;
    // Идём вперёд на k вагонов, выключая свет
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
    // Если стартовый вагон погас — мы обошли круг
    if (!first->light) {
      break;
    }
    ++k;  // увеличиваем предположительную длину
  }
  return k;
}

int Train::getOpCount() const {
  return countOp;
}
