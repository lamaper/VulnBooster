static int doubleebx ( const char * src , uint32_t * myebx , uint32_t * scur , uint32_t ssize ) {
 uint32_t oldebx = * myebx ;
 * myebx *= 2 ;
 if ( ! ( oldebx & 0x7fffffff ) ) {
 if ( ! CLI_ISCONTAINED ( src , ssize , src + * scur , 4 ) ) return - 1 ;
 oldebx = cli_readint32 ( src + * scur ) ;
 * myebx = oldebx * 2 + 1 ;
 * scur += 4 ;
 }
 return ( oldebx >> 31 ) ;
 }