#include <gtest/gtest.h>

#include <putty/palette.hh>

using namespace Putty;

static const Palette::RgbColor ibm_3279_default_colors[] = {
  Palette::RgbColor( 0x00, 0x00, 0x00 ),   // 0
  Palette::RgbColor( 0x00, 0xbf, 0xff ),   // 1
  Palette::RgbColor( 0xff, 0x00, 0x00 ),   // 2
  Palette::RgbColor( 0xff, 0xc0, 0xcb ),   // 3
  Palette::RgbColor( 0x00, 0xff, 0x00 ),   // 4
  Palette::RgbColor( 0x40, 0xe0, 0xd0 ),   // 5
  Palette::RgbColor( 0xff, 0xff, 0x00 ),   // 6
  Palette::RgbColor( 0x00, 0xbf, 0xff ),   // 7
  Palette::RgbColor( 0x00, 0x00, 0x00 ),   // 8
  Palette::RgbColor( 0x00, 0x00, 0xcd ),   // 9
  Palette::RgbColor( 0xff, 0xa5, 0x00 ),   // 10
  Palette::RgbColor( 0xa0, 0x20, 0xf0 ),   // 11
  Palette::RgbColor( 0x98, 0xfb, 0x98 ),   // 12
  Palette::RgbColor( 0xaf, 0xee, 0xee ),   // 13
  Palette::RgbColor( 0xbe, 0xbe, 0xbe ),   // 14
  Palette::RgbColor( 0xff, 0xff, 0xff ),   // 15
  Palette::RgbColor( 0x00, 0x00, 0x00 ),   // 16
  Palette::RgbColor( 0x00, 0xbf, 0xff ),   // 17
  Palette::RgbColor( 0xff, 0x00, 0x00 ),   // 18
  Palette::RgbColor( 0xff, 0xc0, 0xcb )    // 19
};



TEST(PuttyPalette, Construction)
{
  // The default palette can be created
  Palette palette;

  // Check a few colors
  ASSERT_EQ("#000000", palette.lookup(0).as_hex());
  ASSERT_EQ("#00ffd7", palette.lookup(50).as_hex());
  ASSERT_EQ("#878700", palette.lookup(100).as_hex());
  ASSERT_EQ("#ff00d7", palette.lookup(200).as_hex());
}

TEST(PuttyPalette, CopyConstruction)
{
  Palette palette_original;
  palette_original.set_color(0, 1, 2, 3);

  Palette palette_copy(palette_original);

  ASSERT_EQ("#010203", palette_copy.lookup(0).as_hex());
}

TEST(PuttyPalette, Assignment)
{
  Palette palette_original;
  palette_original.set_color(0, 1, 2, 3);

  Palette palette_copy;
  palette_copy = palette_original;

  ASSERT_EQ("#010203", palette_copy.lookup(0).as_hex());
}

TEST(PuttyPalette, SetColor)
{
  Palette palette;
  palette.set_color(0, 1, 2, 3);

  ASSERT_EQ("#010203", palette.lookup(0).as_hex());
}

TEST(PuttyPalette, Reset)
{
  Palette palette;
  palette.set_color(0, 1, 2, 3);
  palette.reset();

  ASSERT_EQ("#000000", palette.lookup(0).as_hex());
}

TEST(PuttyPalette, AsHex)
{
  Palette::RgbColor color = Palette::RgbColor( 1, 2, 3 );

  ASSERT_EQ("#010203", color.as_hex());
}

TEST(PuttyPalette, SmallerColorPalette)
{
  Palette palette(ibm_3279_default_colors);

  ASSERT_EQ("#000000", palette.lookup(0).as_hex());
  ASSERT_EQ("#afeeee", palette.lookup(13).as_hex());
  ASSERT_EQ("#000000", palette.lookup(100).as_hex());
}
