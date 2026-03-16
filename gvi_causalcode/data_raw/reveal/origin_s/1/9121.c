enum nss_status _nss_nis_getaliasbyname_r ( const char * name , struct aliasent * alias , char * buffer , size_t buflen , int * errnop ) {
 if ( name == NULL ) {
 * errnop = EINVAL ;
 return NSS_STATUS_UNAVAIL ;
 }
 size_t namlen = strlen ( name ) ;
 char name2 [ namlen + 1 ] ;
 char * domain ;
 if ( __builtin_expect ( yp_get_default_domain ( & domain ) , 0 ) ) return NSS_STATUS_UNAVAIL ;
 size_t i ;
 for ( i = 0 ;
 i < namlen ;
 ++ i ) name2 [ i ] = _tolower ( name [ i ] ) ;
 name2 [ i ] = '\0' ;
 char * result ;
 int len ;
 int yperr = yp_match ( domain , "mail.aliases" , name2 , namlen , & result , & len ) ;
 if ( __builtin_expect ( yperr != YPERR_SUCCESS , 0 ) ) {
 enum nss_status retval = yperr2nss ( yperr ) ;
 if ( retval == NSS_STATUS_TRYAGAIN ) * errnop = errno ;
 return retval ;
 }
 if ( __builtin_expect ( ( size_t ) ( len + 1 ) > buflen , 0 ) ) {
 free ( result ) ;
 * errnop = ERANGE ;
 return NSS_STATUS_TRYAGAIN ;
 }
 char * p = strncpy ( buffer , result , len ) ;
 buffer [ len ] = '\0' ;
 while ( isspace ( * p ) ) ++ p ;
 free ( result ) ;
 alias -> alias_local = 0 ;
 int parse_res = _nss_nis_parse_aliasent ( name , p , alias , buffer , buflen , errnop ) ;
 if ( __builtin_expect ( parse_res < 1 , 0 ) ) {
 if ( parse_res == - 1 ) return NSS_STATUS_TRYAGAIN ;
 else return NSS_STATUS_NOTFOUND ;
 }
 return NSS_STATUS_SUCCESS ;
 }