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
        video_writer_codec = cv2.VideoWriter_fourcc(*'MJPG')
        video_writer = cv2.VideoWriter(name, self.video_writer_codec, 20.0, (size_x,size_y))
        
