#include "putty/state.hh"
#include "putty/row.hh"

#include <sstream>

using namespace Putty;

State::State()
  : width(0),
    height(0),
    buffer_size(0),
    rows(0)
{
}

State::State(const State &other)
  : width(other.width),
    height(other.height),
    buffer_size(other.buffer_size),
    rows(0),
    palette(other.palette)
{
  rows = new Row[height + buffer_size];
  for (unsigned row = 0; row < (height + buffer_size); ++row)
    rows[row] = other.rows[row];
}

State::~State()
{
  if (rows)
    delete [] rows;
}

bool
State::is_invalid_row_value(int row) const
{
  return (rows == 0) || ((int)(row - height) >= 0 || (int)(row + buffer_size) < 0);
}

const Cell &
State::get_cell(int row, unsigned col) const
{
  return rows[row + buffer_size].cells[col];
}

Cell &State::get_cell(int row, unsigned col)
{
  return rows[row + buffer_size].cells[col];
}

const Row &
State::get_row(int row) const
{
  return rows[row + buffer_size];
}

void
State::set_cell(int row, unsigned col, const std::wstring &characters, Cell::Attributes attr)
{
  rows[row + buffer_size].cells[col].set(characters, attr);
}

Row &
State::get_row_internal(int row)
{
  return rows[row + buffer_size];
}

void
State::resize(unsigned a_width, unsigned a_height, unsigned a_buffer_size)
{
  // If the dimensions don't change, leave this alone
  if (a_width == width && height == a_height && buffer_size == a_buffer_size)
    return;

  Row *new_rows = new Row[a_height + a_buffer_size];

  for (int i = -a_buffer_size; i < (int)a_height; ++i)
    {
      // Copy lines from the original
      if (i >= -(int)buffer_size && i < (int)height)
        new_rows[i + a_buffer_size] = rows[i + buffer_size];

      new_rows[i + a_buffer_size].set_width(a_width);
    }

  height = a_height;
  width = a_width;
  buffer_size = a_buffer_size;

  delete [] rows;
  rows = new_rows;
}
