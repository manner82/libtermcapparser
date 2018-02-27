#ifndef PUTTY_ROW_HH_INCLUDE
#define PUTTY_ROW_HH_INCLUDE

#include <putty/cell.hh>

namespace Putty
{

  class Cell;

  /**
   * Represents a row in the display state of the terminal. A row
   * contains a number of cells and the row attributes.
   */
  class Row
  {
    friend class TermcapParser;
    friend class State;

  public:
    /** Row attributes */
    typedef unsigned long Attributes;

    /**
     * Row attribute flags.
     */
    enum Flags
    {
      NORMAL = 0x00000000UL,        /**< Normal text */
      WIDE = 0x00000001UL,          /**< Double width text */
      TOP = 0x00000002UL,           /**< Top half of double height text */
      BOTTOM = 0x00000003UL,        /**< Bottom half of double height text */
      MASK_MODE = 0x00000003UL,     /**< Text mode mask */

      WRAPPED = 0x00000010UL,       /**< The row wraps to the next one (is continued) */
      WRAPPED_WIDE = 0x00000020UL,  /**< Used with WRAPPED: wide character wrapped to next line */
    };

  public:
    /**
     * Copy constructor.
     */
    Row(const Row &other);

    /**
     * Destructor.
     */
    ~Row();

    /**
     * Assing another row to this row.
     *
     * @param other Other row
     * @return Reference to the assigned object.
     */
    Row &operator=(const Row &other);

    void clear_changed();

    /**
     * Get the row width.
     *
     * @return Width of the row.
     */
    inline unsigned get_width() const
    { return width; }

    /**
     * Get the cell at the given column.
     *
     * @param col Column position.
     */
    const Cell *get_cell(unsigned col) const;

    /**
     * Get the attributes of the row.
     *
     * @return Attribute integer.
     */
    inline Attributes get_attributes() const
    { return attributes; }

    /**
     * Get the text mode.
     *
     * @return Text mode. See Flags.
     */
    inline Attributes get_mode() const
    { return attributes & MASK_MODE; }

    /**
     * Is the line wrapped to the next line?
     *
     * @return True if the line is wrapped.
     */
    inline bool is_wrapped() const
    { return attributes & WRAPPED; }

  protected:
    /**
     * Default constructor. Creates an empty row (row with width 0).
     */
    Row();

    /**
     * Set the width of the row. The data previously here is kept if the new width
     * is greater than it was or is clipped if it's smaller.
     *
     * @param width New width of the row.
     */
    void set_width(unsigned width);

    /**
     * Set the character and attribute pair (a Cell object) at any given position.
     *
     * @param col Column of the cell.
     * @param chr Character of the cell.
     * @param attr Attributes of the cell.
     */
    bool set_cell(unsigned col, const std::wstring &characters, Cell::Attributes attr);

    /**
     * Set the attributes of the row.
     *
     * @param attr New attributes of the row.
     */
    void set_attributes(Attributes attr);

    /**
     * Clear all row data. After this call, the width of the row will be 0.
     */
    void clear();

    void swap(Row &other);

    /** Cells in the row. */
    Cell *cells;

  private:
    /** Width of the row. */
    unsigned width;

    /** Attributes of the row. */
    Attributes attributes;
  };

} // namespace Putty

#endif // PUTTY_LINE_HH_INCLUDE
