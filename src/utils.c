//
// utils.c
//

#include "utils.h"
#include <string.h>

void string_copy(char *dest, const char *src, int max_len)
{
#ifdef _WIN32
  strncpy_s(dest, max_len, src, _TRUNCATE);
#else
  strncpy(dest, src, max_len);
#endif
}
