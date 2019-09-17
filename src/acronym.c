#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "acronym.h"
#include "acronym_internal.h"

static const char * findNextWord(const char * phrase)
{
    while (0 == isalpha(*phrase) && *phrase) {
        phrase++;
    }
    return phrase;
}

static int isExceptionCharacter(char x)
{
    int retval = 0; // Return 1 if the char is an exception, 0 otherwise
    if (x ==  '\'') retval = 1;
    return retval;
}

static const char * skipWord(const char * phrase)
{
    while (((0 != isalpha(*phrase)) || isExceptionCharacter(*phrase)) && *phrase) {
        phrase++;
    }
    return phrase;
}

extern char* abbreviate(const char* phrase)
{
    char * retval = NULL;
    int odx = 0; // Output index
    int phrase_len = 0xDEAD; // Non-initiated value

    if (phrase == NULL) {
        goto exit; // Return NULL as required in test case test_null_string
    }

    phrase_len = strlen(phrase);
    if (phrase_len < MIN_INPUT_LENGTH) {
        goto exit; // Return NULL if string is too short to be abbreviated
    }

    retval = (char*)calloc(phrase_len+1, sizeof(char));
    if (retval == NULL) {
        goto exit; // Return NULL if cannot allocate return (GCOV: Cannot reasonably test)
    }

    // Ready to start, skip possible prefix of non-alpha characters
    while(*phrase) {
        phrase = findNextWord(phrase);
        retval[odx++] = toupper(*phrase);
        phrase = skipWord(phrase);
    }
exit:
    if (retval && ((odx-1)<MIN_ABBREVIATION_LENGTH)) {
        // If abbreviation is too short to be meaningful, return NULL
        // as sign of failure to abbreviate
        free(retval);
        retval = NULL;
    }
    if ((REALLOCATE_RETURN_BUF>0) && retval && ((phrase_len - odx) > REALLOCATE_RETURN_BUF)) {
        // Allocated buffer has maximum length. If there are too much memory wasted,
        // try to reallocate the buffer with acronym's size
        char * reallocated = calloc(odx+1, sizeof(char));
        if (reallocated != NULL) {
            strcpy(reallocated, retval);
            free(retval);
            retval = reallocated;
        }
    }
    return retval;
}
