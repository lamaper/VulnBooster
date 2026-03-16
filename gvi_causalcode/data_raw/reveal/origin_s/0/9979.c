void proto_reg_handoff_btavdtp ( void ) {
 dissector_add_string ( "bluetooth.uuid" , "19" , btavdtp_handle ) ;
 dissector_add_uint ( "btl2cap.psm" , BTL2CAP_PSM_AVDTP , btavdtp_handle ) ;
 dissector_add_for_decode_as ( "btl2cap.cid" , btavdtp_handle ) ;
 }