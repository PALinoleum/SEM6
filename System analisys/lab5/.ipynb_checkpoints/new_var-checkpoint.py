from itertools import combinations
from pprint import pprint

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from scipy import stats



# количество слагаемых в уравнении регрессии (если неизвестно, то приравнять к None)
parts_in_polynom = 3

x = [
    (8.0, 12.0),
    (7.0, 4.0),
    (9.0, 11.0),
    (5.0, 9.0),
    (8.0, 8.0),
    (4.0, 6.0),
    (5.0, 11.0),
    (10.0, 17.0),
    (6.0, 11.0),
    (4.0, 9.0),
    (5.0, 16.0),
    (4.0, 7.0),
]

y = [
    434.6056050,
    99.4576048,
    426.5185028,
    219.8754453,
    261.1813246,
    113.2138322,
    293.0785722,
    811.3168444,
    325.0937345,
    209.3121888,
    506.5148699,
    140.8936827,
]

x_noise_check = (4.0, 8.0)

y_noise_check = [
    185.8041733,
    189.7014111,
    187.8794151,
    190.7171421,
    192.7927908,
    193.4331172,
    185.9415325,
    185.9871731,
    194.3002881,
    191.4144151,
]

# составные уравнения регрессии
def f_x1(x1, x2):
    return x1
f_x1.__name__ = "x₁"
def f_x2(x1, x2):
    return x2
f_x2.__name__ = "x₂"
def f_x1x1(x1, x2):
    return x1 ** 2
f_x1x1.__name__ = "x₁²"
def f_x1x2(x1, x2):
    return x1 * x2
f_x1x2.__name__ = "x₁x₂"
def f_x2x2(x1, x2):
    return x2 ** 2
f_x2x2.__name__ = "x₂²"
# добавленные регрессоры
def f_x2x2x1(x1, x2):
    return x2 ** 2 *x1
f_x2x2x1.__name__ = "x₁x₂²"
def f_x1x1x2(x1, x2):
    return x1 ** 2 *x2
f_x1x1x2.__name__ = "x₁²x₂"

# возможные слагаемые уравнения регрессии
polynom_parts = [f_x1, f_x2, f_x1x2, f_x1x1, f_x2x2,f_x2x2x1,f_x1x1x2]
polynoms = []
## получаем все возможные полиномы
combination_list = []
# если число слагаемых в полиноме известно, то используем его, иначе перебираем все возможные варианты от 2 слагаемых до полного полинома
if parts_in_polynom != None:
    combination_list = combinations(range(len(polynom_parts)), parts_in_polynom)
else:
    for i in range(2, len(polynom_parts) + 1):
        combination_list += combinations(range(len(polynom_parts)), i)
for combination in combination_list:
    combination = sorted(combination, reverse=True)
    result_element = []
    for part_num in combination:
        result_element.append(polynom_parts[part_num])
    polynoms.append(result_element)


def get_func_labels(func_list):
    labels = []
    for func in func_list:
        labels.append(func.__name__)
    return labels


# Получение матриц F для всех возможных уравнений регрессии
def get_all_F_matrices():
    F_matrices = []
    # вычисляем матрицу F для каждого полинома
    for polynom in polynoms:
        F_matrix = []
        for x_vector in x:
            F_str = []
            for polynom_part in polynom:
                F_str.append(polynom_part(x_vector[0], x_vector[1]))
            F_matrix.append(F_str)
        F_matrices.append(np.array(F_matrix))
    return F_matrices


def get_a_vector(F, Y):
    return np.linalg.inv((F.T.dot(F))).dot(F.T.dot(Y))


def get_all_a_vectors():
    a_vectors = []
    F_matrices = get_all_F_matrices()
    Y = np.array(y)
    for F_matrix in F_matrices:
        a_vector = get_a_vector(F_matrix, Y)
        a_vectors.append(a_vector)
    return a_vectors


# вычисляем значения аппроксимированные Y
def calc_Y_vector(a, F):
    return F.dot(a)


