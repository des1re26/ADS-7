import matplotlib.pyplot as plt
import numpy as np
import csv

n, off, on, rand = [], [], [], []
with open('experiment.csv', 'r') as f:
    reader = csv.reader(f)
    next(reader)
    for row in reader:
        n.append(int(row[0]))
        off.append(int(row[1]))
        on.append(int(row[2]))
        rand.append(float(row[3]))

n = np.array(n)
off = np.array(off)
on = np.array(on)
rand = np.array(rand)

plt.figure(figsize=(10, 6))
plt.scatter(n, off, s=8, label='Все выключены', alpha=0.6)
plt.scatter(n, on, s=8, label='Все включены', alpha=0.6)
plt.scatter(n, rand, s=8, label='Случайное', alpha=0.6)

# Линейные тренды
for data, color, name in zip(
    [off, on, rand],
    ['blue', 'orange', 'green'],
    ['off', 'on', 'random']
):
    coeffs = np.polyfit(n, data, 1)
    trend = np.polyval(coeffs, n)
    plt.plot(n, trend, '--', color=color, linewidth=1.5,
             label=f'Тренд {name} ({coeffs[0]:.2f}n + {coeffs[1]:.0f})')

plt.xlabel('Длина поезда n')
plt.ylabel('Число перемещений')
plt.title('Зависимость числа операций от длины поезда (простой алгоритм)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('result/plot.png', dpi=150)
plt.show()
