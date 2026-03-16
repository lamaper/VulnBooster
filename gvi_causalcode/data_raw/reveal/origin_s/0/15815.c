static int dissect_rtmpt_tcp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 conversation_t * conv ;
 rtmpt_conv_t * rconv ;
 int cdir ;
 struct tcpinfo * tcpinfo ;
 if ( data == NULL ) {
 return 0 ;
 }
 tcpinfo = ( struct tcpinfo * ) data ;
 conv = find_or_create_conversation ( pinfo ) ;
 rconv = ( rtmpt_conv_t * ) conversation_get_proto_data ( conv , proto_rtmpt ) ;
 if ( ! rconv ) {
 rconv = rtmpt_init_rconv ( conv ) ;
 }
 cdir = ( addresses_equal ( & conv -> key_ptr -> addr1 , & pinfo -> src ) && addresses_equal ( & conv -> key_ptr -> addr2 , & pinfo -> dst ) && conv -> key_ptr -> port1 == pinfo -> srcport && conv -> key_ptr -> port2 == pinfo -> destport ) ? 0 : 1 ;
 dissect_rtmpt_common ( tvb , pinfo , tree , rconv , cdir , tcpinfo -> seq , tcpinfo -> lastackseq ) ;
 return tvb_reported_length ( tvb ) ;
 }