# -*- coding: utf-8 -*-
import math


def is_inside_sphere(x, y, d, delta_x):
    """
    Проверяет точку на принадлежность сферическому наконечнику волновода
    Точка в ск Федера
    :param delta_x - расстояние от конца прямой части до геом центра сферы
    """
    return (x - delta_x) * (x - delta_x) + y * y <= (d * d / 4 + delta_x * delta_x)


def check_point(x, y, d, length, delta_x):
    """
    Проверяет точку на принадлежность волноводу
    Точка в ск Федера
    """
    if -d / 2 <= y <= d / 2:
        return 0 <= x <= length or is_inside_sphere(x - length, y, d, delta_x)
    else:
        return is_inside_sphere(x - length, y, d, delta_x)
