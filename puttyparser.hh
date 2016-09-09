#ifndef PUTTY_PUTTYPARSER_HH_INCLUDE
#define PUTTY_PUTTYPARSER_HH_INCLUDE

namespace Putty
{
  class TermcapParser;
}

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <putty.h>
#include <terminal.h>

/**
 * Internal PUTTY structure representing the frontend of the terminal.
 * In our case it is just a dummy.
 */
struct gui_data
{
  wchar_t *pastein_data;
  int pastein_data_len;
  int width, height;
  char wintitle[sizeof(((Config *)0)->wintitle)];
  char icontitle[sizeof(((Config *)0)->wintitle)];
  void *ldisc;
  Terminal *term;
  void *logctx;
  struct unicode_data ucsdata;
  Config cfg;

  Putty::TermcapParser *parser;
};

/* for library implementation */
/* Terminal object handlers */
Terminal *term_init(Config *mycfg, struct unicode_data *ucsdata,
                    void *frontend);
int term_data(Terminal *term, int is_stderr, const char *data, int len);
void term_size(Terminal *term, int newrows, int newcols, int newsavelines);
void term_update(Terminal *term);
void term_provide_logctx(Terminal *term, void *logctx);
/* Unicode support */
int init_ucs(struct unicode_data *ucsdata, const char *linecharset,
             int utf8_override, int font_charset, int vtmode);
/* memory allocation tools */
void *safemalloc(size_t n, size_t size);
void safefree(void *ptr);

int sblines(Terminal *term);

__END_DECLS

#endif // PUTTY_PUTTYPARSER_HH_INCLUDE
