import cv2
import numpy as np
import matplotlib.pyplot as plt

def calculate_histogram(image):
    # Inicializar histograma com zeros
    histogram = np.zeros(256)
    
    # Calcular o histograma
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            histogram[image[i, j]] += 1
            
    return histogram

def equalize_histogram(image, histogram):
    # Calcular a função de transformação cumulativa
    cdf = np.cumsum(histogram)
    cdf_normalized = cdf * 255 / cdf[-1]
    
    # Equalizar a imagem
    img_equalized = np.interp(image, np.arange(256), cdf_normalized)
    
    return img_equalized.astype(np.uint8), cdf_normalized

# Ler a imagem em escala de cinza
image = cv2.imread('./lenna.png', cv2.IMREAD_GRAYSCALE)

# Calcular o histograma original
histogram = calculate_histogram(image)

# Equalizar a imagem
img_equalized, cdf_normalized = equalize_histogram(image, histogram)

# Calcular o histograma da imagem equalizada
histogram_equalized = calculate_histogram(img_equalized)

# Plotar os resultados
plt.figure(figsize=(12, 8))

plt.subplot(2, 2, 1)
plt.title("Histograma Original")
plt.bar(np.arange(256), histogram, width=1)

plt.subplot(2, 2, 2)
plt.title("Função de Transformação")
plt.plot(cdf_normalized, color='black')

plt.subplot(2, 2, 3)
plt.title("Histograma Equalizado")
plt.bar(np.arange(256), histogram_equalized, width=1)

plt.subplot(2, 2, 4)
plt.title("Imagem Equalizada")
plt.imshow(img_equalized, cmap='gray')

plt.tight_layout()
plt.show()
