#include <string.h>

#include "putty/cell.hh"

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
{}

Cell::Cell(const std::wstring &characters, Attributes attr)
{
  set(characters, attr);
}

Cell::Cell(const Cell &other)
  : characters(other.characters),
    attr(other.attr)
{}

Cell &
Cell::operator=(const Cell &other)
{
  characters = other.characters;
  attr = other.attr;
  return *this;
}

void
Cell::set(const std::wstring &characters, Attributes attr)
{
  this->characters = characters;
  this->attr = attr & ValidMask;
}
