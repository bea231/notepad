/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "viewbuf.h"

const unsigned char notepad::viewbuf::defaultText[] = "File not found!";

/* Initialite buffer from file function */
int notepad::viewbuf::Open( unsigned char *fileName )
{
  FILE *textFile = NULL;

  buffer = NULL;  
  size = stringsCount = currentString = currentCharacter = currentIndex = nextIndex = beginIndex = 0;

  if (fileName != NULL)
    textFile = fopen((char *)fileName, "rt");
  if (textFile == NULL)
  {
    /* Default text value */
    maxStringLength = size = strlen((char *)notepad::viewbuf::defaultText);    
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * (size + 1));
    strncpy((char *)buffer, (char *)notepad::viewbuf::defaultText, size);

    buffer[size] = 0;
    ++size;
    stringsCount = 1;
    return 0;
  }
  /* Calculate file length */
  fseek(textFile, 0, SEEK_END);
  size = ftell(textFile);
  fseek(textFile, 0, SEEK_SET);

  /* Allocate memory and read text */
  buffer = (unsigned char *)malloc(sizeof(char) * size);
  memset(buffer, 0, sizeof(char) * size);
  if (buffer == NULL)
  {
    fclose(textFile);
    textFile = NULL;
    return 0;
  }  
  fread((void *)buffer, size, 1, textFile);
  ++size;
  for (unsigned long i = 0; i < size; i++)
    if (buffer[i] == '\n')
      stringsCount++;
    
  fclose(textFile);

  /* Calculate maximum string length */
  unsigned char *ptr1, *ptr2;

  ptr1 = Begin();
  ptr2 = End();
  maxStringLength = ptr2 - ptr1;
  while (HaveStrings())
  {
    ptr1 = Next();
    ptr2 = End();
    if ((ptr2 - ptr1) > (int)maxStringLength)
      maxStringLength = ptr2 - ptr1;
  }
  return 1;
}

/* Deinitialite buffer function */
void notepad::viewbuf::Close( void )
{
  if (buffer)
  {
    free(buffer);
    buffer = NULL;
    size = 0;
  }
}

/* Get pointer to begin of first string of 'visible' buffer function */
unsigned char * notepad::viewbuf::Begin( void )
{
  nextIndex = beginIndex;
  return Next();
}

/* Get pointer to begin of next string of 'visible' buffer function */
unsigned char * notepad::viewbuf::Next( void )
{
  currentIndex = nextIndex;
  while (buffer[nextIndex] != '\n' && nextIndex < size - 1)
    nextIndex++;
  if ((nextIndex - currentIndex) > currentCharacter)
    return buffer + currentIndex + currentCharacter;
  else
    return NULL;
}

/* Get pointer to end of string of 'visible' buffer function */
unsigned char * notepad::viewbuf::End( void )
{
  if ((nextIndex++ - currentIndex) > currentCharacter)
    return buffer + nextIndex - 1;
  else
    return NULL;
}

void notepad::viewbuf::ShiftX( long shift )
{
  if (((long)currentCharacter + shift) < 0)
  {
    shift = -(long)currentCharacter;
    currentCharacter = 0;
    return;
  }
  else if ((currentCharacter + shift) >= maxStringLength - breakScrollX)
  {
    shift = maxStringLength - currentCharacter - breakScrollX;
    currentCharacter = maxStringLength - breakScrollX;
    return;
  }
  currentCharacter += shift;
}

/* Vertical shift text function */
void notepad::viewbuf::ShiftY( long shift )
{
  if (((long)currentString + shift) < 0)
  {
    shift = -(long)currentString;
    currentString = 0;
  }
  else if ((currentString + shift) >= stringsCount - breakScrollY)
  {
    shift = stringsCount - breakScrollY - currentString;
    currentString = stringsCount - breakScrollY;
  }
  else
    currentString += shift;

  while (shift-- > 0)
  {
    while (buffer[beginIndex] != '\n' && beginIndex < size)
      beginIndex++;
    ++beginIndex;
  }
  ++shift;
  while (shift++ < 0)
  {
    beginIndex -= 2;
    while (buffer[beginIndex] != '\n' && beginIndex > 0)
      beginIndex--;
    beginIndex += beginIndex != 0;
  }
}
