/* Sergeev Artemiy, 33601/2 (3057/2) */

#ifndef _VIEWBUF_H_
#define _VIEWBUF_H_

#include <stdio.h>

/* Project namespace */
namespace notepad
{
  /* Specialized text buffer class */
  class viewbuf
  {
  private:
    static const unsigned char defaultText[];  // text, which will be displayed default (on error)

    unsigned char *buffer;          // text buffer
    unsigned long size,             // count of bytes of memory for buffer
                  currentString,    // number of current first-displayed string in buffer
                  currentCharacter, // number of current first-displayed character in string
                  beginIndex,       // index of first-displayed character
                  currentIndex,     // index of current displayed string
                  nextIndex,        // index of next displayed
                  stringsCount,     // count of strings in 'buffer' ('\n' is stop-character)
                  maxStringLength;  // length of max-string in buffer
  public:
    unsigned int  breakScrollX,     // Count of characters, which will be displayed in right-side position of scroll bar
                  breakScrollY;     // Count of characters, which will be displayed in bottom-side position of scroll bar

    viewbuf( void ) : buffer(NULL), size(0), stringsCount(0),
        currentString(0), currentCharacter(0), currentIndex(0), nextIndex(0), beginIndex(0),
        breakScrollX(15), breakScrollY(5)
    {
    }

    ~viewbuf( void ) { Close(); }

    /* Read text from file function */
    int Open( unsigned char *fileName = NULL );

    /* Deinitialite buffer function */
    void Close( void );

    /* Get pointer to begin of first string of 'visible' buffer function */
    unsigned char * Begin( void );

    /* Get pointer to begin of next string of 'visible' buffer function */
    unsigned char * Next( void );

    /* Get pointer to end of string of 'visible' buffer function */
    unsigned char * End( void );

    /* Check avalibility of strings to output function */
    bool HaveStrings( void ) const
    {
      return (currentIndex < size);
    }

    /* Horizontal shift text function */
    void ShiftX( const long shift );

    /* Vertical shift text function */
    void ShiftY( const long shift );

    /*** GetSmth() functions ***/

    unsigned long GetStringsCount( void ) const
    {
      return stringsCount;
    }

    unsigned long GetMaxStringLength( void ) const
    {
      return maxStringLength;
    }

    unsigned long GetCurrentString( void ) const
    {
      return currentString;
    }

    unsigned long GetCurrentCharacter( void ) const
    {
      return currentCharacter;
    }
  };
}

#endif /* _VIEWBUF_H_ */
