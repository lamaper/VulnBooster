static int dissect_diameter_eap_payload ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 gboolean save_writable ;
 save_writable = col_get_writable ( pinfo -> cinfo ) ;
 col_set_writable ( pinfo -> cinfo , FALSE ) ;
 call_dissector ( eap_handle , tvb , pinfo , tree ) ;
 col_set_writable ( pinfo -> cinfo , save_writable ) ;
 return tvb_reported_length ( tvb ) ;
 }