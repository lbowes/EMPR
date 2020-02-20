class Pixel:
    def __init__(self, x, y, z, r, g, b) -> None:
        self.x, self.y, self.z, self.r, self.g, self.b = x, y, z, r, g, b

    def updateAndAverage(self, r: int, g: int, b: int):
        # self.r = int((self.r + r)/2)
        # self.g = int((self.g + g) / 2)
        # self.b = int((self.b + b) / 2)
        self.r=r
        self.g=g
        self.b=b
    def getRGB(self) -> tuple:
        return (self.r,self.g,self.b)

    def __eq__(self, pixel) -> bool:
        if pixel.x == self.x and pixel.y == self.y and pixel.z == self.z:
            return True
        return False
