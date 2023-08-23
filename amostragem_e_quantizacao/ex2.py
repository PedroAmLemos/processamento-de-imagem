import cv2
import numpy as np


def downsample_image(image, interval):
    rows, cols, _ = image.shape
    new_rows = rows // interval
    new_cols = cols // interval

    downsampled_image = np.zeros((new_rows, new_cols, 3), dtype=np.uint8)

    for i in range(new_rows):
        for j in range(new_cols):
            downsampled_image[i, j] = image[i * interval, j * interval]

    return downsampled_image


def main():
    image_path = "./lenna.png"  
    interval_list = [1, 5, 10, 15, 20]

    original_image = cv2.imread(image_path)

    for interval in interval_list:
        downsampled_image = downsample_image(original_image, interval)
        cv2.imshow(f"Downsampled (Interval {interval})", downsampled_image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()

