# -*- coding: utf-8 -*-
import math


def is_inside_cone(x, y, d, alpha):
    """
    Проверяет точку на принадлежность коническому наконечнику волновода
    Точка в ск Федера
    """
    k1 = math.tan(0.5 * (math.pi - alpha))
    h = 0.5 * d * math.tan(alpha / 2)
    k2 = math.tan(0.5 * (math.pi + alpha))
    return 0 <= x <= k1 * y + h and x <= k2 * y + h


def check_point(x, y, d, length, alpha):
    """
    Проверяет точку на принадлежность волноводу
    Точка в ск Федера
    """
    if -d / 2 <= y <= d / 2:
        return 0 <= x <= length or is_inside_cone(x - length, y - length, d, alpha)
