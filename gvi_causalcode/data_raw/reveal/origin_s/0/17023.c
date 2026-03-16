static void process_downstream_ack ( int userid , int down_seq , int down_frag ) {
 if ( users [ userid ] . outpacket . len <= 0 ) return ;
 if ( users [ userid ] . outpacket . seqno != down_seq || users [ userid ] . outpacket . fragment != down_frag ) return ;
 users [ userid ] . outpacket . offset += users [ userid ] . outpacket . sentlen ;
 users [ userid ] . outpacket . sentlen = 0 ;
 users [ userid ] . outpacket . fragment ++ ;
 users [ userid ] . outfragresent = 0 ;
 if ( users [ userid ] . outpacket . offset >= users [ userid ] . outpacket . len ) {
 users [ userid ] . outpacket . len = 0 ;
 users [ userid ] . outpacket . offset = 0 ;
 users [ userid ] . outpacket . fragment -- ;


 }