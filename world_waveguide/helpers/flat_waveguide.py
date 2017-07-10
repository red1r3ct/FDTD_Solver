class FlatWaveguide:
    def __init__(self, x0, y0, d_core, d_shell, length):
        self.x0 = x0
        self.y0 = y0
        self.d_core = d_core
        self.d_shell = d_shell
        self.length = length

    def is_core(self, x, y):
        if self.x0 <= x <= self.x0 + self.length:
            return self.y0 - self.d_core / 2 <= y <= self.y0 + self.d_core / 2
        else:
            return False

    def is_shell(self, x, y):
        if self.x0 <= x <= self.x0 + self.length:
            if self.y0 - self.d_core / 2 <= y <= self.y0 + self.d_core / 2:
                return False
            else:
                return self.y0 - self.d_shell / 2 <= y <= self.y0 + self.d_shell / 2
        else:
            return False
