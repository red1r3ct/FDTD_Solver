# -*- coding: utf-8 -*-
def mm2px(mm, lam, px_in_lam):
    return mm / lam * px_in_lam


def px2mm(px, lam, px_in_lam):
    return px / px_in_lam * lam
