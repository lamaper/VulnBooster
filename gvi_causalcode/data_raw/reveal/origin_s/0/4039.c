static void skip ( const char * * date ) {
 while ( * * date && ! ISALNUM ( * * date ) ) ( * date ) ++ ;
 }