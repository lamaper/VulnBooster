static char * create_delimiter ( char * query , char * delimiter_buff , int delimiter_max_size ) {
 int proposed_length ;
 char * presence ;
 delimiter_buff [ 0 ] = ';
' ;
 for ( proposed_length = 2 ;
 proposed_length < delimiter_max_size ;
 delimiter_max_size ++ ) {
 delimiter_buff [ proposed_length - 1 ] = ';
' ;
 delimiter_buff [ proposed_length ] = '\0' ;
 presence = strstr ( query , delimiter_buff ) ;
 if ( presence == NULL ) {
 return delimiter_buff ;
 }
 }
 return NULL ;
 }