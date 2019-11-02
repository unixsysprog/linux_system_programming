#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include <errno.h>

#define MATCH_CNT   4

int main(int argc, char *argv[])
{
  if(argc != 3)
    fprintf(stderr, "retester <pattern> <string>\n"); 
  
  char *pat = argv[1];
  char *str = argv[2];

  regex_t compreg;
  memset(&compreg, 0, sizeof(regex_t));

  regmatch_t matches[MATCH_CNT];
  memset(&matches, 0, MATCH_CNT*sizeof(regmatch_t));
  int matchcnt = -1;

  char *errbuff;
  
  printf("Trying to match with basic regex...\n");
  int compret = -2;
  if((compret = regcomp(&compreg, pat, 0)) == 0)
  {
    printf("Compiling successful.\n");
    int execret = -2; 
    if((execret = regexec(&compreg, str, matchcnt, matches, 0)) == 0)
    {
      printf("regexec successful.\n");
      int i = 0; 
      for(; i < MATCH_CNT; i++)
      {
        printf("Beginning of match %i: ", matches[i].rm_so);
        printf("End of match %i: ", matches[i].rm_so);
      }
    }
    else if(execret != 0)
    {
      printf("Regexec failed.\n");
      size_t errbuffsz = regerror(execret, &compreg, 0, 0);
      errbuff = malloc(errbuffsz);
      memset(errbuff, '\0', errbuffsz);
      regerror(execret, &compreg, errbuff, errbuffsz);
      fprintf(stderr, "Regexec error: %s", errbuff);
    }
  }
  else
  {
    printf("Compiling failed.\n");
    size_t errbuffsz = regerror(compret, &compreg, 0, 0);
    errbuff = malloc(errbuffsz);
    memset(errbuff, '\0', errbuffsz);
    regerror(compret, &compreg, errbuff, errbuffsz);
    fprintf(stderr, "Regexec error: %s", errbuff);
  }

  printf("Trying to match with extended regex...\n");
  compret = -2;
  if((compret = regcomp(&compreg, pat, 0)) == 0)
  {
    printf("Compiling successful.\n");
    int execret = -2; 
    if((execret = regexec(&compreg, str, matchcnt, matches, 0)) == 0)
    {
      printf("regexec successful.\n");
      int i = 0; 
      for(; i < MATCH_CNT; i++)
      {
        printf("Beginning of match %i: ", matches[i].rm_so);
        printf("End of match %i: ", matches[i].rm_so);
      }
    }
    else if(execret != 0)
    {
      printf("Regexec failed.\n");
      size_t errbuffsz = regerror(execret, &compreg, 0, 0);
      errbuff = malloc(errbuffsz);
      memset(errbuff, '\0', errbuffsz);
      regerror(execret, &compreg, errbuff, errbuffsz);
      fprintf(stderr, "Regexec error: %s", errbuff);
    }
  }
  else
  {
    printf("Compiling failed.\n");
    size_t errbuffsz = regerror(compret, &compreg, 0, 0);
    errbuff = malloc(errbuffsz);
    memset(errbuff, '\0', errbuffsz);
    regerror(compret, &compreg, errbuff, errbuffsz);
    fprintf(stderr, "Regexec error: %s", errbuff);
  }
  free(errbuff);
  errbuff = NULL; 
  return 0;

}