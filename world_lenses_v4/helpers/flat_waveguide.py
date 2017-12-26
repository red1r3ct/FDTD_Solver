# -*- coding: utf-8 -*-
def check_point_eps(x, y, length, d):
    '''
    Проверяет точку на принадлежность плоскому волноводу
    Точка в ск Федера
    '''
    return x <= length and (-d / 2 <= y <= d / 2)


def check_point_sigma(x, y, length, d, d_sig):
    '''
    Проверяет точку на принадлежность оболочки плоского волновода
    Точка в ск Федера
    '''
    return x <= length and (-(d / 2 + d_sig) <= y <= d / 2) and (d / 2 <= y <= (d / 2 + d_sig))
