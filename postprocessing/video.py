import cv2
import numpy as np


class Video:
    def __init__(self, size_x, size_y, max_val):
        self.size_x = size_x
        self.size_y = size_y
        self.max = max_val
        self.frames = []

    def add_frame(self, np_arr):
        self.frames.append(np_arr)
        return False

    def write(name):
        print("No writer yet")
