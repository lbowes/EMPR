from PIL import Image
import math
import re


FLAG_NAME = 'north_macedonia'


def main():
    data_file = open("../scans/txt/" + FLAG_NAME + ".txt", 'r')
    non_empty_lines = [line for line in data_file.readlines() if line.strip()]

    pixel_data = []

    for line in non_empty_lines:
        pixel_data.append(pixel_from_rgb_str(line))

    data_file.close()

    save_image_from_pixel_data(pixel_data, "../scans/png/" + FLAG_NAME + ".png")


def pixel_from_rgb_str(rgb_str):
    split_line = rgb_str.split(' ')

    components = []
    for c in split_line:
        component = re.sub('[^0-9]','', c)

        if(component):
            components.append(int(component))

    if(len(components) < 3):
        return (0, 0, 0)

    return (components[0], components[1], components[2])


def save_image_from_pixel_data(pixel_data, file_name):
    img = Image.new('RGB', ( 235, 235 ))
    img.putdata(pixel_data)
    img.save(file_name)


if __name__ == '__main__':
    main()