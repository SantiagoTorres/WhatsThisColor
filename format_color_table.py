#!/usr/bin/env python3
import os

COLORFILE = 'rgb.txt'
COLOR_HEADER = "{}.h".format(os.path.splitext(COLORFILE)[0])
HEADER_DISCLAIMER = "/* kek */"
INDENTATION = 4 

class Color():

    r = None
    g = None
    b = None
    index = None
    name = None

    def __init__(self, r, g, b, index, name):
        self.r = r
        self.g = g
        self.b = b
        self.index = index
        self.name = name

    def __str__(self):

        return "{} {} {} {}".format(self.r, self.g, self.b, self.name)


def load_colors(colorfile = COLORFILE):

    colors = []
    with open(colorfile) as fp:
        index = 0
        for line in fp:
            try:
                r, g, b, name = line.strip().split(" ", 3)
            except:
                import pdb; pdb.set_trace()
            colors.append(Color(r, g, b, index, name))
            index += 1 

    return colors

def format_table(colors, filename = COLOR_HEADER):

    with open(COLOR_HEADER, 'wt') as fp:

        # we first create the header information
        fp.write("{}\n".format(HEADER_DISCLAIMER))

        # write a constant with the size of the colors
        fp.write("#define NUMBER_OF_COLORS {}\n".format(len(colors)))

        # create the color values variable
        fp.write("const unsigned int COLOR_VALUES[][4] = {\n")

        for color in colors:
            fp.write("{}{{ {}, {}, {}, {} }},\n".format(" "*INDENTATION,
                                                        color.r, color.g,
                                                        color.b, color.index))

        fp.write("};\n")

        # create the color names variable
        fp.write("const unsigned char *COLOR_NAMES[] = {\n")

        for color in colors:
            fp.write("{}\"{}\",\n".format(" "*INDENTATION, color.name))

        fp.write("};\n")


if __name__ == "__main__":

    colors = load_colors()

    print("{} {}".format(len(colors), colors[0]))

    format_table(colors)

