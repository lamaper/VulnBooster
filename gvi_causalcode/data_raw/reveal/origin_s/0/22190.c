static gpg_err_code_t make_space ( struct make_space_ctx * c , size_t n ) {
 size_t used = c -> pos - c -> sexp -> d ;
 if ( used + n + sizeof ( DATALEN ) + 1 >= c -> allocated ) {
 gcry_sexp_t newsexp ;
 byte * newhead ;
 size_t newsize ;
 newsize = c -> allocated + 2 * ( n + sizeof ( DATALEN ) + 1 ) ;
 if ( newsize <= c -> allocated ) return GPG_ERR_TOO_LARGE ;
 newsexp = gcry_realloc ( c -> sexp , sizeof * newsexp + newsize - 1 ) ;
 if ( ! newsexp ) return gpg_err_code_from_errno ( errno ) ;
 c -> allocated = newsize ;
 newhead = newsexp -> d ;
 c -> pos = newhead + used ;
 c -> sexp = newsexp ;
 }
 return 0 ;
 }