static int send_chunk_or_dataless ( int dns_fd , int userid , struct query * q ) {
 char pkt [ 4096 ] ;
 int datalen = 0 ;
 int last = 0 ;
 if ( users [ userid ] . outpacket . len > 0 && users [ userid ] . outfragresent > 5 ) {
 users [ userid ] . outpacket . len = 0 ;
 users [ userid ] . outpacket . offset = 0 ;
 users [ userid ] . outpacket . sentlen = 0 ;
 users [ userid ] . outfragresent = 0 ;


 if ( users [ userid ] . outpacket . len > 0 ) {
 datalen = MIN ( users [ userid ] . fragsize , users [ userid ] . outpacket . len - users [ userid ] . outpacket . offset ) ;
 datalen = MIN ( datalen , sizeof ( pkt ) - 2 ) ;
 memcpy ( & pkt [ 2 ] , users [ userid ] . outpacket . data + users [ userid ] . outpacket . offset , datalen ) ;
 users [ userid ] . outpacket . sentlen = datalen ;
 last = ( users [ userid ] . outpacket . len == users [ userid ] . outpacket . offset + datalen ) ;
 users [ userid ] . outfragresent ++ ;
 }
 pkt [ 0 ] = ( 1 << 7 ) | ( ( users [ userid ] . inpacket . seqno & 7 ) << 4 ) | ( users [ userid ] . inpacket . fragment & 15 ) ;
 pkt [ 1 ] = ( ( users [ userid ] . outpacket . seqno & 7 ) << 5 ) | ( ( users [ userid ] . outpacket . fragment & 15 ) << 1 ) | ( last & 1 ) ;
 if ( debug >= 1 ) {
 fprintf ( stderr , "OUT pkt seq# %d, frag %d (last=%d), offset %d, fragsize %d, total %d, to user %d\n" , users [ userid ] . outpacket . seqno & 7 , users [ userid ] . outpacket . fragment & 15 , last , users [ userid ] . outpacket . offset , datalen , users [ userid ] . outpacket . len , userid ) ;
 }
 write_dns ( dns_fd , q , pkt , datalen + 2 , users [ userid ] . downenc ) ;
 if ( q -> id2 != 0 ) {
 q -> id = q -> id2 ;
 q -> fromlen = q -> fromlen2 ;
 memcpy ( & ( q -> from ) , & ( q -> from2 ) , q -> fromlen2 ) ;
 if ( debug >= 1 ) fprintf ( stderr , "OUT again to last duplicate\n" ) ;
 write_dns ( dns_fd , q , pkt , datalen + 2 , users [ userid ] . downenc ) ;
 }
 save_to_qmem_pingordata ( userid , q ) ;


 if ( datalen > 0 && datalen == users [ userid ] . outpacket . len ) {
 users [ userid ] . outpacket . len = 0 ;
 users [ userid ] . outpacket . offset = 0 ;
 users [ userid ] . outpacket . sentlen = 0 ;
 users [ userid ] . outfragresent = 0 ;

 if ( debug >= 3 ) fprintf ( stderr , " Chunk & fromqueue: callagain\n" ) ;
 return 1 ;
 }

 return 0 ;
 }