#ifndef PUTTY_WINSTUFF_H
#define PUTTY_WINSTUFF_H

#include <windows.h>
#include <stdio.h>		       /* for FILENAME_MAX */

#include "charset.h"

struct Filename {
    char path[FILENAME_MAX];
};

struct FontSpec {
    char name[64];
    int isbold;
    int height;
    int charset;
};

typedef void *Context;                 /* FIXME: probably needs changing */

#define SEL_NL { 13, 10 }

#define TICKSPERSEC 1000	       /* GetTickCount returns milliseconds */
#define CURSORBLINK GetCaretBlinkTime()
#define DEFAULT_CODEPAGE CP_ACP

#define GETTICKCOUNT GetTickCount

/*
 * Exports from unicode.c.
 */
struct unicode_data;
int init_ucs(struct unicode_data *ucsdata, const char *line_codepage,
             int utf8_override, int font_charset, int vtmode);

#endif
