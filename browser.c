#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Listing fragt REMOTE_ADDR ab. Laesst sich der Wert nicht
 * auslesen, gibt das CGI-Programm den Statuscode 500 zurueck.
 * Ansonsten werden die verbotenen IP-Adressen in forbidden mit
 * REMOTE_ADDR ueberprueft und entsprechende Massnahmen getroffen. */

/* die Liste der IP-Adressen, die keinen Zugriff auf die Seite
 * haben sollen */
char *forbidden[] = {
   "127.0.0.1", "168.123.6.1", NULL
};

/* Weiterleitung zu einer URL;
 * url ist die URL, zu der Sie den User weiterleiten.
 */
void print_location(char *url) {
   printf("Location: %s\n\n", url);
   /* fuer den Fall, dass ein alter Browser keine
    * automatische Weiterleitung unterstuetzt */
   printf("Content-Type: text/html\n\n");
   printf("<html><head>\n");
   printf("<title>Weiterleitung zu %s</title>\n",url);
   printf("</head><body><pre>\n");
   printf("Weiter gehts <a href=\"%s\">hier</a>",url);
   printf("</pre></body></html>\n");
}

/* Statuscode zurueckgeben */
void print_status(char *status) {
   printf("Status: %s", status);
}

int main(void) {
   char *p;
   int i;

   /* IP-Adresse ermitteln */
   p = getenv("REMOTE_ADDR");
   if( p == NULL) { /* Fehler bei getenv-Abfrage */
      print_status("500");
      return EXIT_FAILURE;
   }
   for(i=0; forbidden[i] != NULL; i++)
      if(strcmp(p, forbidden[i]) == 0) {
         /* Diese IP hat keinen Zutritt */
         print_status("403");
         return EXIT_FAILURE;
      }
   /* Ok, der User wird auf die Willkommen-Seite weitergeleitet.
    * Die URL an Ihre Beduerfnisse anpassen */
   print_location("http://localhost/welcome.html");
   return EXIT_SUCCESS;
}
