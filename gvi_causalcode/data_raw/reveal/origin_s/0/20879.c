static void read_ordlist ( struct recvbuf * rbufp , int restrict_mask ) {
 const char ifstats_s [ ] = "ifstats" ;
 const size_t ifstats_chars = COUNTOF ( ifstats_s ) - 1 ;
 const char addr_rst_s [ ] = "addr_restrictions" ;
 const size_t a_r_chars = COUNTOF ( addr_rst_s ) - 1 ;
 struct ntp_control * cpkt ;
 u_short qdata_octets ;
 cpkt = ( struct ntp_control * ) & rbufp -> recv_pkt ;
 qdata_octets = ntohs ( cpkt -> count ) ;
 if ( 0 == qdata_octets || ( ifstats_chars == qdata_octets && ! memcmp ( ifstats_s , cpkt -> u . data , ifstats_chars ) ) ) {
 read_ifstats ( rbufp ) ;
 return ;
 }
 if ( a_r_chars == qdata_octets && ! memcmp ( addr_rst_s , cpkt -> u . data , a_r_chars ) ) {
 read_addr_restrictions ( rbufp ) ;
 return ;
 }
 ctl_error ( CERR_UNKNOWNVAR ) ;
 }