from transformacoes_ponto.ponto import Point, escala_centro_geometrico
import matplotlib.pyplot as plt

if __name__ == '__main__':
    pontos = [Point(6, 10), Point(8, 8), Point(8, 5), Point(4, 5), Point(4, 8)]
    a = [x for x, _ in pontos]
    b = [y for _, y in pontos]
    plt.plot(a, b)
    plt.show()

    transformacao = []
    for ponto in pontos:
        transformacao.append(ponto.rotacao_ponto(4, 5, 45))
        print(ponto.rotacao_ponto(4, 5, 45).x, ponto.rotacao_ponto(4, 5, 45).y)

    a = [x for x, _ in transformacao]
    b = [y for _, y in transformacao]

    plt.plot(a, b)
    plt.show()
