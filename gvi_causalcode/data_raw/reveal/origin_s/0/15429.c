static void ctl_error ( u_char errcode ) {
 int maclen ;
 numctlerrors ++ ;
 DPRINTF ( 3 , ( "sending control error %u\n" , errcode ) ) ;
 rpkt . r_m_e_op = ( u_char ) CTL_RESPONSE | CTL_ERROR | ( res_opcode & CTL_OP_MASK ) ;
 rpkt . status = htons ( ( u_short ) ( errcode << 8 ) & 0xff00 ) ;
 rpkt . count = 0 ;
 if ( res_authenticate && sys_authenticate ) {
 maclen = authencrypt ( res_keyid , ( u_int32 * ) & rpkt , CTL_HEADER_LEN ) ;
 sendpkt ( rmt_addr , lcl_inter , - 2 , ( void * ) & rpkt , CTL_HEADER_LEN + maclen ) ;
 }
 else sendpkt ( rmt_addr , lcl_inter , - 3 , ( void * ) & rpkt , CTL_HEADER_LEN ) ;
 }