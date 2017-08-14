# -*- coding: utf-8 -*-


def check_point(x, y, d, size):
    """
    Проверяет точку на принадлежность стенке экранирующей выход
    Точка в ск Федера
    """
    if 0 <= x <= size:
        return y >= d/2 or y <= -d/2
