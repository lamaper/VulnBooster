TSReturnCode compare_field_names ( RegressionTest * , TSMBuffer bufp1 , TSMLoc mime_loc1 , TSMLoc field_loc1 , TSMBuffer bufp2 , TSMLoc mime_loc2 , TSMLoc field_loc2 ) {
 const char * name1 ;
 const char * name2 ;
 int length1 ;
 int length2 ;
 name1 = TSMimeHdrFieldNameGet ( bufp1 , mime_loc1 , field_loc1 , & length1 ) ;
 name2 = TSMimeHdrFieldNameGet ( bufp2 , mime_loc2 , field_loc2 , & length2 ) ;
 if ( ( length1 == length2 ) && ( strncmp ( name1 , name2 , length1 ) == 0 ) ) {
 return TS_SUCCESS ;
 }
 else {
 return TS_ERROR ;
 }
 }