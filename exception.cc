#include "putty/exception.hh"

const char *
Putty::RangeException::what() const throw()
{
  return "Value out of range";
}
