#include "putty/state.hh"
#include "putty/row.hh"

#include <sstream>

using namespace Putty;

State::State()
  : width(0),
    height(0),
    buffer_size(0),
    alternate_screen(false),
    cursor_enabled(false),
    cursor_x(0),
    cursor_y(0),
    rows(0)
{
}

State::State(const State &other)
  : width(other.width),
    height(other.height),
    buffer_size(other.buffer_size),
    alternate_screen(other.alternate_screen),
    cursor_enabled(other.cursor_enabled),
    cursor_x(other.cursor_x),
    cursor_y(other.cursor_y),
    rows(0),
    palette(other.palette)
{
  rows = new Row[height + buffer_size];
  for (unsigned row = 0; row < (height + buffer_size); ++row)
    rows[row] = other.rows[row];
}

State &
State::operator=(const State &other)
{
  State tmp(other);
  tmp.swap(*this);
  return *this;
}

void
State::swap(State &other)
{
  std::swap(width, other.width);
  std::swap(height, other.height);
  std::swap(buffer_size, other.buffer_size);
  std::swap(alternate_screen, other.alternate_screen);
  std::swap(cursor_enabled, other.cursor_enabled);
  std::swap(cursor_x, other.cursor_x);
  std::swap(cursor_y, other.cursor_y);
  std::swap(palette, other.palette);
  std::swap(rows, other.rows);
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

bool
State::is_valid_cell(int row, unsigned column) const
{
  return !is_invalid_row_value(row) && column < width;
}

const Cell *
State::get_cell(int row, unsigned col) const
{
  return this->is_valid_cell(row, col) ? &rows[row + buffer_size].cells[col] : 0;
}

Cell *
State::get_cell(int row, unsigned col)
{
  return is_valid_cell(row, col) ? &rows[row + buffer_size].cells[col] : 0;
}

const Row *
State::get_row(int row) const
{
  return is_invalid_row_value(row) ? 0 : &rows[row + buffer_size];
}

bool
State::set_cell(int row, unsigned col, const std::wstring &characters, Cell::Attributes attr)
{
  if (!is_valid_cell(row, col))
    return false;

  rows[row + buffer_size].cells[col].set(characters, attr);
  return true;
}

void
State::set_alternate_screen(bool alternate_screen)
{
  this->alternate_screen = alternate_screen;
}

void
State::set_cursor(bool enabled, int x, int y)
{
  cursor_enabled = enabled;
  cursor_x = x;
  cursor_y = y;
}

Row *
State::get_row_internal(int row)
{
  return is_invalid_row_value(row) ? 0 : &rows[row + buffer_size];
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
