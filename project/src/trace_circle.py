import math


def main():
    x = 0
    y = 0
    lastX = 0
    lastY = 0

    roundCircle = 0.0
    padding = 50
    steps = 200

    for i in range(steps):
        sinVal = math.sin(i / float(steps) * 2 * math.pi)
        cosVal = math.cos(i / float(steps) * 2 * math.pi)

        x = 50 + int((sinVal + 1) / 2 * 100)
        y = 50 + int((cosVal + 1) / 2 * 136)

        if(lastX != x or lastY != y):
            print(F"Motion_moveTo({x}, {y}, 0);")

        lastX = x
        lastY = y


if __name__ == '__main__':
    main()