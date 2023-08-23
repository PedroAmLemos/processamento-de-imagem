import cv2

def quantize_image(image, levels):
    step_size = 256 // levels
    
    quantized_image = (image // step_size) * step_size
    
    return quantized_image

def main():
    image_path = "./lenna.png"  
    target_levels = [64, 32, 16, 8, 4, 2]    
    
    original_image = cv2.imread(image_path)  
    cv2.imshow("Original", original_image)
    cv2.waitKey(0)
    
    for levels in target_levels:
        quantized_image = quantize_image(original_image, levels)
        cv2.imshow(f"Quantized (Levels {levels})", quantized_image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

if __name__ == "__main__":
    main()

