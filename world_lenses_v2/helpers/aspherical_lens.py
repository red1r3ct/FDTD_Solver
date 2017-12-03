# -*- coding: utf-8 -*-
import math
from .dimensions import px2mm, mm2px


def aspheric_curve_front(r, lam, lam_px):
    r = px2mm(r, lam, lam_px)
    R = 19.371
    a1 = 0.027322
    a2 = 5.5360 * 10 ** -5
    a3 = 1.5599 * 10 ** -7
    a4 = 1.0454 * 10 ** -9
    a5 = 2.7424 * 10 ** -12
    a6 = 0
    a = [a1, a2, a3, a4, a5, a6]

    result = r * r / R / (1 + math.sqrt(1 - (r / R) ** 2))
    for i in range(1, 7):
        result += a[i - 1] * r ** (2 * i)
    return mm2px(result, lam, lam_px)


def aspheric_curve_back(r, lam, lam_px):
    r = px2mm(r, lam, lam_px)
    R = -73.7687
    a1 = -0.012541
    a2 = 3.9795 * 10 ** -4
    a3 = -5.1724 * 10 ** -6
    a4 = 4.2630 * 10 ** -8
    a5 = -1.9919 * 10 ** -10
    a6 = 3.9967 * 10 ** -13
    a = [a1, a2, a3, a4, a5, a6]

    result = r * r / R / (1 + math.sqrt(1 - (r / R) ** 2))
    for i in range(1, 7):
        result += a[i - 1] * (r ** (2 * i))
    return mm2px(result, lam, lam_px)


def check_point(x, y, d, diameter, lam, lam_px):
    """
    Проверяет точку на принадлежность асферической линзы
    Точка в ск Федера
    """
    if 0 <= x <= d:
        if -diameter / 2 <= y <= diameter / 2:
            return aspheric_curve_front(y, lam, lam_px) <= x and (x - d) <= aspheric_curve_back(y, lam, lam_px)

    return False
