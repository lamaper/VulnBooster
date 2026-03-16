static void handle_full_packet ( int tun_fd , int dns_fd , int userid ) {
 unsigned long outlen ;
 char out [ 64 * 1024 ] ;
 int touser ;
 int ret ;
 outlen = sizeof ( out ) ;
 ret = uncompress ( ( uint8_t * ) out , & outlen , ( uint8_t * ) users [ userid ] . inpacket . data , users [ userid ] . inpacket . len ) ;
 if ( ret == Z_OK ) {
 struct ip * hdr ;
 hdr = ( struct ip * ) ( out + 4 ) ;
 touser = find_user_by_ip ( hdr -> ip_dst . s_addr ) ;
 if ( touser == - 1 ) {
 write_tun ( tun_fd , out , outlen ) ;
 }
 else {
 if ( users [ touser ] . conn == CONN_DNS_NULL ) {
 if ( users [ touser ] . outpacket . len == 0 ) {
 start_new_outpacket ( touser , users [ userid ] . inpacket . data , users [ userid ] . inpacket . len ) ;
 if ( users [ touser ] . q_sendrealsoon . id != 0 ) send_chunk_or_dataless ( dns_fd , touser , & users [ touser ] . q_sendrealsoon ) ;
 else if ( users [ touser ] . q . id != 0 ) send_chunk_or_dataless ( dns_fd , touser , & users [ touser ] . q ) ;

 else {
 save_to_outpacketq ( touser , users [ userid ] . inpacket . data , users [ userid ] . inpacket . len ) ;

 }
 else {
 send_raw ( dns_fd , users [ userid ] . inpacket . data , users [ userid ] . inpacket . len , touser , RAW_HDR_CMD_DATA , & users [ touser ] . q ) ;
 }
 }
 }
 else {
 if ( debug >= 1 ) fprintf ( stderr , "Discarded data, uncompress() result: %d\n" , ret ) ;
 }
 users [ userid ] . inpacket . len = 0 ;
 users [ userid ] . inpacket . offset = 0 ;
 }