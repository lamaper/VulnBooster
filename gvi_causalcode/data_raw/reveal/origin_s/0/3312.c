static char * nexttok ( char * * str ) {
 register char * cp ;
 char * starttok ;
 cp = * str ;
 while ( * cp == ' ' || * cp == '\t' ) cp ++ ;
 starttok = cp ;
 while ( * cp != '\0' && * cp != '\n' && * cp != ' ' && * cp != '\t' && * cp != '#' ) cp ++ ;
 if ( starttok == cp ) return NULL ;
 if ( * cp == ' ' || * cp == '\t' ) * cp ++ = '\0' ;
 else * cp = '\0' ;
 * str = cp ;
 return starttok ;
 }