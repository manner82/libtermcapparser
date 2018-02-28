#include <string.h>

#include "putty/cell.hh"
#include <stdio.h>

using namespace Putty;

const Cell::Attributes Cell::FlagMask = 0x00FC0000U;
const Cell::Attributes Cell::FgColorMask = 0x0001FFU;
const int Cell::FgColorShift = 0;
const Cell::Attributes Cell::BgColorMask = 0x03FE00U;
const int Cell::BgColorShift = 9;
const Cell::Attributes Cell::InvalidColor = 0x03FFFFU;
const Cell::Attributes Cell::ValidMask = Cell::FlagMask | Cell::BgColorMask | Cell::FgColorMask;
const Cell::Color Cell::DefaultForeground = 256 + Cell::DEFAULT_FOREGROUND;
const Cell::Color Cell::DefaultBackground = 256 + Cell::DEFAULT_BACKGROUND;
const Cell::Attributes Cell::DefaultAttributes = (Cell::DefaultForeground << Cell::FgColorShift) |
    (Cell::DefaultBackground << Cell::BgColorShift);


Cell::Cell()
  : attr(Cell::DefaultAttributes),
    changed(true)
{
  set_changed(true);
}

Cell::Cell(const std::wstring &characters, Attributes attr)
  : changed(true)
{
  set(characters, attr);
  set_changed(true);
}

Cell::Cell(const Cell &other)
  : characters(other.characters),
    attr(other.attr),
    changed(other.changed)
{
}

Cell &
Cell::operator=(const Cell &other)
{
  characters = other.characters;
  attr = other.attr;
  changed = other.changed;
  return *this;
}

void
Cell::set(const std::wstring &characters, Attributes attr)
{
  set_characters(characters);
  set_attributes(attr);
}

void
Cell::set_characters(const std::wstring &characters)
{
  if (get_characters() != characters)
    {
      set_changed(true);
    }

  this->characters = characters;
}

void
Cell::set_attributes(Cell::Attributes attributes)
{
  this->attr = attributes & ValidMask;
}

void
Cell::set_changed(bool is_changed)
{
  changed = is_changed;
}

bool
Cell::is_changed() const
{
  return changed;
}
