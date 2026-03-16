void ufile_close_translit ( UFILE * f ) {



 if ( f -> fTranslit -> buffer ) {
 uprv_free ( f -> fTranslit -> buffer ) ;
 }
 uprv_free ( f -> fTranslit ) ;
 f -> fTranslit = NULL ;
