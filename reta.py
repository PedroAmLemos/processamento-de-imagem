import matplotlib.pyplot as plt


def dda(x1, y1, x2, y2, log=0):
    step = abs(x2 - x1)
    if abs(y2 - y1) > step:
        step = abs(y2 - y1)

    xinc = (x2 - x1) / step
    yinc = (y2 - y1) / step
    x = x1
    y = y1

    while x <= x2:
        plt.scatter(round(x), round(y))
        if log:
            print(f"x = {x}, y= {y}, round(y) = {round(y)}")
        x = x + xinc
        y = y + yinc


if __name__ == '__main__':
    dda(2, 2, 7, 6, 1)
    plt.show()
