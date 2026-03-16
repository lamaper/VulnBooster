static int convert_to_token ( const unsigned char * src , size_t len , char * dest ) {
 if ( dest ) memcpy ( dest , src , len ) ;
 return len ;
 }