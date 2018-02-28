#include "putty/row.hh"

#include <stdio.h>

using namespace Putty;

Row::Row()
  : cells(0),
    width(0),
    attributes(0)
{
}

Row::Row(const Row &other)
  : cells(0),
    width(other.width),
    attributes(other.attributes)
{
  if (other.width > 0)
    {
      cells = new Cell[width];
      for (unsigned i = 0; i < width; ++i)
        {
          cells[i] = other.cells[i];
        }
    }
}

Row::~Row()
{
  clear();
}

Row &
Row::operator=(const Row &other)
{
  Row tmp(other);
  tmp.swap(*this);
  return *this;
}

void
Row::clear_changed()
{
  Cell *cell = cells;
  for (int cell_pos = 0; cell_pos < get_width(); ++cell_pos)
    {
      cell->set_changed(false);
      ++cell;
    }
}

void
Row::swap(Row &other)
{
  std::swap(width, other.width);
  std::swap(attributes, other.attributes);
  std::swap(cells, other.cells);
}

const Cell *
Row::get_cell(unsigned col) const
{
  return col < width ? &cells[col] : 0;
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

bool
Row::set_cell(unsigned col, const std::wstring &characters, Cell::Attributes attr)
{
  if (col >= width)
    return false;

  cells[col].set(characters, attr);
  return true;
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
