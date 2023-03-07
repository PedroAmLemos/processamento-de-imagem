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

    def __iter__(self):
        return iter((self.x, self.y))

    @staticmethod
    def __calcula_matriz_translacao(tx, ty):
        return numpy.matrix([[1, 0, tx], [0, 1, ty], [0, 0, 1]])

    @staticmethod
    def __calcula_matriz_rotacao(angulo):
        return numpy.matrix(
            [[numpy.cos(angulo), -numpy.sin(angulo), 0], [numpy.sin(angulo), numpy.cos(angulo), 0], [0, 0, 1]])

    def translacao(self, tx, ty):
        matriz_transformacao = self.__calcula_matriz_translacao(tx, ty)
        print(f'Matriz de transformacao <translacao>\n{matriz_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def escala(self, sx, sy):
        matriz_transformacao = numpy.matrix([[sx, 0, 0], [0, sy, 0], [0, 0, 1]])
        print(f'Matriz de transformacao <escala>\n{matriz_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def rotacao(self, angulo_graus):
        angulo = angulo_graus * numpy.pi / 180
        matriz_transformacao = self.__calcula_matriz_rotacao(angulo)
        print(f'Matriz de transformacao <rotacao>\n{matriz_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def cisalhamento(self, kx: float, ky: float):
        matriz_de_transformacao = numpy.matrix([[1, kx, 0], [ky, 1, 0], [0, 0, 1]])
        print(f'Matriz de transformacao <cisalhamento>\n{matriz_de_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_x(self):
        matriz_de_transformacao = numpy.matrix([[1, 0, 0], [0, -1, 0], [0, 0, 1]])
        print(f'Matriz de transformacao <reflexao x>\n{matriz_de_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_y(self):
        matriz_de_transformacao = numpy.matrix([[-1, 0, 0], [0, 1, 0], [0, 0, 1]])
        print(f'Matriz de transformacao <reflexao y>\n{matriz_de_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_linha_xy(self):
        matriz_de_transformacao = numpy.matrix([[0, 1, 0], [1, 0, 0], [0, 0, 1]])
        print(f'Matriz de transformacao <reflexao linha x=y>\n{matriz_de_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def reflexao_linha_menos_xy(self):
        matriz_de_transformacao = numpy.matrix([[0, -1, 0], [-1, 0, 0], [0, 0, 1]])
        print(f'Matriz de transformacao <reflexao linha -x=y>\n{matriz_de_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def rotacao_ponto(self, x, y, angulo_graus):
        angulo = angulo_graus * numpy.pi / 180
        cos = numpy.cos(angulo)
        sin = numpy.sin(angulo)
        matriz_de_transformacao = numpy.matrix(
            [[cos, -sin, (x - x * cos) + (y * sin)],
             [sin, cos, (y - y * cos) - (x * sin)],
             [0, 0, 1]])
        print(f'Matriz de transformacao <rotacao ponto>\n{matriz_de_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])

    def escala_ponto(self, x, y, sx, sy):
        matriz_de_transformacao = numpy.matrix([[sx, 0, x - x * sx], [0, sy, y - y * sy], [0, 0, 1]])
        print(f'Matriz de transformacao <escala ponto>\n{matriz_de_transformacao}')
        matriz_homogenea = numpy.matrix([[self.x], [self.y], [1]])
        resultado = numpy.matmul(matriz_de_transformacao, matriz_homogenea)
        return Point(resultado[0, 0], resultado[1, 0])
