static int validate_header ( const struct evkeyvalq * headers , const char * key , const char * value ) {
 const char * real_val = evhttp_find_header ( headers , key ) ;
 if ( real_val == NULL ) return ( - 1 ) ;
 if ( strcmp ( real_val , value ) != 0 ) return ( - 1 ) ;
 return ( 0 ) ;
 }