static int dissect_diameter_tcp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 gint is_diam = check_diameter ( tvb ) ;
 if ( is_diam == NOT_DIAMETER ) {
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "DIAMETER" ) ;
 col_set_str ( pinfo -> cinfo , COL_INFO , "Continuation" ) ;
 call_dissector ( data_handle , tvb , pinfo , tree ) ;
 }
 else if ( is_diam == NOT_ENOUGH_DATA ) {
 pinfo -> desegment_offset = 0 ;
 pinfo -> desegment_len = DESEGMENT_ONE_MORE_SEGMENT ;
 }
 else {
 tcp_dissect_pdus ( tvb , pinfo , tree , gbl_diameter_desegment , 4 , get_diameter_pdu_len , dissect_diameter_common , data ) ;
 }
 return tvb_reported_length ( tvb ) ;
 }