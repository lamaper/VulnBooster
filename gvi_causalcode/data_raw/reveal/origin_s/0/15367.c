static int utf16_to_unicode ( uint32_t * pwc , const char * s , size_t n , int be ) {
 const char * utf16 = s ;
 unsigned uc ;
 if ( n == 0 ) return ( 0 ) ;
 if ( n == 1 ) {
 * pwc = UNICODE_R_CHAR ;
 return ( - 1 ) ;
 }
 if ( be ) uc = archive_be16dec ( utf16 ) ;
 else uc = archive_le16dec ( utf16 ) ;
 utf16 += 2 ;
 if ( IS_HIGH_SURROGATE_LA ( uc ) ) {
 unsigned uc2 ;
 if ( n >= 4 ) {
 if ( be ) uc2 = archive_be16dec ( utf16 ) ;
 else uc2 = archive_le16dec ( utf16 ) ;
 }
 else uc2 = 0 ;
 if ( IS_LOW_SURROGATE_LA ( uc2 ) ) {
 uc = combine_surrogate_pair ( uc , uc2 ) ;
 utf16 += 2 ;
 }
 else {
 * pwc = UNICODE_R_CHAR ;
 return ( - 2 ) ;
 }
 }
 if ( IS_SURROGATE_PAIR_LA ( uc ) || uc > UNICODE_MAX ) {
 * pwc = UNICODE_R_CHAR ;
 return ( ( ( int ) ( utf16 - s ) ) * - 1 ) ;
 }
 * pwc = uc ;
 return ( ( int ) ( utf16 - s ) ) ;
 }