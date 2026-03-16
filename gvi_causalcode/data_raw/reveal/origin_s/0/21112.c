static int tunnel_tun ( int tun_fd , int dns_fd ) {
 unsigned long outlen ;
 struct ip * header ;
 char out [ 64 * 1024 ] ;
 char in [ 64 * 1024 ] ;
 int userid ;
 int read ;
 if ( ( read = read_tun ( tun_fd , in , sizeof ( in ) ) ) <= 0 ) return 0 ;
 header = ( struct ip * ) ( in + 4 ) ;
 userid = find_user_by_ip ( header -> ip_dst . s_addr ) ;
 if ( userid < 0 ) return 0 ;
 outlen = sizeof ( out ) ;
 compress2 ( ( uint8_t * ) out , & outlen , ( uint8_t * ) in , read , 9 ) ;
 if ( users [ userid ] . conn == CONN_DNS_NULL ) {

 save_to_outpacketq ( userid , out , outlen ) ;
 return 0 ;
 }

 if ( users [ userid ] . q_sendrealsoon . id != 0 ) send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q_sendrealsoon ) ;
 else if ( users [ userid ] . q . id != 0 ) send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q ) ;
 return outlen ;
 }
 else {
 send_raw ( dns_fd , out , outlen , userid , RAW_HDR_CMD_DATA , & users [ userid ] . q ) ;
 return outlen ;
 }
 }