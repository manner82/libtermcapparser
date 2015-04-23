#ifndef PUTTY_PALETTE_HH_INCLUDE
#define PUTTY_PALETTE_HH_INCLUDE

#include <string.h>

namespace Putty
{

  /**
   * A palette represents the 256 indexed color RGB palette. By default
   * the palette values are filled with the default xterm palette colors.
   */
  class Palette
  {
  public:
    /** Color index */
    typedef unsigned char ColorIndex;

    /** Color channel */
    typedef unsigned char ColorChannel;

    /** Size of the palette */
    static const int PaletteSize = 256;

    /**
     * RGB color value.
     */
    struct RgbColor
    {
      RgbColor()
        : red(0), green(0), blue(0)
      { }

      RgbColor(ColorChannel red, ColorChannel green, ColorChannel blue)
        : red(red), green(green), blue(blue)
      { }

      ColorChannel red;
      ColorChannel green;
      ColorChannel blue;

      std::string as_hex() const;
    };

  public:
    /**
     * Construct a palette with the default values set.
     */
    Palette();

    /**
     * Construct a palette from an RgbColor array.
     */
    template < size_t N >
    Palette(const RgbColor (&palette)[N])
    {
      set_palette(palette);
    }

    /**
     * Copy constructor of the palette.
     */
    Palette(const Palette &other);

    /**
     * Assign another palettes values to this one.
     */
    Palette &operator=(const Palette &other);

    /**
     * Reset the palette values.
     */
    void reset();

    /**
     * Set the color at the given index.
     *
     * @param index Color index.
     * @param red RGB red channel.
     * @param green RGB green channel.
     * @param blue RGB blue channel.
     */
    void set_color(ColorIndex index, ColorChannel red, ColorChannel green, ColorChannel blue);

    /**
     * Lookup the color value at the given index.
     *
     * @param index Color index
     * @return RGB representation of the color.
     */
    const RgbColor &lookup(ColorIndex index) const;

  private:
    /**
     * Set the palette. If the source palette has more colors than PaletteSize,
     * the additional colors are dropped.
     *
     * @param palette The color array to set as palette.
     */
    template < size_t N >
    void set_palette(const RgbColor (&palette)[N])
    {
      memcpy(colors, palette, std::min(sizeof(palette), sizeof(colors)));
    }

  private:
    /** Current palette values. */
    RgbColor colors[PaletteSize];
  };

} // namespace Putty

#endif // PUTTY_PALETTE_HH_INCLUDE
