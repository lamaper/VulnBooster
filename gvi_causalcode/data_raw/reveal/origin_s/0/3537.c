static enum nss_status internal_getent ( struct STRUCTURE * result , char * buffer , size_t buflen , int * errnop H_ERRNO_PROTO EXTRA_ARGS_DECL ) {
 char * p ;
 struct parser_data * data = ( void * ) buffer ;
 size_t linebuflen = buffer + buflen - data -> linebuffer ;
 int parse_result ;
 if ( buflen < sizeof * data + 2 ) {
 * errnop = ERANGE ;
 H_ERRNO_SET ( NETDB_INTERNAL ) ;
 return NSS_STATUS_TRYAGAIN ;
 }
 do {
 get_contents_ret r = get_contents ( data -> linebuffer , linebuflen , stream ) ;
 if ( r == gcr_error ) {
 H_ERRNO_SET ( HOST_NOT_FOUND ) ;
 return NSS_STATUS_NOTFOUND ;
 }
 if ( r == gcr_overflow ) {
 * errnop = ERANGE ;
 H_ERRNO_SET ( NETDB_INTERNAL ) ;
 return NSS_STATUS_TRYAGAIN ;
 }
 p = data -> linebuffer ;
 while ( isspace ( * p ) ) ++ p ;
 }
 while ( * p == '\0' || * p == '#' || ! ( parse_result = parse_line ( p , result , data , buflen , errnop EXTRA_ARGS ) ) ) ;
 if ( __glibc_unlikely ( parse_result == - 1 ) ) {
 H_ERRNO_SET ( NETDB_INTERNAL ) ;
 return NSS_STATUS_TRYAGAIN ;
 }
 return NSS_STATUS_SUCCESS ;
 }