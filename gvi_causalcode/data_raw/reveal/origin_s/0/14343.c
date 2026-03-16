void glob_cleanup ( URLGlob * glob ) {
 size_t i ;
 int elem ;
 for ( i = 0 ;
 i < glob -> size ;
 i ++ ) {
 if ( ( glob -> pattern [ i ] . type == UPTSet ) && ( glob -> pattern [ i ] . content . Set . elements ) ) {
 for ( elem = glob -> pattern [ i ] . content . Set . size - 1 ;
 elem >= 0 ;
 -- elem ) {
 Curl_safefree ( glob -> pattern [ i ] . content . Set . elements [ elem ] ) ;
 }
 Curl_safefree ( glob -> pattern [ i ] . content . Set . elements ) ;
 }
 }
 Curl_safefree ( glob -> glob_buffer ) ;
 Curl_safefree ( glob ) ;
 }