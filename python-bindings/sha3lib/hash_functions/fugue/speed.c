
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "SHA3api_ref.h"

#define MAX_MARKER_LEN          50
#define SUBMITTER_INFO_LEN      128

typedef enum { KAT_SUCCESS = 0, KAT_FILE_OPEN_ERROR = 1, KAT_HEADER_ERROR = 2, KAT_DATA_ERROR = 3, KAT_HASH_ERROR = 4 } STATUS_CODES;

STATUS_CODES    chkSpeedHash(char *td, char *tn, int hashbitlen, int repeat_count);
int             FindMarker(FILE *infile, const char *marker);
int             ReadHex(FILE *infile, BitSequence *A, int Length, char *str);
void            fprintBstr(FILE *fp, char *S, BitSequence *A, int L);

int
main (int argc, char* argv[])
{
  int     i, ret_val,  bitlens[] = { 224, 256, 384, 512, 0 };
  int     all = 0, fast = 0;

  for (i=1;i<argc;i++)
    {
      if (!strcmp(argv[i],"-a")) all = 1;
      if (!strcmp(argv[i],"-s")) fast = 1;
    }

  for ( i=0; bitlens[i]; i++ )
    {
      if ( (ret_val = chkSpeedHash(TEST_DIR"KAT_MCT", "ShortMsg", bitlens[i], 10000)) != KAT_SUCCESS )
        return ret_val;
    }

  return KAT_SUCCESS;
}

STATUS_CODES
chkSpeedHash(char *td, char *tn, int hashbitlen, int repeat_count)
{
  clock_t         elapsed;
  int             i;
  char            fn[64];
  int             msglen, msgbytelen, hashbytelen, done, passes, errors, prev_msgbytelen;
  BitSequence     Msg[160000], MD[64], Exp[64];
  FILE            *fp_in;

  sprintf(fn, "%s/%sKAT_%d.txt", td, tn, hashbitlen);
  if ( (fp_in = fopen(fn, "r")) == NULL ) {
    printf("Couldn't open <%s> for read\n", fn);
    return KAT_FILE_OPEN_ERROR;
  }
  hashbytelen = (hashbitlen+7)/8;

  printf("Performing "IMPL_NAME" %sKAT speed tests for Fugue-%d:\n", tn, hashbitlen);

  done = 0;
  passes = 0;
  errors = 0;
  prev_msgbytelen =-1;
  do
    {
      if ( FindMarker(fp_in, "Len = ") )
        fscanf(fp_in, "%d", &msglen);
      else {
        done = 1;
        break;
      }
      msgbytelen = (msglen+7)/8;
      passes++;

      if ( !ReadHex(fp_in, Msg, msgbytelen, "Msg = ") ) {
        printf("ERROR: unable to read 'Msg' from <%s>\n", fn);
        return KAT_DATA_ERROR;
      }

      if ( !ReadHex(fp_in, Exp, hashbytelen, "MD = ") ) {
        printf("ERROR: unable to read 'MD' from <%s>\n", fn);
        return KAT_DATA_ERROR;
      }
	
      // patched to increase the length of the message
      if (msgbytelen > prev_msgbytelen+4)
        {
          elapsed = -clock();
          for (i=0; i< repeat_count; i++)
            Hash(hashbitlen, Msg, msglen*64, MD);
          elapsed += clock();

          fprintf(stdout, "finished "IMPL_NAME" Fugue-%d Msg byte Len = %d, Speed = %.1f MByte/sec\n",
                  hashbitlen, msgbytelen*64,
                  (float) msgbytelen*64*((float)((float) repeat_count*CLOCKS_PER_SEC/1000000)/elapsed));
		
          prev_msgbytelen = msgbytelen;	
        }

    } while ( !done );

  printf("Completed "IMPL_NAME" %sKAT speed tests for Fugue-%d with %d subtests\n", tn, hashbitlen, passes);

  fclose(fp_in);

  return KAT_SUCCESS;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
FindMarker(FILE *infile, const char *marker)
{
  char    line[MAX_MARKER_LEN];
  int             i, len;

  len = (int)strlen(marker);
  if ( len > MAX_MARKER_LEN-1 )
    len = MAX_MARKER_LEN-1;

  for ( i=0; i<len; i++ )
    if ( (line[i] = fgetc(infile)) == EOF )
      return 0;
  line[len] = '\0';

  while ( 1 ) {
    if ( !strncmp(line, marker, len) )
      return 1;

    for ( i=0; i<len-1; i++ )
      line[i] = line[i+1];
    if ( (line[len-1] = fgetc(infile)) == EOF )
      return 0;
    line[len] = '\0';
  }

  // shouldn't get here
  return 0;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
ReadHex(FILE *infile, BitSequence *A, int Length, char *str)
{
  int                     i, ch, started;
  BitSequence     ich=0;

  if ( Length == 0 ) {
    A[0] = 0x00;
    return 1;
  }
  memset(A, 0x00, Length);
  started = 0;
  if ( FindMarker(infile, str) )
    while ( (ch = fgetc(infile)) != EOF ) {
      if ( !isxdigit(ch) ) {
        if ( !started ) {
          if ( ch == '\n' )
            break;
          else
            continue;
        }
        else
          break;
      }
      started = 1;
      if ( (ch >= '0') && (ch <= '9') )
        ich = ch - '0';
      else if ( (ch >= 'A') && (ch <= 'F') )
        ich = ch - 'A' + 10;
      else if ( (ch >= 'a') && (ch <= 'f') )
        ich = ch - 'a' + 10;

      for ( i=0; i<Length-1; i++ )
        A[i] = (A[i] << 4) | (A[i+1] >> 4);
      A[Length-1] = (A[Length-1] << 4) | ich;
    }
  else
    return 0;

  return 1;
}

void
fprintBstr(FILE *fp, char *S, BitSequence *A, int L)
{
  int             i;

  fprintf(fp, "%s", S);

  for ( i=0; i<L; i++ )
    fprintf(fp, "%02X", A[i]);

  if ( L == 0 )
    fprintf(fp, "00");

  fprintf(fp, "\n");
}
