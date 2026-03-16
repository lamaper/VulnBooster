int32 filechecksum ( FILE * file ) {
 uint32 sum = 0 , chunk ;
 rewind ( file ) ;
 while ( 1 ) {
 chunk = getuint32 ( file ) ;
 if ( feof ( file ) || ferror ( file ) ) break ;
 sum += chunk ;
 }
 return ( sum ) ;
 }