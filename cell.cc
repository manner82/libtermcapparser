#include <string.h>

#include "putty/cell.hh"
#include <stdio.h>

using namespace Putty;

const Cell::Attributes Cell::FlagMask = 0x00FC0000U;
const Cell::Attributes Cell::FgColorMask = 0x0001FFU;
const int Cell::FgColorShift = 0;
const Cell::Attributes Cell::BgColorMask = 0x03FE00U;
const int Cell::BgColorShift = 9;
static const Cell::Attributes ChangeMask = (1 << Cell::BgColorShift);
const Cell::Attributes Cell::InvalidColor = 0x03FFFFU;
const Cell::Attributes Cell::ValidMask = Cell::FlagMask | Cell::BgColorMask | Cell::FgColorMask;
const Cell::Color Cell::DefaultForeground = 256 + Cell::DEFAULT_FOREGROUND;
const Cell::Color Cell::DefaultBackground = 256 + Cell::DEFAULT_BACKGROUND;
const Cell::Attributes Cell::DefaultAttributes = (Cell::DefaultForeground << Cell::FgColorShift) |
    (Cell::DefaultBackground << Cell::BgColorShift);


Cell::Cell()
  : attr(Cell::DefaultAttributes),
    track(false)
{
  set_changed(true);
}

Cell::Cell(const std::wstring &characters, Attributes attr)
  : track(false)
{
  set(characters, attr);
  set_changed(true);
}

Cell::Cell(const Cell &other)
  : characters(other.characters),
    attr(other.attr),
    track(other.track)
{
}

Cell &
Cell::operator=(const Cell &other)
{
  characters = other.characters;
  attr = other.attr;
  track = other.track;
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
  this->attr = (attributes & ValidMask) | (this->attr & ChangeMask);
}

void
Cell::set_changed(bool is_changed)
{
  if (track)
    printf("Marking changed %p %d\n", this, is_changed);

  if (is_changed)
    {
      this->attr = this->attr | ChangeMask;
    }
  else
    {
      this->attr = this->attr & (~ChangeMask);
    }
}

bool
Cell::is_changed() const
{
  return this->attr & ChangeMask;
}
