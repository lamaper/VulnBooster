CURLcode glob_match_url ( char * * result , char * filename , URLGlob * glob ) {
 char * target ;
 size_t allocsize ;
 char numbuf [ 18 ] ;
 char * appendthis = NULL ;
 size_t appendlen = 0 ;
 size_t stringlen = 0 ;
 * result = NULL ;
 allocsize = strlen ( filename ) + 1 ;
 target = malloc ( allocsize ) ;
 if ( ! target ) return CURLE_OUT_OF_MEMORY ;
 while ( * filename ) {
 if ( * filename == '#' && ISDIGIT ( filename [ 1 ] ) ) {
 unsigned long i ;
 char * ptr = filename ;
 unsigned long num = strtoul ( & filename [ 1 ] , & filename , 10 ) ;
 URLPattern * pat = NULL ;
 if ( num < glob -> size ) {
 num -- ;
 for ( i = 0 ;
 i < glob -> size ;
 i ++ ) {
 if ( glob -> pattern [ i ] . globindex == ( int ) num ) {
 pat = & glob -> pattern [ i ] ;
 break ;
 }
 }
 }
 if ( pat ) {
 switch ( pat -> type ) {
 case UPTSet : if ( pat -> content . Set . elements ) {
 appendthis = pat -> content . Set . elements [ pat -> content . Set . ptr_s ] ;
 appendlen = strlen ( pat -> content . Set . elements [ pat -> content . Set . ptr_s ] ) ;
 }
 break ;
 case UPTCharRange : numbuf [ 0 ] = pat -> content . CharRange . ptr_c ;
 numbuf [ 1 ] = 0 ;
 appendthis = numbuf ;
 appendlen = 1 ;
 break ;
 case UPTNumRange : snprintf ( numbuf , sizeof ( numbuf ) , "%0*d" , pat -> content . NumRange . padlength , pat -> content . NumRange . ptr_n ) ;
 appendthis = numbuf ;
 appendlen = strlen ( numbuf ) ;
 break ;
 default : fprintf ( stderr , "internal error: invalid pattern type (%d)\n" , ( int ) pat -> type ) ;
 Curl_safefree ( target ) ;
 return CURLE_FAILED_INIT ;
 }
 }
 else {
 filename = ptr ;
 appendthis = filename ++ ;
 appendlen = 1 ;
 }
 }
 else {
 appendthis = filename ++ ;
 appendlen = 1 ;
 }
 if ( appendlen + stringlen >= allocsize ) {
 char * newstr ;
 allocsize = ( appendlen + stringlen ) * 2 ;
 newstr = realloc ( target , allocsize + 1 ) ;
 if ( ! newstr ) {
 Curl_safefree ( target ) ;
 return CURLE_OUT_OF_MEMORY ;
 }
 target = newstr ;
 }
 memcpy ( & target [ stringlen ] , appendthis , appendlen ) ;
 stringlen += appendlen ;
 }
 target [ stringlen ] = '\0' ;

 char * sanitized ;
 SANITIZEcode sc = sanitize_file_name ( & sanitized , target , ( SANITIZE_ALLOW_PATH | SANITIZE_ALLOW_RESERVED ) ) ;
 Curl_safefree ( target ) ;
 if ( sc ) return CURLE_URL_MALFORMAT ;
 target = sanitized ;
 }

 return CURLE_OK ;
 }