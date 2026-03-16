static unsigned int uint_to_str ( ngx_uint_t i , u_char * str , ngx_uint_t size ) {
 unsigned int len = ngx_snprintf ( str , size - 1 , "%ui" , i ) - str ;
 str [ len ] = '\0' ;
 return len ;
 }