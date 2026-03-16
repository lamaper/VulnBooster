static void ctl_flushpkt ( u_char more ) {
 size_t i ;
 int dlen ;
 int sendlen ;
 int maclen ;
 int totlen ;
 keyid_t keyid ;
 dlen = datapt - rpkt . u . data ;
 if ( ! more && datanotbinflag && dlen + 2 < CTL_MAX_DATA_LEN ) {
 * datapt ++ = '\r' ;
 * datapt ++ = '\n' ;
 dlen += 2 ;
 }
 sendlen = dlen + CTL_HEADER_LEN ;
 while ( sendlen & 0x3 ) {
 * datapt ++ = '\0' ;
 sendlen ++ ;
 }
 rpkt . r_m_e_op = CTL_RESPONSE | more | ( res_opcode & CTL_OP_MASK ) ;
 rpkt . count = htons ( ( u_short ) dlen ) ;
 rpkt . offset = htons ( ( u_short ) res_offset ) ;
 if ( res_async ) {
 for ( i = 0 ;
 i < COUNTOF ( ctl_traps ) ;
 i ++ ) {
 if ( TRAP_INUSE & ctl_traps [ i ] . tr_flags ) {
 rpkt . li_vn_mode = PKT_LI_VN_MODE ( sys_leap , ctl_traps [ i ] . tr_version , MODE_CONTROL ) ;
 rpkt . sequence = htons ( ctl_traps [ i ] . tr_sequence ) ;
 sendpkt ( & ctl_traps [ i ] . tr_addr , ctl_traps [ i ] . tr_localaddr , - 4 , ( struct pkt * ) & rpkt , sendlen ) ;
 if ( ! more ) ctl_traps [ i ] . tr_sequence ++ ;
 numasyncmsgs ++ ;
 }
 }
 }
 else {
 if ( res_authenticate && sys_authenticate ) {
 totlen = sendlen ;
 while ( totlen & 7 ) {
 * datapt ++ = '\0' ;
 totlen ++ ;
 }
 keyid = htonl ( res_keyid ) ;
 memcpy ( datapt , & keyid , sizeof ( keyid ) ) ;
 maclen = authencrypt ( res_keyid , ( u_int32 * ) & rpkt , totlen ) ;
 sendpkt ( rmt_addr , lcl_inter , - 5 , ( struct pkt * ) & rpkt , totlen + maclen ) ;
 }
 else {
 sendpkt ( rmt_addr , lcl_inter , - 6 , ( struct pkt * ) & rpkt , sendlen ) ;
 }
 if ( more ) numctlfrags ++ ;
 else numctlresponses ++ ;
 }
 res_frags ++ ;
 res_offset += dlen ;
 datapt = rpkt . u . data ;
 }