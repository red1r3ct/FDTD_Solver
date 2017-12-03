# -*- coding: utf-8 -*-
def check_point(x, y, radius, d, diameter):
    """
    Проверяет точку на принадлежность сферической линзы
    Точка в ск Федера
    """
    if 0 <= x <= d:
        if -diameter / 2 <= y <= diameter / 2:
            return (x - radius) ** 2 + y ** 2 <= radius ** 2
    return False
