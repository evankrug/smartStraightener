# This script is used to take in a BMP format file, and convert it to a compressed format that can be directly used in code.

import sys
import getopt
from PIL import Image


def main(argv):

    # First, pull out all the arguments we are interested in.
    input_image_file = ''
    output_code_file = ''

    try:
        opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
    except getopt.GetoptError:
        print ('bitmap_convert.py -i <inputfile> -o <outputfile>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print ('bitmap_convert.py -i <inputfile> -o <outputfile>')
            sys.exit()
        elif opt in ("-i", "--ifile"):
            input_image_file = arg
        elif opt in ("-o", "--ofile"):
            output_code_file = arg

    print ('Input file is "', input_image_file)
    print ('Output file is "', output_code_file)

    image_object = Image.open(input_image_file)

    print(image_object.getpixel((1, 1)))


if __name__ == "__main__":
    main(sys.argv[1:])