from PIL import Image
import os.path

FLAG_NAMES = [
    'central_african_rebublic',
    'united_kingdom',
    'czechia',
    'france',
    'iceland',
    'syria',
    'burkina_faso',
    'sudan',
    'north_macedonia',
    'burundi'
]

PLATFORM_COLOUR = (3, 2, 2)


def colour_sqr_distance(col_a, col_b):
    return pow(col_a[0] - col_b[0], 2) + pow(col_a[1] - col_b[1], 2) + pow(col_a[2] - col_b[2], 2)


def process_flag(flag_name):
    file_name = "../scans/png/" + flag_name + ".png"

    if(not os.path.exists(file_name)):
        return

    input_img = Image.open("../scans/png/" + flag_name + ".png")

    pixels = list(input_img.getdata())
    width, height = input_img.size

    output_pixel_data = []

    for pixel in pixels:
        if(colour_sqr_distance(pixel, PLATFORM_COLOUR) < 1700): #1700
            output_pixel_data.append((0, 255, 255))
        else:
            output_pixel_data.append(pixel)


    output_img = Image.new('RGB', (width, height))
    output_img.putdata(output_pixel_data)
    output_img.save("../scans/removed_bg/" + flag_name + "_no_bg.png")


def main():
    for flag_name in FLAG_NAMES:
        process_flag(flag_name)


if __name__ == '__main__':
    main()