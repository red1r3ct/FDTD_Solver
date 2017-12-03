# -*- coding: utf-8 -*-
def check_point(x, y, size_x, size_y):
    """
    Проверяет точку на принадлежность пластинке
    Точка в ск Федера
    """
    if 0 <= x <= size_x:
        return -size_y / 2 <= y <= size_y / 2
    return False
