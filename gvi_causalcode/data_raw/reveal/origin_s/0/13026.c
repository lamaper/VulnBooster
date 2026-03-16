static int best_effort_strncat_in_locale ( struct archive_string * as , const void * _p , size_t length , struct archive_string_conv * sc ) {
 size_t remaining ;
 const uint8_t * itp ;
 int return_value = 0 ;
 if ( sc -> same ) {
 if ( archive_string_append ( as , _p , length ) == NULL ) return ( - 1 ) ;
 return ( invalid_mbs ( _p , length , sc ) ) ;
 }
 remaining = length ;
 itp = ( const uint8_t * ) _p ;
 while ( * itp && remaining > 0 ) {
 if ( * itp > 127 ) {
 if ( sc -> flag & SCONV_TO_UTF8 ) {
 if ( archive_string_append ( as , utf8_replacement_char , sizeof ( utf8_replacement_char ) ) == NULL ) {
 __archive_errx ( 1 , "Out of memory" ) ;
 }
 }
 else {
 archive_strappend_char ( as , '?' ) ;
 }
 return_value = - 1 ;
 }
 else {
 archive_strappend_char ( as , * itp ) ;
 }
 ++ itp ;
 }
 return ( return_value ) ;
 }