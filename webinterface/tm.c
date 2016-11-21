/*  Das hier soll nur zum test des Aufrufs von der Webseite dienen   */

#include <stdio.h>
#include <stdlib.h>
 
main (void) {

  int i;
  FILE * fp; 
  char s[100] = "----------------";

  fp = fopen("/tmp/tm-output.txt","w+");

  fprintf(fp,"<h1>Antwort</h1>\n\n");

  fgets(s,30,stdin);
  fprintf(fp,"%s\n",s);

  fclose(fp);

  return 0; 
}
