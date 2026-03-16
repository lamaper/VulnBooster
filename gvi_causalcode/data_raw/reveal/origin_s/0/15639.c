u_int sl_bsdos_if_print ( netdissect_options * ndo , const struct pcap_pkthdr * h , const u_char * p ) {
 register u_int caplen = h -> caplen ;
 register u_int length = h -> len ;
 register const struct ip * ip ;
 if ( caplen < SLIP_HDRLEN ) {
 ND_PRINT ( ( ndo , "%s" , tstr ) ) ;
 return ( caplen ) ;
 }
 length -= SLIP_HDRLEN ;
 ip = ( const struct ip * ) ( p + SLIP_HDRLEN ) ;


 return ( SLIP_HDRLEN ) ;
 }