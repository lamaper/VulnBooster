static void tokenize ( const char * line , char * * tokens , int * ntok ) {
 register const char * cp ;
 register char * sp ;
 static char tspace [ MAXLINE ] ;
 sp = tspace ;
 cp = line ;
 for ( * ntok = 0 ;
 * ntok < MAXTOKENS ;
 ( * ntok ) ++ ) {
 tokens [ * ntok ] = sp ;
 while ( ISSPACE ( * cp ) ) cp ++ ;
 if ( ISEOL ( * cp ) ) break ;
 if ( * ntok == 1 && tokens [ 0 ] [ 0 ] == ':' ) {
 do {
 if ( sp - tspace >= MAXLINE ) goto toobig ;
 * sp ++ = * cp ++ ;
 }
 while ( ! ISEOL ( * cp ) ) ;
 }
 else if ( * cp == '\"' ) {
 ++ cp ;
 do {
 if ( sp - tspace >= MAXLINE ) goto toobig ;
 * sp ++ = * cp ++ ;
 }
 while ( ( * cp != '\"' ) && ! ISEOL ( * cp ) ) ;
 }
 else {
 do {
 if ( sp - tspace >= MAXLINE ) goto toobig ;
 * sp ++ = * cp ++ ;
 }
 while ( ( * cp != '\"' ) && ! ISSPACE ( * cp ) && ! ISEOL ( * cp ) ) ;
 }
 if ( sp - tspace >= MAXLINE ) goto toobig ;
 * sp ++ = '\0' ;
 }
 return ;
 toobig : * ntok = 0 ;
 fprintf ( stderr , "***Line `%s' is too big\n" , line ) ;
 return ;
 }