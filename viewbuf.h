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
    static const unsigned char defaultText[];

    unsigned char *buffer;          // text buffer
    unsigned long size,             // count of charater in buffer
                  currentString,    // number of current first string in buffer
                  currentCharacter, // number of current first character in string
                  beginIndex,       // index of first string
                  currentIndex,     // index of 'currentString'
                  nextIndex,        // index of string after 'currentString'
                  stringsCount,     // count of strings in 'buffer' ('\n' is stop-character)
                  maxStringLength;
  public:
    viewbuf( void ) : buffer(NULL), size(0), stringsCount(0),
        currentString(0), currentCharacter(0), currentIndex(0), nextIndex(0), beginIndex(0)
    {
    }

    ~viewbuf( void ) { Close(); }

    /* Initialite buffer from file function */
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

    /*** GetSmth() functions */ 
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