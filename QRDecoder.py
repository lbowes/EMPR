from PIL import Image, ImageOps
import os.path



PLATFORM_COLOUR = 0


def colour_sqr_distance(col_a, col_b):
    return pow(col_a - col_b, 2) 


def process_flag(flag_name):
    file_name =  flag_name + ".png"

    if(not os.path.exists(file_name)):
        return

    input_img = Image.open(flag_name + ".png")

    pixels = input_img.getdata()
    width, height = input_img.size
    pixel_data = []
    output_pixel_data = []

    imSizeW, imSizeH = input_img.size
    
    
    #file1 = open("dump.txt", "w")
    for pixel in pixels:
        #file1.write(str(pixel) + "\n")
        output_pixel_data.append((pixel,pixel,pixel))
        
    #70* 6
    rows = [70* 14, 70*  20, 70*  27, 70*  34, 70*  40, 70* 47, 70* 54]
    output_pixel_data[(70 * 53) + (3*6)] = (255,0,0)
    word = ''
    for row in rows:
        string = ""
        for col in range(0,5):
            if (output_pixel_data[(row) + (col*7) + 3])[0] < 100 :
                string = string + '1'
            else:
                string = string + '0'
        print(string)
        if string != '00000':
            word = word + chr(int(string,2) + 96 )
        
    word = word[::-1]
    url = [".com",".org",".onion",".co.uk",".jp"]
    for col in range(0,5):
        if (output_pixel_data[(70* 6) + (col*7) + 3])[0] < 100 :
                end = url[col]

    word = word + end
    print(word)
                
            #output_pixel_data[(row) + (col*7) + 3] = (255,0,0)
            
    #file1.close()

   # output_img = Image.new('RGB', (width, height))
    #output_img.putdata(output_pixel_data)
    #output_img = ImageOps.grayscale(output_img)
    #output_img.save(flag_name + "_no_bg.png")

    
            


def main():
	
	
    process_flag('QRGrey')


if __name__ == '__main__':
    main()
