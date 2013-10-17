#include "putty/row.hh"
#include "putty/exception.hh"

using namespace Putty;

Row::Row()
  : cells(0),
    width(0),
    attributes(0)
{
}

Row::Row(const Row &other)
  : cells(0),
    width(0),
    attributes(0)
{
  *this = other;
}

Row::~Row()
{
  clear();
}

Row &
Row::operator=(const Row &other)
{
  clear();

  if (other.width != 0)
    {
      width = other.width;
      cells = new Cell[width];
      for (unsigned i = 0; i < width; ++i)
        cells[i] = other.cells[i];
    }

  attributes = other.attributes;

  return *this;
}

const Cell &
Row::get_cell(unsigned col) const
{
  return cells[col];
}

void
Row::set_width(unsigned width)
{
  if (width == 0)
    {
      clear();
      return;
    }

  Cell *new_cells = new Cell[width];
  int copy_width = std::min(width, this->width);

  for (int i = 0; i < copy_width; ++i)
    new_cells[i] = cells[i];

  this->width = width;
  delete [] cells;
  cells = new_cells;
}

void
Row::set_cell(unsigned col, const std::wstring &characters, Cell::Attributes attr)
{
  cells[col].set(characters, attr);
}

void
Row::set_attributes(Attributes attr)
{
  attributes = attr;
}

void
Row::clear()
{
  width = 0;
  if (cells)
    {
      delete [] cells;
      cells = 0;
    }
}
