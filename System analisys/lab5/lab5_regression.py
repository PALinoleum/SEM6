from itertools import combinations

import matplotlib.pyplot as plt
import numpy as np

subscript_dict = str.maketrans("0123456789", "₀₁₂₃₄₅₆₇₈₉")

# Возвращает все возможные полиномы из набора слагаемых polynom_parts размером polynom_parts_count
def get_polynom_list(polynom_parts, polynom_parts_count=3):
    polynoms = []
    combination_list = combinations(range(len(polynom_parts)), polynom_parts_count)
    for combination in combination_list:
        combination = sorted(combination, reverse=True)
        result_element = []
        for part_num in combination:
            result_element.append(polynom_parts[part_num])
        polynoms.append(result_element)
    return polynoms


# Возвращает строковые имена функций из списка functions
def get_functions_labels(functions):
    labels = []
    for func in functions:
        labels.append(func.__name__)
    return labels


# Получение матриц F для каждого полинома в polynoms_list
def get_all_F_matrices(polynoms_list, x_vectors):
    F_matrices = []
    for polynom in polynoms_list:
        F_matrix = []
        for x_vector in x_vectors:
            F_matrix_str = []
            for polynom_part in polynom:
                F_matrix_str.append(polynom_part(x_vector[0], x_vector[1]))
            F_matrix.append(F_matrix_str)
        F_matrices.append(np.array(F_matrix))
    return F_matrices


# Получение векторов а для каждого полинома в списке polynoms_list
def get_all_a_vectors(F_matrices, Y_vector):
    a_vectors = []
    for F_matrix in F_matrices:
        a_vector = np.linalg.inv((F_matrix.T.dot(F_matrix))).dot(
            F_matrix.T.dot(Y_vector)
        )
        a_vectors.append(a_vector)
    return a_vectors


def get_best_polynom(F_matrices, a_vectors, Y_vector,polynoms):
    # Вычисляем y c крышечкой
    y_cap_vectors = []
    for F, a in zip(F_matrices, a_vectors):
        y_cap_vectors.append(F.dot(a))

    R2_1_list = []
    R2_2_list = []
    Q = sum(map(lambda y: (y - np.mean(Y_vector)) ** 2, Y_vector))
    for index,y_cap_vector in enumerate(y_cap_vectors):
        QR = sum(map(lambda y_cap_i: (y_cap_i - np.mean(Y_vector)) ** 2, y_cap_vector))
        Qstop = sum(
            map(lambda y_cap_i, Y_i: (Y_i - y_cap_i) ** 2, y_cap_vector, Y_vector)
        )
        # Вычислим коэффициент детерминации 2 способами
        R2_1 = QR / Q
        R2_2 = 1 - Qstop / Q
        R2_1_list.append(R2_1)
        R2_2_list.append(R2_2)
        print('{}. '.format(index+1),get_regression_equation(get_functions_labels(polynoms[index]),a_vectors[index]), ' Rr:' ,R2_1,'Rост: ',R2_2)
    # Возвращаем индекс максимального R2 (соответственно индекс полинома) для двух способов
    return (R2_1_list.index(max(R2_1_list)), R2_2_list.index(max(R2_2_list)))


def get_regression_equation(polynom_labels, a_vector):
    result_str = ""
    for index, label in enumerate(polynom_labels, start=1):
        result_str += str(round(a_vector[index - 1],5))
        result_str += " " + label + " + "
    return result_str[:-3]
