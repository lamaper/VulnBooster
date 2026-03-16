strong_alias ( _nss_nis_setaliasent , _nss_nis_endaliasent ) static enum nss_status internal_nis_getaliasent_r ( struct aliasent * alias , char * buffer , size_t buflen , int * errnop ) {
 char * domain ;
 if ( __builtin_expect ( yp_get_default_domain ( & domain ) , 0 ) ) return NSS_STATUS_UNAVAIL ;
 alias -> alias_local = 0 ;
 int parse_res ;
 do {
 char * result ;
 int len ;
 char * outkey ;
 int keylen ;
 int yperr ;
 if ( new_start ) yperr = yp_first ( domain , "mail.aliases" , & outkey , & keylen , & result , & len ) ;
 else yperr = yp_next ( domain , "mail.aliases" , oldkey , oldkeylen , & outkey , & keylen , & result , & len ) ;
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
 parse_res = _nss_nis_parse_aliasent ( outkey , p , alias , buffer , buflen , errnop ) ;
 if ( __builtin_expect ( parse_res == - 1 , 0 ) ) {
 free ( outkey ) ;
 * errnop = ERANGE ;
 return NSS_STATUS_TRYAGAIN ;
 }
 free ( oldkey ) ;
 oldkey = outkey ;
 oldkeylen = keylen ;
 new_start = 0 ;
 }
 while ( ! parse_res ) ;
 return NSS_STATUS_SUCCESS ;
 }