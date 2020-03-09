from PIL import Image, ImageOps
import os.path



PLATFORM_COLOUR = 80


def colour_sqr_distance(col_a, col_b):
    return pow(col_a - col_b, 2) 


def process_flag(flag_name):
    file_name =  flag_name + ".png"

    if(not os.path.exists(file_name)):
        return

    input_img = Image.open(flag_name + ".png")

    pixels = input_img.getdata()
    width, height = input_img.size

    output_pixel_data = []
    #file1 = open("dump.txt", "w")
    for pixel in pixels:
        #file1.write(str(pixel) + "\n")
        if(pixel < 140): #1700
            output_pixel_data.append((0,0,0))
        else:
            output_pixel_data.append((pixel,pixel,pixel))

    #file1.close()

    output_img = Image.new('RGB', (width, height))
    output_img.putdata(output_pixel_data)
    output_img = ImageOps.grayscale(output_img)
    output_img.save(flag_name + "_no_bg.png")


def main():
	
	
    process_flag('QRGrey')


if __name__ == '__main__':
    main()
