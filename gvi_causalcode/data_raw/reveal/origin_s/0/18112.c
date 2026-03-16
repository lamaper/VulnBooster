gcry_error_t gcry_sexp_create ( gcry_sexp_t * retsexp , void * buffer , size_t length , int autodetect , void ( * freefnc ) ( void * ) ) {
 gcry_error_t errcode ;
 gcry_sexp_t se ;
 if ( ! retsexp ) return gcry_error ( GPG_ERR_INV_ARG ) ;
 * retsexp = NULL ;
 if ( autodetect < 0 || autodetect > 1 || ! buffer ) return gcry_error ( GPG_ERR_INV_ARG ) ;
 if ( ! length && ! autodetect ) {
 length = gcry_sexp_canon_len ( buffer , 0 , NULL , & errcode ) ;
 if ( ! length ) return errcode ;
 }
 else if ( ! length && autodetect ) {
 length = strlen ( ( char * ) buffer ) ;
 }
 errcode = sexp_sscan ( & se , NULL , buffer , length , 0 , NULL ) ;
 if ( errcode ) return errcode ;
 * retsexp = se ;
 if ( freefnc ) {
 freefnc ( buffer ) ;
 }
 return gcry_error ( GPG_ERR_NO_ERROR ) ;
 }