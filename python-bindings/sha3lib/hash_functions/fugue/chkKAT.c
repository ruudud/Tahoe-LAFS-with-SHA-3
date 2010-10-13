
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "SHA3api_ref.h"
#include "fugue.h"

#define MAX_MARKER_LEN          50
#define SUBMITTER_INFO_LEN      128

typedef enum { KAT_SUCCESS = 0, KAT_FILE_OPEN_ERROR = 1, KAT_HEADER_ERROR = 2, KAT_DATA_ERROR = 3, KAT_HASH_ERROR = 4 } STATUS_CODES;

STATUS_CODES    chkTestTable(char *td, int hashbitlen, int numtables);
STATUS_CODES    chkTestHash(char *td, char *tn, int hashbitlen);
STATUS_CODES    chkTestRepeat(char *td, char *tn, int hashbitlen);
STATUS_CODES    chkMonteCarlo(char *td, char *tn, int hashbitlen);
int             FindMarker(FILE *infile, const char *marker);
int             ReadHex(FILE *infile, BitSequence *A, int Length, char *str);
void            fprintBstr(FILE *fp, char *S, BitSequence *A, int L);

int
main (int argc, char* argv[])
{
  int             i, ret_val,  bitlens[] = { 224, 256, 384, 512, 0 };
  int             j,           tables[] = { 1, 2, 4, 8, 16, 0 };
  int             all = 0, fast = 0;

  for (i=1;i<argc;i++)
    {
      if (!strcmp(argv[i],"-a")) all = 1;
      if (!strcmp(argv[i],"-s")) fast = 1;
    }
  for ( i=0; bitlens[i]; i++ ) for ( j=0; tables[j]; j++ ) {
      if ( (ret_val = chkTestTable(TEST_DIR"TST_KAT", bitlens[i], tables[j])) != KAT_SUCCESS )
        return ret_val;
    }

  for ( i=0; bitlens[i]; i++ ) {
    if (fast || all)
      {
        if ( (ret_val = chkTestHash(TEST_DIR"KAT_MCT", "ShortMsg", bitlens[i])) != KAT_SUCCESS )
          return ret_val;
        if ( (ret_val = chkMonteCarlo(TEST_DIR"KAT_MCT", "MonteCarlo", bitlens[i])) != KAT_SUCCESS )
          return ret_val;
      }
    if (all)
      {
        if ( (ret_val = chkTestHash(TEST_DIR"KAT_MCT", "LongMsg", bitlens[i])) != KAT_SUCCESS )
          return ret_val;
        if ( (ret_val = chkTestRepeat(TEST_DIR"KAT_MCT", "ExtremelyLongMsg", bitlens[i])) != KAT_SUCCESS )
          return ret_val;
      }
  }

  return KAT_SUCCESS;
}

