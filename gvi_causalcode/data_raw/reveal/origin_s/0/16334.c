CURLcode glob_next_url ( char * * globbed , URLGlob * glob ) {
 URLPattern * pat ;
 size_t i ;
 size_t len ;
 size_t buflen = glob -> urllen + 1 ;
 char * buf = glob -> glob_buffer ;
 * globbed = NULL ;
 if ( ! glob -> beenhere ) glob -> beenhere = 1 ;
 else {
 bool carry = TRUE ;
 for ( i = 0 ;
 carry && ( i < glob -> size ) ;
 i ++ ) {
 carry = FALSE ;
 pat = & glob -> pattern [ glob -> size - 1 - i ] ;
 switch ( pat -> type ) {
 case UPTSet : if ( ( pat -> content . Set . elements ) && ( ++ pat -> content . Set . ptr_s == pat -> content . Set . size ) ) {
 pat -> content . Set . ptr_s = 0 ;
 carry = TRUE ;
 }
 break ;
 case UPTCharRange : pat -> content . CharRange . ptr_c = ( char ) ( pat -> content . CharRange . step + ( int ) ( ( unsigned char ) pat -> content . CharRange . ptr_c ) ) ;
 if ( pat -> content . CharRange . ptr_c > pat -> content . CharRange . max_c ) {
 pat -> content . CharRange . ptr_c = pat -> content . CharRange . min_c ;
 carry = TRUE ;
 }
 break ;
 case UPTNumRange : pat -> content . NumRange . ptr_n += pat -> content . NumRange . step ;
 if ( pat -> content . NumRange . ptr_n > pat -> content . NumRange . max_n ) {
 pat -> content . NumRange . ptr_n = pat -> content . NumRange . min_n ;
 carry = TRUE ;
 }
 break ;
 default : printf ( "internal error: invalid pattern type (%d)\n" , ( int ) pat -> type ) ;
 return CURLE_FAILED_INIT ;
 }
 }
 if ( carry ) {
 return CURLE_OK ;
 }
 }
 for ( i = 0 ;
 i < glob -> size ;
 ++ i ) {
 pat = & glob -> pattern [ i ] ;
 switch ( pat -> type ) {
 case UPTSet : if ( pat -> content . Set . elements ) {
 len = strlen ( pat -> content . Set . elements [ pat -> content . Set . ptr_s ] ) ;
 snprintf ( buf , buflen , "%s" , pat -> content . Set . elements [ pat -> content . Set . ptr_s ] ) ;
 buf += len ;
 buflen -= len ;
 }
 break ;
 case UPTCharRange : * buf ++ = pat -> content . CharRange . ptr_c ;
 break ;
 case UPTNumRange : len = snprintf ( buf , buflen , "%0*ld" , pat -> content . NumRange . padlength , pat -> content . NumRange . ptr_n ) ;
 buf += len ;
 buflen -= len ;
 break ;
 default : printf ( "internal error: invalid pattern type (%d)\n" , ( int ) pat -> type ) ;
 return CURLE_FAILED_INIT ;
 }
 }
 * buf = '\0' ;
 * globbed = strdup ( glob -> glob_buffer ) ;
 if ( ! * globbed ) return CURLE_OUT_OF_MEMORY ;
 return CURLE_OK ;
 }