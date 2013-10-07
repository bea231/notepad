/* Sergeev Artemiy, 33602 (3057/2) */

#ifndef _VIEWBUF_H_
#define _VIEWBUF_H_

#include <stdio.h>

#define _FILE_ERR_TEXT "File not found"

namespace task2
{
  class viewbuf
  {
  private:
    FILE *TextFile;
    char *TextBuf;
    unsigned long shift_x, shift_y,
                  shift_index,
                  cur_index,
                  next_index,
                  LinesCount,
                  TextBufSize;
  public:
    viewbuf( char *FileName = NULL );
    ~viewbuf( void );

    void Init( char *FileName = NULL );

    char * GetFirstBeginPtr( void );
    char * GetBeginPtr( void );
    char * GetEndPtr( void );
    bool HaveStrings( void ) const;
    void ShiftX( long shift = 0 );
    void ShiftY( long shift = 0 );
  };
}

#endif /* _VIEWBUF_H_ */