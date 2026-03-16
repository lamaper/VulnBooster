UChar * ufmt_defaultCPToUnicode ( const char * s , int32_t sSize , UChar * target , int32_t tSize ) {
 UChar * alias ;
 UErrorCode status = U_ZERO_ERROR ;
 UConverter * defConverter = u_getDefaultConverter ( & status ) ;
 if ( U_FAILURE ( status ) || defConverter == 0 ) return 0 ;
 if ( sSize <= 0 ) {
 sSize = uprv_strlen ( s ) + 1 ;
 }
 if ( target != 0 ) {
 alias = target ;
 ucnv_toUnicode ( defConverter , & alias , alias + tSize , & s , s + sSize - 1 , NULL , TRUE , & status ) ;
 * alias = 0x0000 ;
 }
 u_releaseDefaultConverter ( defConverter ) ;
 return target ;
 }