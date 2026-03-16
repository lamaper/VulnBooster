static inline int padr_bcast ( PCNetState * s , const uint8_t * buf , int size ) {
 static const uint8_t BCAST [ 6 ] = {
 0xff , 0xff , 0xff , 0xff , 0xff , 0xff }
 ;
 struct qemu_ether_header * hdr = ( void * ) buf ;
 int result = ! CSR_DRCVBC ( s ) && ! memcmp ( hdr -> ether_dhost , BCAST , 6 ) ;


 }