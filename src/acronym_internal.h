#ifndef ACRONYM_H
#define ACRONYM_H

/**
 * \brief   Utility function to shift char pointer right until first alphanumeric character
 *          or end of the line
 * \param   phrase  the char pointer to start
 * \return          pointer to the next word
 */
static const char * findNextWord(const char * phrase);

/**
 * \brief   Non-alpha character shall be considered as part of word, not delimiter
 *
 * For larger exception lists trade-off speed for size:
 * const char exceptions[256] = {0,0,0,...1,1,...0}
 * return exceptions[x];
 *
 * \param   x   character
 * \return      1 if exception char, 0 otherwise
 */
static int isExceptionCharacter(char x);

/**
 * \brief   Utility function to shift char pointer right until non-aphanumeric char
 *          or end of the line
 *
 * \param   phrase  the char pointer to start
 * \return          pointer to the next non-alpha
 */
static const char * skipWord(const char * phrase);

#endif
