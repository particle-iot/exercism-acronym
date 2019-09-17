#ifndef ACRONYM_H
#define ACRONYM_H

#define MIN_INPUT_LENGTH 1          /*!< Minimal length of input can be abbreviated */
#define MIN_ABBREVIATION_LENGTH 1   /*!< Minimal meaningful length of abbreviation */
#define REALLOCATE_RETURN_BUF   4   /*!< Reallocation threshold, set to 0 if no reallocation */

/** \brief abbreviate returns capitalized first letters of the words found in phrase
 *
 * Function return NULL as sign of failure:
 * - NULL input
 * - Too short or empty input
 * - Memory allocation failure
 * - Too short abbreviation
 *
 * \param   phrase  Phrase to abbreviate
 * \return          Abbreviation of NULL in case of fail
 */
char* abbreviate(const char* phrase);

#endif
