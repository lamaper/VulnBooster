static void start_new_outpacket ( int userid , char * data , int datalen ) {
 datalen = MIN ( datalen , sizeof ( users [ userid ] . outpacket . data ) ) ;
 memcpy ( users [ userid ] . outpacket . data , data , datalen ) ;
 users [ userid ] . outpacket . len = datalen ;
 users [ userid ] . outpacket . offset = 0 ;
 users [ userid ] . outpacket . sentlen = 0 ;
 users [ userid ] . outpacket . seqno = ( users [ userid ] . outpacket . seqno + 1 ) & 7 ;
 users [ userid ] . outpacket . fragment = 0 ;
 users [ userid ] . outfragresent = 0 ;
 }