STATUS_CODES
chkTestTable(char *td, int hashbitlen, int numtables)
{
#define TN "TestTable"
  char            fn[64];
  int             msglen, msgbytelen, msgwordlen, hashbytelen, hashwordlen, done, passes, errors;
  BitSequence     Msg[4288], IV[64], MD[64], Exp[64];
  FILE            *fp_in;
  hashState       state;

  sprintf(fn, "%s/Test_%dTableKAT_%d.txt", td, numtables, hashbitlen);
  if ( (fp_in = fopen(fn, "r")) == NULL )
    {
      printf("Couldn't open <%s> for read\n", fn);
      return KAT_FILE_OPEN_ERROR;
    }
  hashbytelen = (hashbitlen+7)/8;
  hashwordlen = (hashbytelen+3)/4;

  done = 0;
  passes = 0;
  errors = 0;
  do
    {
      if ( FindMarker(fp_in, "Len = ") )
        fscanf(fp_in, "%d", &msglen);
      else {
        done = 1;
        break;
      }
      msgbytelen = (msglen+7)/8;
      msgwordlen = (msgbytelen+3)/4;
      passes++;

      if ( !ReadHex(fp_in, IV, hashbytelen, "IV = ") ) {
        printf("ERROR: unable to read 'IV' from <%s>\n", fn);
        return KAT_DATA_ERROR;
      }

      if ( !ReadHex(fp_in, Msg, msgbytelen, "Msg = ") ) {
        printf("ERROR: unable to read 'Msg' from <%s>\n", fn);
        return KAT_DATA_ERROR;
      }

      if ( !ReadHex(fp_in, Exp, hashbytelen, "MD = ") ) {
        printf("ERROR: unable to read 'MD' from <%s>\n", fn);
        return KAT_DATA_ERROR;
      }

      if ( !Load_Fugue(&state, hashbitlen, (uint32*)IV, hashwordlen) ) {
        printf("Load_Fugue FAILED in chk"TN"\n");
        return KAT_HASH_ERROR;
      }
      if ( !Next_Fugue(&state, (uint32*)Msg, msgwordlen) ) {
        printf("Next_Fugue FAILED in chk"TN"\n");
        return KAT_HASH_ERROR;
      }
      if ( !Done_Fugue(&state, (uint32*)MD, &hashwordlen) ) {
        printf("Done_Fugue FAILED in chk"TN"\n");
        return KAT_HASH_ERROR;
      }
      hashbytelen = hashwordlen*4;

      if (memcmp (Exp, MD, hashbytelen))
        {
          fprintf(stdout, "Subtest %d FAILED from <%s>\n", passes, fn);
          fprintf(stdout, "Len = %d\n", msglen);
          fprintBstr(stdout, "IV  = ", IV, hashbytelen);
          fprintBstr(stdout, "Msg = ", Msg, msgbytelen);
          fprintBstr(stdout, "Exp = ", Exp, hashbytelen);
          fprintBstr(stdout, "MD  = ", MD, hashbytelen);
          errors++;
          return KAT_HASH_ERROR;
        }
    } while (!done);

  printf("finished "IMPL_NAME" "TN"KAT tests for Fugue-%d and %d tables with %d subtests\n", hashbitlen, numtables, passes);

  fclose(fp_in);

  return KAT_SUCCESS;
#undef  TN
}

STATUS_CODES
chkTestHash(char *td, char *tn, int hashbitlen)
{
  char            fn[64];
  int             msglen, msgbytelen, hashbytelen, done, passes, errors;
  BitSequence     Msg[4288], MD[64], Exp[64];
  FILE            *fp_in;

  sprintf(fn, "%s/%sKAT_%d.txt", td, tn, hashbitlen);
  if ( (fp_in = fopen(fn, "r")) == NULL ) {
    printf("Couldn't open <%s> for read\n", fn);
    return KAT_FILE_OPEN_ERROR;
  }
  hashbytelen = (hashbitlen+7)/8;

  done = 0;
  passes = 0;
  errors = 0;
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

      Hash(hashbitlen, Msg, msglen, MD);

      if (memcmp (Exp, MD, hashbytelen))
        {
          fprintf(stdout, "Subtest %d FAILED from <%s>\n", passes, fn);
          fprintf(stdout, "Len = %d\n", msglen);
          fprintBstr(stdout, "Msg = ", Msg, msgbytelen);
          fprintBstr(stdout, "Exp = ", Exp, hashbytelen);
          fprintBstr(stdout, "MD  = ", MD, hashbytelen);
          errors++;
          return KAT_HASH_ERROR;
        }
    } while ( !done );

  printf("finished "IMPL_NAME" %sKAT tests for Fugue-%d with %d subtests\n", tn, hashbitlen, passes);

  fclose(fp_in);

  return KAT_SUCCESS;
}

