import numpy


class Point:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

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
