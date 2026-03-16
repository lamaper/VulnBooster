u_int ppp_if_print ( netdissect_options * ndo , const struct pcap_pkthdr * h , register const u_char * p ) {
 register u_int length = h -> len ;
 register u_int caplen = h -> caplen ;
 if ( caplen < PPP_HDRLEN ) {
 ND_PRINT ( ( ndo , "[|ppp]" ) ) ;
 return ( caplen ) ;
 }


 return ( 0 ) ;
 }