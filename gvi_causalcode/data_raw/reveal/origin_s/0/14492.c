static inline int padr_match ( PCNetState * s , const uint8_t * buf , int size ) {
 struct qemu_ether_header * hdr = ( void * ) buf ;
 uint8_t padr [ 6 ] = {
 s -> csr [ 12 ] & 0xff , s -> csr [ 12 ] >> 8 , s -> csr [ 13 ] & 0xff , s -> csr [ 13 ] >> 8 , s -> csr [ 14 ] & 0xff , s -> csr [ 14 ] >> 8 }
 ;
 int result = ( ! CSR_DRCVPA ( s ) ) && ! memcmp ( hdr -> ether_dhost , padr , 6 ) ;

 printf ( "padr_match result=%d\n" , result ) ;

 }