static int rv34_decoder_realloc ( RV34DecContext * r ) {
 rv34_decoder_free ( r ) ;
 return rv34_decoder_alloc ( r ) ;
 }