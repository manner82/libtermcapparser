#!/usr/bin/env python

'''
Script to generate XTerm color codes. For information about
XTerm colors, visit http://www.mudpedia.org/wiki/Xterm_256_colors
'''

import sys

# These are the system colors. 0-7 are the traditional color
# values, 8-15 are the bright versions of these
basecols = {
    0 : (0x00, 0x00, 0x00),
    1 : (0x80, 0x00, 0x00),
    2 : (0x00, 0x80, 0x00),
    3 : (0x80, 0x80, 0x00),
    4 : (0x00, 0x00, 0x80),
    5 : (0x80, 0x00, 0x80),
    6 : (0x00, 0x80, 0x00),
    7 : (0x80, 0x80, 0x80),

    8 : (0x00, 0x00, 0x00),
    9 : (0xFF, 0x00, 0x00),
    10 : (0x00, 0xFF, 0x00),
    11 : (0xFF, 0xFF, 0x00),
    12 : (0x00, 0x00, 0xFF),
    13 : (0xFF, 0x00, 0xFF),
    14 : (0x00, 0xFF, 0x00),
    15 : (0xFF, 0xFF, 0xFF),
}

def xtermchannel(n):
    '''Get XTerm color channel from a color value'''

    if n == 0:
        return 0

    return n * 40 + 55

def xtermrgb(n):
    '''Convert an RGB value to it's hex representation'''

    b = xtermchannel(n % 6)
    g = xtermchannel((n / 6) % 6)
    r = xtermchannel(n / 36)

    return r, g, b

def colhex(n):
    '''Convert any color to a hex value.

    The following color value ranges are used:
        * 0-15: system color, see basecols.
        * 16-231: RGB colors, see xtermrgb.
        * 232-255: Grayscale colors.
    '''

    if 16 <= n <= 231:
        return xtermrgb(n - 16)

    elif 232 <= n <= 255:
        val = (n - 232) * 10 + 8
        return val, val, val

    else:
        return basecols[n]

if __name__ == '__main__':
    print 'namespace'
    print '{'
    print '  static const Cell::RgbColor xterm_colors[] = {'
    for i in range(256):
        print '    { 0x%02x, 0x%02x, 0x%02x },         // %3d' % (colhex(i) + (i, ))
    print '  };'
    print '} // namespace'
