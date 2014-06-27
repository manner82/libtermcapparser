#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>

#include "putty/palette.hh"

using namespace Putty;

namespace
{

  static const Palette::RgbColor xterm_default_colors[] = {
    Palette::RgbColor( 0x00, 0x00, 0x00 ),         //   0
    Palette::RgbColor( 0x80, 0x00, 0x00 ),         //   1
    Palette::RgbColor( 0x00, 0x80, 0x00 ),         //   2
    Palette::RgbColor( 0x80, 0x80, 0x00 ),         //   3
    Palette::RgbColor( 0x00, 0x00, 0x80 ),         //   4
    Palette::RgbColor( 0x80, 0x00, 0x80 ),         //   5
    Palette::RgbColor( 0x00, 0x80, 0x80 ),         //   6
    Palette::RgbColor( 0xc0, 0xc0, 0xc0 ),         //   7
    Palette::RgbColor( 0x80, 0x80, 0x80 ),         //   8
    Palette::RgbColor( 0xff, 0x00, 0x00 ),         //   9
    Palette::RgbColor( 0x00, 0xff, 0x00 ),         //  10
    Palette::RgbColor( 0xff, 0xff, 0x00 ),         //  11
    Palette::RgbColor( 0x00, 0x00, 0xff ),         //  12
    Palette::RgbColor( 0xff, 0x00, 0xff ),         //  13
    Palette::RgbColor( 0x00, 0xff, 0xff ),         //  14
    Palette::RgbColor( 0xff, 0xff, 0xff ),         //  15
    Palette::RgbColor( 0x00, 0x00, 0x00 ),         //  16
    Palette::RgbColor( 0x00, 0x00, 0x5f ),         //  17
    Palette::RgbColor( 0x00, 0x00, 0x87 ),         //  18
    Palette::RgbColor( 0x00, 0x00, 0xaf ),         //  19
    Palette::RgbColor( 0x00, 0x00, 0xd7 ),         //  20
    Palette::RgbColor( 0x00, 0x00, 0xff ),         //  21
    Palette::RgbColor( 0x00, 0x5f, 0x00 ),         //  22
    Palette::RgbColor( 0x00, 0x5f, 0x5f ),         //  23
    Palette::RgbColor( 0x00, 0x5f, 0x87 ),         //  24
    Palette::RgbColor( 0x00, 0x5f, 0xaf ),         //  25
    Palette::RgbColor( 0x00, 0x5f, 0xd7 ),         //  26
    Palette::RgbColor( 0x00, 0x5f, 0xff ),         //  27
    Palette::RgbColor( 0x00, 0x87, 0x00 ),         //  28
    Palette::RgbColor( 0x00, 0x87, 0x5f ),         //  29
    Palette::RgbColor( 0x00, 0x87, 0x87 ),         //  30
    Palette::RgbColor( 0x00, 0x87, 0xaf ),         //  31
    Palette::RgbColor( 0x00, 0x87, 0xd7 ),         //  32
    Palette::RgbColor( 0x00, 0x87, 0xff ),         //  33
    Palette::RgbColor( 0x00, 0xaf, 0x00 ),         //  34
    Palette::RgbColor( 0x00, 0xaf, 0x5f ),         //  35
    Palette::RgbColor( 0x00, 0xaf, 0x87 ),         //  36
    Palette::RgbColor( 0x00, 0xaf, 0xaf ),         //  37
    Palette::RgbColor( 0x00, 0xaf, 0xd7 ),         //  38
    Palette::RgbColor( 0x00, 0xaf, 0xff ),         //  39
    Palette::RgbColor( 0x00, 0xd7, 0x00 ),         //  40
    Palette::RgbColor( 0x00, 0xd7, 0x5f ),         //  41
    Palette::RgbColor( 0x00, 0xd7, 0x87 ),         //  42
    Palette::RgbColor( 0x00, 0xd7, 0xaf ),         //  43
    Palette::RgbColor( 0x00, 0xd7, 0xd7 ),         //  44
    Palette::RgbColor( 0x00, 0xd7, 0xff ),         //  45
    Palette::RgbColor( 0x00, 0xff, 0x00 ),         //  46
    Palette::RgbColor( 0x00, 0xff, 0x5f ),         //  47
    Palette::RgbColor( 0x00, 0xff, 0x87 ),         //  48
    Palette::RgbColor( 0x00, 0xff, 0xaf ),         //  49
    Palette::RgbColor( 0x00, 0xff, 0xd7 ),         //  50
    Palette::RgbColor( 0x00, 0xff, 0xff ),         //  51
    Palette::RgbColor( 0x5f, 0x00, 0x00 ),         //  52
    Palette::RgbColor( 0x5f, 0x00, 0x5f ),         //  53
    Palette::RgbColor( 0x5f, 0x00, 0x87 ),         //  54
    Palette::RgbColor( 0x5f, 0x00, 0xaf ),         //  55
    Palette::RgbColor( 0x5f, 0x00, 0xd7 ),         //  56
    Palette::RgbColor( 0x5f, 0x00, 0xff ),         //  57
    Palette::RgbColor( 0x5f, 0x5f, 0x00 ),         //  58
    Palette::RgbColor( 0x5f, 0x5f, 0x5f ),         //  59
    Palette::RgbColor( 0x5f, 0x5f, 0x87 ),         //  60
    Palette::RgbColor( 0x5f, 0x5f, 0xaf ),         //  61
    Palette::RgbColor( 0x5f, 0x5f, 0xd7 ),         //  62
    Palette::RgbColor( 0x5f, 0x5f, 0xff ),         //  63
    Palette::RgbColor( 0x5f, 0x87, 0x00 ),         //  64
    Palette::RgbColor( 0x5f, 0x87, 0x5f ),         //  65
    Palette::RgbColor( 0x5f, 0x87, 0x87 ),         //  66
    Palette::RgbColor( 0x5f, 0x87, 0xaf ),         //  67
    Palette::RgbColor( 0x5f, 0x87, 0xd7 ),         //  68
    Palette::RgbColor( 0x5f, 0x87, 0xff ),         //  69
    Palette::RgbColor( 0x5f, 0xaf, 0x00 ),         //  70
    Palette::RgbColor( 0x5f, 0xaf, 0x5f ),         //  71
    Palette::RgbColor( 0x5f, 0xaf, 0x87 ),         //  72
    Palette::RgbColor( 0x5f, 0xaf, 0xaf ),         //  73
    Palette::RgbColor( 0x5f, 0xaf, 0xd7 ),         //  74
    Palette::RgbColor( 0x5f, 0xaf, 0xff ),         //  75
    Palette::RgbColor( 0x5f, 0xd7, 0x00 ),         //  76
    Palette::RgbColor( 0x5f, 0xd7, 0x5f ),         //  77
    Palette::RgbColor( 0x5f, 0xd7, 0x87 ),         //  78
    Palette::RgbColor( 0x5f, 0xd7, 0xaf ),         //  79
    Palette::RgbColor( 0x5f, 0xd7, 0xd7 ),         //  80
    Palette::RgbColor( 0x5f, 0xd7, 0xff ),         //  81
    Palette::RgbColor( 0x5f, 0xff, 0x00 ),         //  82
    Palette::RgbColor( 0x5f, 0xff, 0x5f ),         //  83
    Palette::RgbColor( 0x5f, 0xff, 0x87 ),         //  84
    Palette::RgbColor( 0x5f, 0xff, 0xaf ),         //  85
    Palette::RgbColor( 0x5f, 0xff, 0xd7 ),         //  86
    Palette::RgbColor( 0x5f, 0xff, 0xff ),         //  87
    Palette::RgbColor( 0x87, 0x00, 0x00 ),         //  88
    Palette::RgbColor( 0x87, 0x00, 0x5f ),         //  89
    Palette::RgbColor( 0x87, 0x00, 0x87 ),         //  90
    Palette::RgbColor( 0x87, 0x00, 0xaf ),         //  91
    Palette::RgbColor( 0x87, 0x00, 0xd7 ),         //  92
    Palette::RgbColor( 0x87, 0x00, 0xff ),         //  93
    Palette::RgbColor( 0x87, 0x5f, 0x00 ),         //  94
    Palette::RgbColor( 0x87, 0x5f, 0x5f ),         //  95
    Palette::RgbColor( 0x87, 0x5f, 0x87 ),         //  96
    Palette::RgbColor( 0x87, 0x5f, 0xaf ),         //  97
    Palette::RgbColor( 0x87, 0x5f, 0xd7 ),         //  98
    Palette::RgbColor( 0x87, 0x5f, 0xff ),         //  99
    Palette::RgbColor( 0x87, 0x87, 0x00 ),         // 100
    Palette::RgbColor( 0x87, 0x87, 0x5f ),         // 101
    Palette::RgbColor( 0x87, 0x87, 0x87 ),         // 102
    Palette::RgbColor( 0x87, 0x87, 0xaf ),         // 103
    Palette::RgbColor( 0x87, 0x87, 0xd7 ),         // 104
    Palette::RgbColor( 0x87, 0x87, 0xff ),         // 105
    Palette::RgbColor( 0x87, 0xaf, 0x00 ),         // 106
    Palette::RgbColor( 0x87, 0xaf, 0x5f ),         // 107
    Palette::RgbColor( 0x87, 0xaf, 0x87 ),         // 108
    Palette::RgbColor( 0x87, 0xaf, 0xaf ),         // 109
    Palette::RgbColor( 0x87, 0xaf, 0xd7 ),         // 110
    Palette::RgbColor( 0x87, 0xaf, 0xff ),         // 111
    Palette::RgbColor( 0x87, 0xd7, 0x00 ),         // 112
    Palette::RgbColor( 0x87, 0xd7, 0x5f ),         // 113
    Palette::RgbColor( 0x87, 0xd7, 0x87 ),         // 114
    Palette::RgbColor( 0x87, 0xd7, 0xaf ),         // 115
    Palette::RgbColor( 0x87, 0xd7, 0xd7 ),         // 116
    Palette::RgbColor( 0x87, 0xd7, 0xff ),         // 117
    Palette::RgbColor( 0x87, 0xff, 0x00 ),         // 118
    Palette::RgbColor( 0x87, 0xff, 0x5f ),         // 119
    Palette::RgbColor( 0x87, 0xff, 0x87 ),         // 120
    Palette::RgbColor( 0x87, 0xff, 0xaf ),         // 121
    Palette::RgbColor( 0x87, 0xff, 0xd7 ),         // 122
    Palette::RgbColor( 0x87, 0xff, 0xff ),         // 123
    Palette::RgbColor( 0xaf, 0x00, 0x00 ),         // 124
    Palette::RgbColor( 0xaf, 0x00, 0x5f ),         // 125
    Palette::RgbColor( 0xaf, 0x00, 0x87 ),         // 126
    Palette::RgbColor( 0xaf, 0x00, 0xaf ),         // 127
    Palette::RgbColor( 0xaf, 0x00, 0xd7 ),         // 128
    Palette::RgbColor( 0xaf, 0x00, 0xff ),         // 129
    Palette::RgbColor( 0xaf, 0x5f, 0x00 ),         // 130
    Palette::RgbColor( 0xaf, 0x5f, 0x5f ),         // 131
    Palette::RgbColor( 0xaf, 0x5f, 0x87 ),         // 132
    Palette::RgbColor( 0xaf, 0x5f, 0xaf ),         // 133
    Palette::RgbColor( 0xaf, 0x5f, 0xd7 ),         // 134
    Palette::RgbColor( 0xaf, 0x5f, 0xff ),         // 135
    Palette::RgbColor( 0xaf, 0x87, 0x00 ),         // 136
    Palette::RgbColor( 0xaf, 0x87, 0x5f ),         // 137
    Palette::RgbColor( 0xaf, 0x87, 0x87 ),         // 138
    Palette::RgbColor( 0xaf, 0x87, 0xaf ),         // 139
    Palette::RgbColor( 0xaf, 0x87, 0xd7 ),         // 140
    Palette::RgbColor( 0xaf, 0x87, 0xff ),         // 141
    Palette::RgbColor( 0xaf, 0xaf, 0x00 ),         // 142
    Palette::RgbColor( 0xaf, 0xaf, 0x5f ),         // 143
    Palette::RgbColor( 0xaf, 0xaf, 0x87 ),         // 144
    Palette::RgbColor( 0xaf, 0xaf, 0xaf ),         // 145
    Palette::RgbColor( 0xaf, 0xaf, 0xd7 ),         // 146
    Palette::RgbColor( 0xaf, 0xaf, 0xff ),         // 147
    Palette::RgbColor( 0xaf, 0xd7, 0x00 ),         // 148
    Palette::RgbColor( 0xaf, 0xd7, 0x5f ),         // 149
    Palette::RgbColor( 0xaf, 0xd7, 0x87 ),         // 150
    Palette::RgbColor( 0xaf, 0xd7, 0xaf ),         // 151
    Palette::RgbColor( 0xaf, 0xd7, 0xd7 ),         // 152
    Palette::RgbColor( 0xaf, 0xd7, 0xff ),         // 153
    Palette::RgbColor( 0xaf, 0xff, 0x00 ),         // 154
    Palette::RgbColor( 0xaf, 0xff, 0x5f ),         // 155
    Palette::RgbColor( 0xaf, 0xff, 0x87 ),         // 156
    Palette::RgbColor( 0xaf, 0xff, 0xaf ),         // 157
    Palette::RgbColor( 0xaf, 0xff, 0xd7 ),         // 158
    Palette::RgbColor( 0xaf, 0xff, 0xff ),         // 159
    Palette::RgbColor( 0xd7, 0x00, 0x00 ),         // 160
    Palette::RgbColor( 0xd7, 0x00, 0x5f ),         // 161
    Palette::RgbColor( 0xd7, 0x00, 0x87 ),         // 162
    Palette::RgbColor( 0xd7, 0x00, 0xaf ),         // 163
    Palette::RgbColor( 0xd7, 0x00, 0xd7 ),         // 164
    Palette::RgbColor( 0xd7, 0x00, 0xff ),         // 165
    Palette::RgbColor( 0xd7, 0x5f, 0x00 ),         // 166
    Palette::RgbColor( 0xd7, 0x5f, 0x5f ),         // 167
    Palette::RgbColor( 0xd7, 0x5f, 0x87 ),         // 168
    Palette::RgbColor( 0xd7, 0x5f, 0xaf ),         // 169
    Palette::RgbColor( 0xd7, 0x5f, 0xd7 ),         // 170
    Palette::RgbColor( 0xd7, 0x5f, 0xff ),         // 171
    Palette::RgbColor( 0xd7, 0x87, 0x00 ),         // 172
    Palette::RgbColor( 0xd7, 0x87, 0x5f ),         // 173
    Palette::RgbColor( 0xd7, 0x87, 0x87 ),         // 174
    Palette::RgbColor( 0xd7, 0x87, 0xaf ),         // 175
    Palette::RgbColor( 0xd7, 0x87, 0xd7 ),         // 176
    Palette::RgbColor( 0xd7, 0x87, 0xff ),         // 177
    Palette::RgbColor( 0xd7, 0xaf, 0x00 ),         // 178
    Palette::RgbColor( 0xd7, 0xaf, 0x5f ),         // 179
    Palette::RgbColor( 0xd7, 0xaf, 0x87 ),         // 180
    Palette::RgbColor( 0xd7, 0xaf, 0xaf ),         // 181
    Palette::RgbColor( 0xd7, 0xaf, 0xd7 ),         // 182
    Palette::RgbColor( 0xd7, 0xaf, 0xff ),         // 183
    Palette::RgbColor( 0xd7, 0xd7, 0x00 ),         // 184
    Palette::RgbColor( 0xd7, 0xd7, 0x5f ),         // 185
    Palette::RgbColor( 0xd7, 0xd7, 0x87 ),         // 186
    Palette::RgbColor( 0xd7, 0xd7, 0xaf ),         // 187
    Palette::RgbColor( 0xd7, 0xd7, 0xd7 ),         // 188
    Palette::RgbColor( 0xd7, 0xd7, 0xff ),         // 189
    Palette::RgbColor( 0xd7, 0xff, 0x00 ),         // 190
    Palette::RgbColor( 0xd7, 0xff, 0x5f ),         // 191
    Palette::RgbColor( 0xd7, 0xff, 0x87 ),         // 192
    Palette::RgbColor( 0xd7, 0xff, 0xaf ),         // 193
    Palette::RgbColor( 0xd7, 0xff, 0xd7 ),         // 194
    Palette::RgbColor( 0xd7, 0xff, 0xff ),         // 195
    Palette::RgbColor( 0xff, 0x00, 0x00 ),         // 196
    Palette::RgbColor( 0xff, 0x00, 0x5f ),         // 197
    Palette::RgbColor( 0xff, 0x00, 0x87 ),         // 198
    Palette::RgbColor( 0xff, 0x00, 0xaf ),         // 199
    Palette::RgbColor( 0xff, 0x00, 0xd7 ),         // 200
    Palette::RgbColor( 0xff, 0x00, 0xff ),         // 201
    Palette::RgbColor( 0xff, 0x5f, 0x00 ),         // 202
    Palette::RgbColor( 0xff, 0x5f, 0x5f ),         // 203
    Palette::RgbColor( 0xff, 0x5f, 0x87 ),         // 204
    Palette::RgbColor( 0xff, 0x5f, 0xaf ),         // 205
    Palette::RgbColor( 0xff, 0x5f, 0xd7 ),         // 206
    Palette::RgbColor( 0xff, 0x5f, 0xff ),         // 207
    Palette::RgbColor( 0xff, 0x87, 0x00 ),         // 208
    Palette::RgbColor( 0xff, 0x87, 0x5f ),         // 209
    Palette::RgbColor( 0xff, 0x87, 0x87 ),         // 210
    Palette::RgbColor( 0xff, 0x87, 0xaf ),         // 211
    Palette::RgbColor( 0xff, 0x87, 0xd7 ),         // 212
    Palette::RgbColor( 0xff, 0x87, 0xff ),         // 213
    Palette::RgbColor( 0xff, 0xaf, 0x00 ),         // 214
    Palette::RgbColor( 0xff, 0xaf, 0x5f ),         // 215
    Palette::RgbColor( 0xff, 0xaf, 0x87 ),         // 216
    Palette::RgbColor( 0xff, 0xaf, 0xaf ),         // 217
    Palette::RgbColor( 0xff, 0xaf, 0xd7 ),         // 218
    Palette::RgbColor( 0xff, 0xaf, 0xff ),         // 219
    Palette::RgbColor( 0xff, 0xd7, 0x00 ),         // 220
    Palette::RgbColor( 0xff, 0xd7, 0x5f ),         // 221
    Palette::RgbColor( 0xff, 0xd7, 0x87 ),         // 222
    Palette::RgbColor( 0xff, 0xd7, 0xaf ),         // 223
    Palette::RgbColor( 0xff, 0xd7, 0xd7 ),         // 224
    Palette::RgbColor( 0xff, 0xd7, 0xff ),         // 225
    Palette::RgbColor( 0xff, 0xff, 0x00 ),         // 226
    Palette::RgbColor( 0xff, 0xff, 0x5f ),         // 227
    Palette::RgbColor( 0xff, 0xff, 0x87 ),         // 228
    Palette::RgbColor( 0xff, 0xff, 0xaf ),         // 229
    Palette::RgbColor( 0xff, 0xff, 0xd7 ),         // 230
    Palette::RgbColor( 0xff, 0xff, 0xff ),         // 231
    Palette::RgbColor( 0x08, 0x08, 0x08 ),         // 232
    Palette::RgbColor( 0x12, 0x12, 0x12 ),         // 233
    Palette::RgbColor( 0x1c, 0x1c, 0x1c ),         // 234
    Palette::RgbColor( 0x26, 0x26, 0x26 ),         // 235
    Palette::RgbColor( 0x30, 0x30, 0x30 ),         // 236
    Palette::RgbColor( 0x3a, 0x3a, 0x3a ),         // 237
    Palette::RgbColor( 0x44, 0x44, 0x44 ),         // 238
    Palette::RgbColor( 0x4e, 0x4e, 0x4e ),         // 239
    Palette::RgbColor( 0x58, 0x58, 0x58 ),         // 240
    Palette::RgbColor( 0x62, 0x62, 0x62 ),         // 241
    Palette::RgbColor( 0x6c, 0x6c, 0x6c ),         // 242
    Palette::RgbColor( 0x76, 0x76, 0x76 ),         // 243
    Palette::RgbColor( 0x80, 0x80, 0x80 ),         // 244
    Palette::RgbColor( 0x8a, 0x8a, 0x8a ),         // 245
    Palette::RgbColor( 0x94, 0x94, 0x94 ),         // 246
    Palette::RgbColor( 0x9e, 0x9e, 0x9e ),         // 247
    Palette::RgbColor( 0xa8, 0xa8, 0xa8 ),         // 248
    Palette::RgbColor( 0xb2, 0xb2, 0xb2 ),         // 249
    Palette::RgbColor( 0xbc, 0xbc, 0xbc ),         // 250
    Palette::RgbColor( 0xc6, 0xc6, 0xc6 ),         // 251
    Palette::RgbColor( 0xd0, 0xd0, 0xd0 ),         // 252
    Palette::RgbColor( 0xda, 0xda, 0xda ),         // 253
    Palette::RgbColor( 0xe4, 0xe4, 0xe4 ),         // 254
    Palette::RgbColor( 0xee, 0xee, 0xee )          // 255
  };
} // namespace

std::string
Palette::RgbColor::as_hex() const
{
  std::stringstream ss;
  ss << '#'
     << std::hex << std::setw(2) << std::setfill('0') << (int)red
     << std::hex << std::setw(2) << std::setfill('0') << (int)green
     << std::hex << std::setw(2) << std::setfill('0') << (int)blue;
  return ss.str();
}

Palette::Palette()
{
  reset();
}

Palette::Palette(const Palette &other)
{
  set_palette(other.colors);
}

Palette &
Palette::operator=(const Palette &other)
{
  set_palette(other.colors);
  return *this;
}

void
Palette::reset()
{
  set_palette(xterm_default_colors);
}

void
Palette::set_color(ColorIndex index, ColorChannel red, ColorChannel green, ColorChannel blue)
{
  colors[index].red = red;
  colors[index].green = green;
  colors[index].blue = blue;
}

const Palette::RgbColor &
Palette::lookup(ColorIndex index) const
{
  return colors[index];
}
