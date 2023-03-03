import numpy


def find_centro_geometrico(points):
    media_x = sum(p.x for p in points) / len(points)
    media_y = sum(p.y for p in points) / len(points)
    return media_x, media_y


def escala_centro_geometrico(points, sx, sy):
    centro_x, centro_y = find_centro_geometrico(points)
    return [point.escala_ponto(centro_x, centro_y, sx, sy) for point in points]


class Point:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def translacao(self, tx, ty):
        matriz_transformacao = numpy.matrix([[1, 0, tx], [0, 1, ty], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def escala(self, sx, sy):
        matriz_transformacao = numpy.matrix([[sx, 0, 0], [0, sy, 0], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def rotacao(self, angulo):
        matriz_transformacao = numpy.matrix(
            [[numpy.cos(angulo), -numpy.sin(angulo), 0], [numpy.sin(angulo), numpy.cos(angulo), 0], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def cisalhamento(self, kx: float, ky: float):
        matriz_de_transformacao = numpy.matrix([[1, kx, 0], [ky, 1, 0], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_x(self):
        matriz_de_transformacao = numpy.matrix([[1, 0, 0], [0, -1, 0], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_y(self):
        matriz_de_transformacao = numpy.matrix([[1, 0, 0], [-1, 0, 0], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_linha_xy(self):
        matriz_de_transformacao = numpy.matrix([[0, 1, 0], [1, 0, 0], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_linha_menos_xy(self):
        matriz_de_transformacao = numpy.matrix([[0, -1, 0], [-1, 0, 0], [0, 0, 1]])
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def rotacao_ponto(self, x, y, angulo):
        return self.translacao(-x, -y).rotacao(angulo).translacao(x, y)

    def escala_ponto(self, x, y, sx, sy):
        return self.translacao(-x, -y).escala(sx, sy).translacao(x, y)
