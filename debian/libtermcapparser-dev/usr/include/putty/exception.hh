#ifndef PUTTY_EXCEPTION_HH_INCLUDE
#define PUTTY_EXCEPTION_HH_INCLUDE

#include <exception>

namespace Putty
{

  /**
   * The range of a request is out of bounds.
   */
  class RangeException : public std::exception
  {
  public:
    /**
     * Get exception message.
     */
    virtual const char *what() const throw();
  };

} // namespace

#endif // PUTTY_EXCEPTION_HH_INCLUDE
