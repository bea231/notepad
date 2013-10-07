/* Sergeev Artemiy, 33602 (3057/2) */

#include <stdlib.h>
#include <string.h>
#include "viewbuf.h"

/* Default class constructor */
task2::viewbuf::viewbuf( char *FileName ) : TextFile(NULL), TextBuf(NULL), shift_x(0), shift_y(0), cur_index(0), shift_index(0)
{
  if (FileName != NULL)
    this->Init(FileName);
}

/* Class destructor */
task2::viewbuf::~viewbuf( void )
{
  if (TextBuf)
  {
    free(TextBuf);
    TextBuf = NULL;
  }
  if (TextFile)
  {
    fclose(TextFile);
    TextFile = NULL;
  }
}

/* Initialite buffer from file function */
void task2::viewbuf::Init( char *FileName )
{
  unsigned long len;

  if (FileName != NULL)
    TextFile = fopen(FileName, "rt");
  if (TextFile == NULL)
  {
    len = strlen(_FILE_ERR_TEXT);
    TextBuf = (char *)malloc(sizeof(char) * (len + 1));
    strncpy(TextBuf, _FILE_ERR_TEXT, len);
    TextBuf[len] = 0;
    TextBufSize = len + 1;
    LinesCount = 1;
    return;
  }
  fseek(TextFile, 0, SEEK_END);
  len = ftell(TextFile);
  fseek(TextFile, 0, SEEK_SET);

  TextBuf = (char *)malloc(sizeof(char) * (len + 1));
  memset(TextBuf, 0, sizeof(char) * (len + 1));
  if (TextBuf == NULL)
  {
    fclose(TextFile);
    TextFile = NULL;
    return;
  }
  fread((void *)TextBuf, len, 1, TextFile);
  TextBufSize = strlen(TextBuf);
  LinesCount = len - TextBufSize + 1;
  fclose(TextFile);
  TextFile = NULL;
}

/* Get pointer to begin of first string for output function */
char * task2::viewbuf::GetFirstBeginPtr( void )
{
  cur_index = next_index = shift_index;
  return GetBeginPtr();
}

/* Get pointer to begin of next string for output function */
char * task2::viewbuf::GetBeginPtr( void )
{
  cur_index = next_index;
  while (TextBuf[next_index] != '\n' && next_index < TextBufSize - 1)
    next_index++;
  if ((next_index - cur_index) > shift_x)
    return TextBuf + cur_index + shift_x;
  else
    return NULL;
}

/* Get pointer to end of next string for output function */
char * task2::viewbuf::GetEndPtr( void )
{
  if ((next_index++ - cur_index) > shift_x)
    return TextBuf + next_index - 1;
  else
    return NULL;
}

/* Check avalibility of strings to output function */
bool task2::viewbuf::HaveStrings( void ) const
{
  return (cur_index < TextBufSize);
}

/* Horizontal shift text function */
void task2::viewbuf::ShiftX( long shift )
{
  if ((shift_x += shift) < 0 || shift_x >= TextBufSize)
    shift_x -= shift;
}

/* Vertical shift text function */
void task2::viewbuf::ShiftY( long shift )
{
  if (((long)shift_y + shift) < 0)
  {
    shift = -(long)shift_y;
    shift_y = 0;
  }
  else if ((shift_y + shift) >= LinesCount - 3)
  {
    shift = LinesCount - 3 - shift_y;
    shift_y = LinesCount - 3;
  }
  else
    shift_y += shift;

  while (shift-- > 0)
  {
    while (TextBuf[shift_index] != '\n' && TextBuf[shift_index] != 0)
      shift_index++;
    ++shift_index;
  }
  ++shift;
  while (shift++ < 0)
  {
    shift_index -= 2;
    while (TextBuf[shift_index] != '\n' && shift_index > 0)
      shift_index--;
    shift_index += shift_index != 0;
  }
}