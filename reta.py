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
    plt.show()


def bresenham(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    p = 2 * dy - dx
    p2 = 2 * dy
    xy2 = 2 * (dy - dx)

    x = x1
    y = y1

    plt.scatter(x, y)

    while x < x2:
        x += 1
        if p < 0:
            p += p2
        else:
            y += 1
            p += xy2
        plt.scatter(x, y)


def bresenham_retas(x1, y1, x2, y2):

    # Verifica o sinal da inclinação
    sx = 1 if x2 > x1 else -1
    sy = 1 if y2 > y1 else -1

    # Calcula as distâncias entre os pontos inicial e final
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)

    # Inverte x com y se estiver no segundo quadrante
    trocar = False
    if dy > dx:
        x1, y1 = y1, x1
        x2, y2 = y2, x2
        dx, dy = dy, dx
        sx, sy = sy, sx
        trocar = True

    # Inicializa o erro
    err = 2 * dy - dx

    while x1 != x2 or y1 != y2:
        ponto = (y1, x1) if trocar else (x1, y1)
        plt.scatter(ponto[0], ponto[1])

        # Atualiza os valores de erro, x e y
        if err > 0:
            y1 += sy
            err -= 2 * dx

        x1 += sx
        err += 2 * dy

    ponto = (y2, x2) if trocar else (x2, y2)
    plt.scatter(ponto[0], ponto[1])
    plt.show()


def bresenham_circunferencia(xc, yc, r):
    x = 0
    y = r
    d = 3 - 2 * r

    def simetria(xc, yc, x, y):
        plt.scatter(xc + x, yc + y)
        plt.scatter(xc - x, yc + y)
        plt.scatter(xc + x, yc - y)
        plt.scatter(xc - x, yc - y)
        plt.scatter(xc + y, yc + x)
        plt.scatter(xc - y, yc + x)
        plt.scatter(xc + y, yc - x)
        plt.scatter(xc - y, yc - x)

    while x <= y:
        simetria(xc, yc, x, y)

        if d < 0:
            d = d + 4 * x + 6
        else:
            d = d + 4 * (x - y) + 10
            y -= 1

        x += 1
    plt.show()


if __name__ == '__main__':
    dda(2, 2, 7, 6)
    bresenham_retas(2, 2, 5, 8)
    bresenham_circunferencia(5, 5, 4)

