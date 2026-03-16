size_t gcry_sexp_canon_len ( const unsigned char * buffer , size_t length , size_t * erroff , gcry_error_t * errcode ) {
 const unsigned char * p ;
 const unsigned char * disphint = NULL ;
 unsigned int datalen = 0 ;
 size_t dummy_erroff ;
 gcry_error_t dummy_errcode ;
 size_t count = 0 ;
 int level = 0 ;
 if ( ! erroff ) erroff = & dummy_erroff ;
 if ( ! errcode ) errcode = & dummy_errcode ;
 * errcode = gcry_error ( GPG_ERR_NO_ERROR ) ;
 * erroff = 0 ;
 if ( ! buffer ) return 0 ;
 if ( * buffer != '(' ) {
 * errcode = gcry_error ( GPG_ERR_SEXP_NOT_CANONICAL ) ;
 return 0 ;
 }
 for ( p = buffer ;
 ;
 p ++ , count ++ ) {
 if ( length && count >= length ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_STRING_TOO_LONG ) ;
 return 0 ;
 }
 if ( datalen ) {
 if ( * p == ':' ) {
 if ( length && ( count + datalen ) >= length ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_STRING_TOO_LONG ) ;
 return 0 ;
 }
 count += datalen ;
 p += datalen ;
 datalen = 0 ;
 }
 else if ( digitp ( p ) ) datalen = datalen * 10 + atoi_1 ( p ) ;
 else {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_INV_LEN_SPEC ) ;
 return 0 ;
 }
 }
 else if ( * p == '(' ) {
 if ( disphint ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_UNMATCHED_DH ) ;
 return 0 ;
 }
 level ++ ;
 }
 else if ( * p == ')' ) {
 if ( ! level ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_UNMATCHED_PAREN ) ;
 return 0 ;
 }
 if ( disphint ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_UNMATCHED_DH ) ;
 return 0 ;
 }
 if ( ! -- level ) return ++ count ;
 }
 else if ( * p == '[' ) {
 if ( disphint ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_NESTED_DH ) ;
 return 0 ;
 }
 disphint = p ;
 }
 else if ( * p == ']' ) {
 if ( ! disphint ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_UNMATCHED_DH ) ;
 return 0 ;
 }
 disphint = NULL ;
 }
 else if ( digitp ( p ) ) {
 if ( * p == '0' ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_ZERO_PREFIX ) ;
 return 0 ;
 }
 datalen = atoi_1 ( p ) ;
 }
 else if ( * p == '&' || * p == '\\' ) {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_UNEXPECTED_PUNC ) ;
 return 0 ;
 }
 else {
 * erroff = count ;
 * errcode = gcry_error ( GPG_ERR_SEXP_BAD_CHARACTER ) ;
 return 0 ;
 }
 }
 }