#include "putty/state.hh"
#include "putty/row.hh"

#include <sstream>
#include <stdio.h>

using namespace Putty;

State::State()
  : width(0),
    height(0),
    buffer_size(0),
    alternate_screen(false),
    cursor_enabled(false),
    cursor_x(0),
    cursor_y(0),
    scroll_depth(0)
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
    rows(other.rows),
    palette(other.palette),
    scroll_depth(other.scroll_depth)
{
}

State &
State::operator=(const State &other)
{
  State tmp(other);
  tmp.swap(*this);
  return *this;
}

long long
State::get_scroll_depth() const
{
  return scroll_depth;
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
  std::swap(scroll_depth, other.scroll_depth);
}

State::~State()
{
}

bool
State::is_valid_row_value(int row) const
{
  return row >= -(int)(buffer_size) && row < (int)height;
}

bool
State::is_valid_cell(int row, unsigned column) const
{
  return is_valid_row_value(row) && column < width;
}

const Cell *
State::get_cell(int row, unsigned col) const
{
  return this->is_valid_cell(row, col) ? &get_row(row)->cells[col] : 0;
}

Cell *
State::get_cell(int row, unsigned col)
{
  return is_valid_cell(row, col) ? &get_row(row)->cells[col] : 0;
}

const Row *
State::get_row(int row) const
{
  return is_valid_row_value(row) ? &rows[row + buffer_size] : 0;
}

void
State::clear_changed() const
{
  printf("XXX clear changed %p\n", this);
  for (unsigned i = 0; i < rows.size(); ++i)
    {
      rows[i].clear_changed();
    }
}

void
State::scroll(int count)
{
  if (count <= 0)
    return;

  Row row;
  row.set_width(width);

  rows = std::vector<Row>(rows.begin() + count, rows.end());

  for (int i=0; i<count; ++i)
    rows.push_back(row);

  scroll_depth += count;
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
  return is_valid_row_value(row) ? &rows[row + buffer_size] : 0;
}

void
State::resize(unsigned a_width, unsigned a_height, unsigned a_buffer_size)
{
  printf("Resize request: %u %u %u\n", a_width, a_height, a_buffer_size);
  // If the dimensions don't change, leave this alone
  if (a_width == width && height == a_height && buffer_size == a_buffer_size)
    return;

  std::vector< Row > new_rows;
  printf("Resizing from %u %u %u\n", width, height, buffer_size);
  for (int i = -a_buffer_size; i < (int)a_height; ++i)
    {
      Row row = is_valid_row_value(i) ? rows[i + buffer_size] : Row();
      row.set_width(a_width);

      new_rows.push_back(row);
    }

  height = a_height;
  width = a_width;
  buffer_size = a_buffer_size;

  rows = new_rows;
}
