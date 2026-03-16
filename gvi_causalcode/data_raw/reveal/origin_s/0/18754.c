static int fix_pseudo_header ( int encap , Buffer * buf , int len , union wtap_pseudo_header * pseudo_header ) {
 const guint8 * pd ;
 pd = ws_buffer_start_ptr ( buf ) ;
 switch ( encap ) {
 case WTAP_ENCAP_PER_PACKET : encap = infer_pkt_encap ( pd , len ) ;
 switch ( encap ) {
 case WTAP_ENCAP_WFLEET_HDLC : case WTAP_ENCAP_CHDLC_WITH_PHDR : case WTAP_ENCAP_PPP_WITH_PHDR : if ( pseudo_header -> x25 . flags == 0 ) pseudo_header -> p2p . sent = TRUE ;
 else pseudo_header -> p2p . sent = FALSE ;
 break ;
 case WTAP_ENCAP_ISDN : if ( pseudo_header -> x25 . flags == 0x00 ) pseudo_header -> isdn . uton = FALSE ;
 else pseudo_header -> isdn . uton = TRUE ;
 pseudo_header -> isdn . channel = 0 ;
 break ;
 }
 break ;
 case WTAP_ENCAP_ATM_PDUS : if ( pseudo_header -> atm . type == TRAF_LANE && len >= 2 ) {
 if ( pd [ 0 ] == 0xff && pd [ 1 ] == 0x00 ) {
 pseudo_header -> atm . subtype = TRAF_ST_LANE_LE_CTRL ;
 }
 else {
 if ( pseudo_header -> atm . subtype == TRAF_ST_LANE_LE_CTRL ) {
 pseudo_header -> atm . subtype = TRAF_ST_LANE_802_3 ;
 }
 }
 }
 break ;
 }
 return encap ;
 }