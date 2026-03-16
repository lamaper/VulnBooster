static gcry_error_t vsexp_sscan ( gcry_sexp_t * retsexp , size_t * erroff , const char * buffer , size_t length , int argflag , void * * arg_list , va_list arg_ptr ) {
 gcry_err_code_t err = 0 ;
 static const char tokenchars [ ] = "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "0123456789-./_:*+=" ;
 const char * p ;
 size_t n ;
 const char * digptr = NULL ;
 const char * quoted = NULL ;
 const char * tokenp = NULL ;
 const char * hexfmt = NULL ;
 const char * base64 = NULL ;
 const char * disphint = NULL ;
 const char * percent = NULL ;
 int hexcount = 0 ;
 int quoted_esc = 0 ;
 int datalen = 0 ;
 size_t dummy_erroff ;
 struct make_space_ctx c ;
 int arg_counter = 0 ;
 int level = 0 ;
 if ( ! erroff ) erroff = & dummy_erroff ;

 \ if ( ! arg_list ) \ storage = va_arg ( arg_ptr , type ) ;
 \ else \ storage = * ( ( type * ) ( arg_list [ arg_counter ++ ] ) ) ;
 \ }
 \ while ( 0 ) # define MAKE_SPACE ( n ) do {
 \ gpg_err_code_t _ms_err = make_space ( & c , ( n ) ) ;
 \ if ( _ms_err ) \ {
 \ err = _ms_err ;
 \ * erroff = p - buffer ;
 \ goto leave ;
 \ }
 \ }
 while ( 0 ) # define STORE_LEN ( p , n ) do {
 \ DATALEN ashort = ( n ) ;
 \ memcpy ( ( p ) , & ashort , sizeof ( ashort ) ) ;
 \ ( p ) += sizeof ( ashort ) ;
 \ }
 while ( 0 ) c . allocated = length + sizeof ( DATALEN ) ;
 if ( buffer && length && gcry_is_secure ( buffer ) ) c . sexp = gcry_malloc_secure ( sizeof * c . sexp + c . allocated - 1 ) ;
 else c . sexp = gcry_malloc ( sizeof * c . sexp + c . allocated - 1 ) ;
 if ( ! c . sexp ) {
 err = gpg_err_code_from_errno ( errno ) ;
 * erroff = 0 ;
 goto leave ;
 }
 c . pos = c . sexp -> d ;
 for ( p = buffer , n = length ;
 n ;
 p ++ , n -- ) {
 if ( tokenp && ! hexfmt ) {
 if ( strchr ( tokenchars , * p ) ) continue ;
 else {
 datalen = p - tokenp ;
 MAKE_SPACE ( datalen ) ;
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , datalen ) ;
 memcpy ( c . pos , tokenp , datalen ) ;
 c . pos += datalen ;
 tokenp = NULL ;
 }
 }
 if ( quoted ) {
 if ( quoted_esc ) {
 switch ( * p ) {
 case 'b' : case 't' : case 'v' : case 'n' : case 'f' : case 'r' : case '"' : case '\'' : case '\\' : quoted_esc = 0 ;
 break ;
 case '0' : case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' : if ( ! ( ( n > 2 ) && ( p [ 1 ] >= '0' ) && ( p [ 1 ] <= '7' ) && ( p [ 2 ] >= '0' ) && ( p [ 2 ] <= '7' ) ) ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_BAD_QUOTATION ;
 goto leave ;
 }
 p += 2 ;
 n -= 2 ;
 quoted_esc = 0 ;
 break ;
 case 'x' : if ( ! ( ( n > 2 ) && hexdigitp ( p + 1 ) && hexdigitp ( p + 2 ) ) ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_BAD_QUOTATION ;
 goto leave ;
 }
 p += 2 ;
 n -= 2 ;
 quoted_esc = 0 ;
 break ;
 case '\r' : if ( n && ( p [ 1 ] == '\n' ) ) {
 p ++ ;
 n -- ;
 }
 quoted_esc = 0 ;
 break ;
 case '\n' : if ( n && ( p [ 1 ] == '\r' ) ) {
 p ++ ;
 n -- ;
 }
 quoted_esc = 0 ;
 break ;
 default : * erroff = p - buffer ;
 err = GPG_ERR_SEXP_BAD_QUOTATION ;
 goto leave ;
 }
 }
 else if ( * p == '\\' ) quoted_esc = 1 ;
 else if ( * p == '\"' ) {
 unsigned char * save ;
 size_t len ;
 quoted ++ ;
 MAKE_SPACE ( p - quoted ) ;
 * c . pos ++ = ST_DATA ;
 save = c . pos ;
 STORE_LEN ( c . pos , 0 ) ;
 len = unquote_string ( quoted , p - quoted , c . pos ) ;
 c . pos += len ;
 STORE_LEN ( save , len ) ;
 quoted = NULL ;
 }
 }
 else if ( hexfmt ) {
 if ( isxdigit ( * p ) ) hexcount ++ ;
 else if ( * p == '#' ) {
 if ( ( hexcount & 1 ) ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_ODD_HEX_NUMBERS ;
 goto leave ;
 }
 datalen = hexcount / 2 ;
 MAKE_SPACE ( datalen ) ;
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , datalen ) ;
 for ( hexfmt ++ ;
 hexfmt < p ;
 hexfmt ++ ) {
 int tmpc ;
 if ( whitespacep ( hexfmt ) ) continue ;
 tmpc = hextonibble ( * ( const unsigned char * ) hexfmt ) ;
 for ( hexfmt ++ ;
 hexfmt < p && whitespacep ( hexfmt ) ;
 hexfmt ++ ) ;
 if ( hexfmt < p ) {
 tmpc *= 16 ;
 tmpc += hextonibble ( * ( const unsigned char * ) hexfmt ) ;
 }
 * c . pos ++ = tmpc ;
 }
 hexfmt = NULL ;
 }
 else if ( ! whitespacep ( p ) ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_BAD_HEX_CHAR ;
 goto leave ;
 }
 }
 else if ( base64 ) {
 if ( * p == '|' ) base64 = NULL ;
 }
 else if ( digptr ) {
 if ( digitp ( p ) ) ;
 else if ( * p == ':' ) {
 datalen = atoi ( digptr ) ;
 digptr = NULL ;
 if ( datalen > n - 1 ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_STRING_TOO_LONG ;
 goto leave ;
 }
 MAKE_SPACE ( datalen ) ;
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , datalen ) ;
 memcpy ( c . pos , p + 1 , datalen ) ;
 c . pos += datalen ;
 n -= datalen ;
 p += datalen ;
 }
 else if ( * p == '\"' ) {
 digptr = NULL ;
 quoted = p ;
 quoted_esc = 0 ;
 }
 else if ( * p == '#' ) {
 digptr = NULL ;
 hexfmt = p ;
 hexcount = 0 ;
 }
 else if ( * p == '|' ) {
 digptr = NULL ;
 base64 = p ;
 }
 else {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_INV_LEN_SPEC ;
 goto leave ;
 }
 }
 else if ( percent ) {
 if ( * p == 'm' || * p == 'M' ) {
 gcry_mpi_t m ;
 size_t nm = 0 ;
 int mpifmt = * p == 'm' ? GCRYMPI_FMT_STD : GCRYMPI_FMT_USG ;
 ARG_NEXT ( m , gcry_mpi_t ) ;
 if ( gcry_mpi_get_flag ( m , GCRYMPI_FLAG_OPAQUE ) ) {
 void * mp ;
 unsigned int nbits ;
 mp = gcry_mpi_get_opaque ( m , & nbits ) ;
 nm = ( nbits + 7 ) / 8 ;
 if ( mp && nm ) {
 MAKE_SPACE ( nm ) ;
 if ( ! gcry_is_secure ( c . sexp -> d ) && gcry_mpi_get_flag ( m , GCRYMPI_FLAG_SECURE ) ) {
 gcry_sexp_t newsexp ;
 byte * newhead ;
 newsexp = gcry_malloc_secure ( sizeof * newsexp + c . allocated - 1 ) ;
 if ( ! newsexp ) {
 err = gpg_err_code_from_errno ( errno ) ;
 goto leave ;
 }
 newhead = newsexp -> d ;
 memcpy ( newhead , c . sexp -> d , ( c . pos - c . sexp -> d ) ) ;
 c . pos = newhead + ( c . pos - c . sexp -> d ) ;
 gcry_free ( c . sexp ) ;
 c . sexp = newsexp ;
 }
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , nm ) ;
 memcpy ( c . pos , mp , nm ) ;
 c . pos += nm ;
 }
 }
 else {
 if ( gcry_mpi_print ( mpifmt , NULL , 0 , & nm , m ) ) BUG ( ) ;
 MAKE_SPACE ( nm ) ;
 if ( ! gcry_is_secure ( c . sexp -> d ) && gcry_mpi_get_flag ( m , GCRYMPI_FLAG_SECURE ) ) {
 gcry_sexp_t newsexp ;
 byte * newhead ;
 newsexp = gcry_malloc_secure ( sizeof * newsexp + c . allocated - 1 ) ;
 if ( ! newsexp ) {
 err = gpg_err_code_from_errno ( errno ) ;
 goto leave ;
 }
 newhead = newsexp -> d ;
 memcpy ( newhead , c . sexp -> d , ( c . pos - c . sexp -> d ) ) ;
 c . pos = newhead + ( c . pos - c . sexp -> d ) ;
 gcry_free ( c . sexp ) ;
 c . sexp = newsexp ;
 }
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , nm ) ;
 if ( gcry_mpi_print ( mpifmt , c . pos , nm , & nm , m ) ) BUG ( ) ;
 c . pos += nm ;
 }
 }
 else if ( * p == 's' ) {
 const char * astr ;
 size_t alen ;
 ARG_NEXT ( astr , const char * ) ;
 alen = strlen ( astr ) ;
 MAKE_SPACE ( alen ) ;
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , alen ) ;
 memcpy ( c . pos , astr , alen ) ;
 c . pos += alen ;
 }
 else if ( * p == 'b' ) {
 const char * astr ;
 int alen ;
 ARG_NEXT ( alen , int ) ;
 ARG_NEXT ( astr , const char * ) ;
 MAKE_SPACE ( alen ) ;
 if ( alen && ! gcry_is_secure ( c . sexp -> d ) && gcry_is_secure ( astr ) ) {
 gcry_sexp_t newsexp ;
 byte * newhead ;
 newsexp = gcry_malloc_secure ( sizeof * newsexp + c . allocated - 1 ) ;
 if ( ! newsexp ) {
 err = gpg_err_code_from_errno ( errno ) ;
 goto leave ;
 }
 newhead = newsexp -> d ;
 memcpy ( newhead , c . sexp -> d , ( c . pos - c . sexp -> d ) ) ;
 c . pos = newhead + ( c . pos - c . sexp -> d ) ;
 gcry_free ( c . sexp ) ;
 c . sexp = newsexp ;
 }
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , alen ) ;
 memcpy ( c . pos , astr , alen ) ;
 c . pos += alen ;
 }
 else if ( * p == 'd' ) {
 int aint ;
 size_t alen ;
 char buf [ 35 ] ;
 ARG_NEXT ( aint , int ) ;
 sprintf ( buf , "%d" , aint ) ;
 alen = strlen ( buf ) ;
 MAKE_SPACE ( alen ) ;
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , alen ) ;
 memcpy ( c . pos , buf , alen ) ;
 c . pos += alen ;
 }
 else if ( * p == 'u' ) {
 unsigned int aint ;
 size_t alen ;
 char buf [ 35 ] ;
 ARG_NEXT ( aint , unsigned int ) ;
 sprintf ( buf , "%u" , aint ) ;
 alen = strlen ( buf ) ;
 MAKE_SPACE ( alen ) ;
 * c . pos ++ = ST_DATA ;
 STORE_LEN ( c . pos , alen ) ;
 memcpy ( c . pos , buf , alen ) ;
 c . pos += alen ;
 }
 else if ( * p == 'S' ) {
 gcry_sexp_t asexp ;
 size_t alen , aoff ;
 ARG_NEXT ( asexp , gcry_sexp_t ) ;
 alen = get_internal_buffer ( asexp , & aoff ) ;
 if ( alen ) {
 MAKE_SPACE ( alen ) ;
 memcpy ( c . pos , asexp -> d + aoff , alen ) ;
 c . pos += alen ;
 }
 }
 else {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_INV_LEN_SPEC ;
 goto leave ;
 }
 percent = NULL ;
 }
 else if ( * p == '(' ) {
 if ( disphint ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_UNMATCHED_DH ;
 goto leave ;
 }
 MAKE_SPACE ( 0 ) ;
 * c . pos ++ = ST_OPEN ;
 level ++ ;
 }
 else if ( * p == ')' ) {
 if ( disphint ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_UNMATCHED_DH ;
 goto leave ;
 }
 MAKE_SPACE ( 0 ) ;
 * c . pos ++ = ST_CLOSE ;
 level -- ;
 }
 else if ( * p == '\"' ) {
 quoted = p ;
 quoted_esc = 0 ;
 }
 else if ( * p == '#' ) {
 hexfmt = p ;
 hexcount = 0 ;
 }
 else if ( * p == '|' ) base64 = p ;
 else if ( * p == '[' ) {
 if ( disphint ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_NESTED_DH ;
 goto leave ;
 }
 disphint = p ;
 }
 else if ( * p == ']' ) {
 if ( ! disphint ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_UNMATCHED_DH ;
 goto leave ;
 }
 disphint = NULL ;
 }
 else if ( digitp ( p ) ) {
 if ( * p == '0' ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_ZERO_PREFIX ;
 goto leave ;
 }
 digptr = p ;
 }
 else if ( strchr ( tokenchars , * p ) ) tokenp = p ;
 else if ( whitespacep ( p ) ) ;
 else if ( * p == '{
' ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_UNEXPECTED_PUNC ;
 goto leave ;
 }
 else if ( strchr ( "&\\" , * p ) ) {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_UNEXPECTED_PUNC ;
 goto leave ;
 }
 else if ( argflag && ( * p == '%' ) ) percent = p ;
 else {
 * erroff = p - buffer ;
 err = GPG_ERR_SEXP_BAD_CHARACTER ;
 goto leave ;
 }
 }
 MAKE_SPACE ( 0 ) ;
 * c . pos ++ = ST_STOP ;
 if ( level && ! err ) err = GPG_ERR_SEXP_UNMATCHED_PAREN ;
 leave : if ( err ) {
 if ( c . sexp ) {
 if ( gcry_is_secure ( c . sexp ) ) wipememory ( c . sexp , sizeof ( struct gcry_sexp ) + c . allocated - 1 ) ;
 gcry_free ( c . sexp ) ;
 }
 * retsexp = NULL ;
 }
 else * retsexp = normalize ( c . sexp ) ;
 return gcry_error ( err ) ;
