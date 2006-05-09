/*  $Id: strlcat.c 5681 2002-08-29 04:07:50Z rra $
**
**  Replacement for a missing strlcat.
**
**  Written by Russ Allbery <rra@stanford.edu>
**  This work is hereby placed in the public domain by its author.
**
**  Provides the same functionality as the *BSD function strlcat, originally
**  developed by Todd Miller and Theo de Raadt.  strlcat works similarly to
**  strncat, except simpler.  The result is always nul-terminated even if the
**  source string is longer than the space remaining in the destination
**  string, and the total space required is returned.  The third argument is
**  the total space available in the destination buffer, not just the amount
**  of space remaining.
*/

#include <config.h>
#include <system.h>

/* If we're running the test suite, rename strlcat to avoid conflicts with
   the system version. */
#if TESTING
# define strlcat test_strlcat
size_t test_strlcat(char *, const char *, size_t);
#endif

size_t
strlcat(char *dst, const char *src, size_t size)
{
    size_t used, length, copy;

    used = strlen(dst);
    length = strlen(src);
    if (size > 0 && used < size - 1) {
        copy = (length >= size - used) ? size - used - 1 : length;
        memcpy(dst + used, src, copy);
        dst[used + copy] = '\0';
    }
    return used + length;
}