STATUS_CODES
chkTestRepeat(char *td, char *tn, int hashbitlen)
{
  char            fn[64];
  BitSequence     Text[65], MD[64], Exp[64];
  int             hashbytelen, errors;
  int             i, repeat;
  FILE            *fp_in;
  hashState       state;
  HashReturn      retval;

  sprintf(fn, "%s/%sKAT_%d.txt", td, tn, hashbitlen);
  if ( (fp_in = fopen(fn, "r")) == NULL ) {
    printf("Couldn't open <%s> for read\n", fn);
    return KAT_FILE_OPEN_ERROR;
  }
  hashbytelen = (hashbitlen+7)/8;

  errors = 0;

  if ( FindMarker(fp_in, "Repeat = ") )
    fscanf(fp_in, "%d", &repeat);
  else {
    printf("ERROR: unable to read 'Repeat' from <%s>\n", fn);
    return KAT_DATA_ERROR;
  }

  if ( FindMarker(fp_in, "Text = ") )
    fscanf(fp_in, "%s", Text);
  else {
    printf("ERROR: unable to read 'Text' from <%s>\n", fn);
    return KAT_DATA_ERROR;
  }

  if ( !ReadHex(fp_in, Exp, hashbytelen, "MD = ") ) {
    printf("ERROR: unable to read 'MD' from <%s>\n", fn);
    return KAT_DATA_ERROR;
  }

  if ( (retval = Init(&state, hashbitlen)) != KAT_SUCCESS ) {
    printf("Init returned <%d> in chk%s\n", retval, tn);
    return KAT_HASH_ERROR;
  }
  for ( i=0; i<repeat; i++ )
    if ( (retval = Update(&state, Text, 512)) != KAT_SUCCESS ) {
      printf("Update returned <%d> in chk%s\n", retval, tn);
      return KAT_HASH_ERROR;
    }
  if ( (retval = Final(&state, MD)) != KAT_SUCCESS ) {
    printf("Final returned <%d> in chk%s\n", retval, tn);
    return KAT_HASH_ERROR;
  }

  if (memcmp (Exp, MD, hashbytelen))
    {
      fprintf(stdout, "Subtest 1 FAILED from <%s>\n", fn);
      fprintf(stdout, "Repeat = %d\n", repeat);
      fprintf(stdout, "Text = %s\n", Text);
      fprintBstr(stdout, "Exp = ", Exp, hashbytelen);
      fprintBstr(stdout, "MD  = ", MD, hashbytelen);
      errors++;
      return KAT_HASH_ERROR;
    }

  printf("finished "IMPL_NAME" %sKAT tests for Fugue-%d\n", tn, hashbitlen);

  fclose(fp_in);

  return KAT_SUCCESS;
}

STATUS_CODES
chkMonteCarlo(char *td, char *tn, int hashbitlen)
{
  char            fn[64];
  BitSequence     Seed[128], Msg[128], MD[64], Exp[64], Temp[128];
  int             i, j, bytelen, done, errors;
  FILE            *fp_in;

  sprintf(fn, "%s/%s_%d.txt", td, tn, hashbitlen);
  if ( (fp_in = fopen(fn, "r")) == NULL ) {
    printf("Couldn't open <%s> for read\n", fn);
    return KAT_FILE_OPEN_ERROR;
  }
  bytelen = (hashbitlen+7)/8;

  if ( !ReadHex(fp_in, Seed, 128, "Seed = ") ) {
    printf("ERROR: unable to read 'Seed' from <%s>\n", fn);
    return KAT_DATA_ERROR;
  }
  memcpy(Msg, Seed, 128);

  done = 0;
  errors = 0;
  do
    {
      if ( FindMarker(fp_in, "j = ") )
        fscanf(fp_in, "%d", &j);
      else {
        done = 1;
        break;
      }

      if ( !ReadHex(fp_in, Exp, bytelen, "MD = ") ) {
        printf("ERROR: unable to read 'MD' from <%s>\n", fn);
        return KAT_DATA_ERROR;
      }

      for ( i=0; i<1000; i++ )
        {
          Hash(hashbitlen, Msg, 1024, MD);
          memcpy(Temp, Msg, 128-bytelen);
          memcpy(Msg, MD, bytelen);
          memcpy(Msg+bytelen, Temp, 128-bytelen);
        }

      if (memcmp (Exp, MD, bytelen))
        {
          fprintf(stdout, "Subtest %d FAILED from <%s>\n", j, fn);
          fprintf(stdout, "j = %d\n", j);
          fprintBstr(stdout, "Exp = ", Exp, bytelen);
          fprintBstr(stdout, "MD  = ", MD, bytelen);
          errors++;
          return KAT_HASH_ERROR;
        }
    } while ( !done );

  printf("finished "IMPL_NAME" %sKAT tests for Fugue-%d with %d subtests\n", tn, hashbitlen, j+1);

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
