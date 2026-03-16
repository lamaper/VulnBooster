static void dissect_applemidi ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 guint16 command ;
 if ( test_applemidi ( tvb , & command , TRUE ) ) dissect_applemidi_common ( tvb , pinfo , tree , command ) ;
 else call_dissector ( rtp_handle , tvb , pinfo , tree ) ;
 }