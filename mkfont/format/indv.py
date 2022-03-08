import os
from fontforge import *

font = open("desiredfont.ttf")
for glyph in font:
    if font[glyph].isWorthOutputting():
        font[glyph].export("img/" + font[glyph].glyphname + ".png")
