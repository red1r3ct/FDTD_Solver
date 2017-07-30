# -*- coding: utf-8 -*-


def check_point(x, y, d, d_shell, length):
    """
    Проверяет точку на принадлежность оболочке волновода
    Точка в ск Федера
    """
    if 0 <= x <= length:
        return -d_shell / 2 <= y <= -d / 2 or d / 2 <= y <= d_shell / 2
