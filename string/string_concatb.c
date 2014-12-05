#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "string.h"

bool
string_concatb(struct string* s, const char* sta, uintptr_t len)
{
    uintptr_t growby;
    char* buf;

    if (len > (s->size - s->length)) {
        growby = s->growby;
        while ((s->size + growby - s->length) < len) {
            growby += s->growby;
            if ((s->size + growby) < s->size) return false;
        }
        buf = realloc(s->s, s->size + growby);
        memset(buf+s->size, 0, growby);
        if (!buf) return false;
        s->size += growby;
        s->s = buf;
    }
    memcpy(s->s + s->length, sta, len);
    s->length += len;
    return true;
}
