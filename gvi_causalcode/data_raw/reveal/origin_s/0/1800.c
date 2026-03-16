static int infer_pkt_encap ( const guint8 * pd , int len ) {
 int i ;
 if ( len <= 0 ) {
 return WTAP_ENCAP_PPP_WITH_PHDR ;
 }
 if ( pd [ 0 ] == 0xFF ) {
 return WTAP_ENCAP_PPP_WITH_PHDR ;
 }
 if ( len >= 2 ) {
 if ( pd [ 0 ] == 0x07 && pd [ 1 ] == 0x03 ) {
 return WTAP_ENCAP_WFLEET_HDLC ;
 }
 else if ( ( pd [ 0 ] == 0x0F && pd [ 1 ] == 0x00 ) || ( pd [ 0 ] == 0x8F && pd [ 1 ] == 0x00 ) ) {
 return WTAP_ENCAP_CHDLC_WITH_PHDR ;
 }
 for ( i = 0 ;
 i < len && ( pd [ i ] & 0x01 ) == 0 ;
 i ++ ) ;
 i ++ ;
 if ( i == len ) {
 return WTAP_ENCAP_LAPB ;
 }
 if ( pd [ i ] == 0x03 ) return WTAP_ENCAP_FRELAY_WITH_PHDR ;
 }
 return WTAP_ENCAP_LAPB ;
 }