# поиск наилучшей мат модели
def find_best_polynom():
    # вычисляем все возможные y с крышечкой
    y_cap_vectors = []
    for a, F in zip(get_all_a_vectors(), get_all_F_matrices()):
        y_cap_vectors.append(calc_Y_vector(a, F))

    # игрек с черточкой, среднее значение y
    mean_real_Y = np.mean(y)

    Q = sum(map(lambda y_i: (y_i - mean_real_Y) ** 2, y))
    """
    all_R = []
    for y_cap_vector in y_cap_vectors:
        Q_stop = sum(map(lambda y_i,y_cap_i: (y_i-y_cap_i)**2,y,y_cap_vector))
        all_R.append(1-(Q_stop/Q))
    
    #номер лучшего полинома в списке
    polynom_index = all_R.index(max(all_R))
    #получаем красивую надпись полинома
    func_label = get_func_labels(polynoms[polynom_index])
    
    result_str = ''
    for func in func_label:
        result_str += func
        result_str += ' + '
    result_str = result_str[:-3]
    print('Наилучшее уравнение регрессии: ',result_str)
    print('R²: ',max(all_R))
    
    
    all_R = []
    for y_cap_vector in y_cap_vectors:
        Q_real = sum(map(lambda y_i,y_cap_i: (y_cap_i-mean_real_Y)**2,y,y_cap_vector))
        all_R.append(Q_real/Q)

    polynom_index = all_R.index(max(all_R))
    func_label = get_func_labels(polynoms[polynom_index])
    
    print('Наилучшее уравнение регрессии: ',func_label)
    print('R²: ',max(all_R))"""

    R_and_index = []
    # оценка качества модели критерием Фишера
    # уровень значимости = 0.01
    # k1 = 2
    # k2 = 9
    Ft = 8.65
    for index, y_cap_vector in enumerate(y_cap_vectors):
        Q_stop = sum(map(lambda y_i, y_cap_i: (y_i - y_cap_i) ** 2, y, y_cap_vector))
        Q_real = sum(map(lambda y_cap_i: (y_cap_i - np.mean(y)) ** 2, y_cap_vector))
        S_real = Q_real / 2
        S_stop = Q_stop / 9
        F = S_real / S_stop
        if F >= Ft:
            result_str = ""
            for func in get_func_labels(polynoms[index]):
                result_str += func
                result_str += " + "
            result_str = result_str[:-3]
            # print('Полином прошел по критерию Фишера: ',result_str)
            R_and_index.append(((Q_real/Q),index))
            # R_and_index.append(((1 - Q_stop / Q), index))
            print(
                "Полином:",
                result_str,
                "R² первая формула :",
                (Q_real / Q),
                "R² вторая формула:",
                (1 - Q_stop / Q),
            )
            expr_str = ""
            for a_value, func in zip(
                get_all_a_vectors()[index], get_func_labels(polynoms[index])
            ):
                expr_str += str(round(a_value, 4)) + " " + func + " + "
            expr_str = expr_str[:-3] + "\n"
            print(expr_str)

        else:
            result_str = ""
            for func in get_func_labels(polynoms[index]):
                result_str += func
                result_str += " + "
            result_str = result_str[:-3]
            # print('Полином не прошел ❌ по критерию Фишера: ',result_str)
    all_R, indexes = [], []
    for i in R_and_index:
        all_R.append(i[0])
        indexes.append(i[1])
    return indexes[all_R.index(max(all_R))]


def get_a_vector_noise(polynom_index):
    a = get_all_a_vectors()
    F = get_all_F_matrices()
    a = a[polynom_index]
    F = F[polynom_index]
    C = np.linalg.inv((F.T.dot(F)))
    a_noise_vector = []
    experiment_noise = np.var(y_noise_check)
    print("Дисперсия ошибок измерений (шума): ", experiment_noise)
    for C_i in np.diag(C):
        a_noise_vector.append(experiment_noise * np.sqrt(C_i))
    return a, np.array(a_noise_vector)


def student_check(a_vector, a_noise_vector):
    t_vector = list(
        map(lambda a, a_noise: np.abs(a) / a_noise, a_vector, a_noise_vector)
    )
    """
        кол-во степеней свободы - кол-во y в наборе для поиска шума
        уровень значимости 0.01
    """
    t_a = 21.7
    for index, t_i in enumerate(t_vector, start=1):
        if t_i > t_a:
            test = ""
        else:
            test = "(❌ Стьюдент не сходится, ну и ладно)"
        print(
            "Коэффициент a{}:".format(index).translate(SUB), a_vector[index - 1], test
        )
    # вычисляем доверительные интервалы
    t_gr = 3.2498355
    a = get_all_a_vectors()
    F = get_all_F_matrices()
    a = a[polynom_index]
    F = F[polynom_index]
    C = np.linalg.inv((F.T.dot(F)))
    C = np.diag(C)
    a_noise_vector = []
    experiment_noise = np.var(y_noise_check)
    for index, i in enumerate(a_vector):
        delta = t_gr * experiment_noise * np.sqrt(C[index])
        print(
            "Доверительный интервал a{} :".format(index + 1).translate(SUB),
            i - delta,
            " <= ",
            i,
            " <= ",
            i + delta,
        )


polynom_index = find_best_polynom()
func_label = get_func_labels(polynoms[polynom_index])
a_vector, a_noise_vector = get_a_vector_noise(polynom_index)
student_check(a_vector, a_noise_vector)

print("\nУравнение регрессии:")
expr_str = ""
for a_value, func in zip(a_vector, func_label):
    expr_str += str(round(a_value, 4)) + " " + func + " + "
expr_str = expr_str[:-3]

print(expr_str)

a = get_all_a_vectors()
F = get_all_F_matrices()
a = a[polynom_index]
F = F[polynom_index]
y_cap = F.dot(a)

x1 = []
x2 = []
for values in x:
    v1, v2 = values
    x1.append(v1)
    x2.append(v2)

fig = plt.figure()
axes = Axes3D(fig)
axes.plot_trisurf(np.array(x1), np.array(x2), np.array(y))
axes.plot_trisurf(np.array(x1), np.array(x2), np.array(y_cap))
plt.show()
