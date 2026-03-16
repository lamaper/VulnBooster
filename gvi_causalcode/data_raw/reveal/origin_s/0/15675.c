int dissect_coap_options ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * coap_tree , gint offset , gint offset_end , coap_info * coinfo , coap_common_dissect_t * dissect_hf ) {
 guint opt_num = 0 ;
 int i ;
 guint8 endmarker ;
 for ( i = 1 ;
 offset < offset_end ;
 i ++ ) {
 offset = dissect_coap_options_main ( tvb , pinfo , coap_tree , offset , i , & opt_num , offset_end , coinfo , dissect_hf ) ;
 if ( offset == - 1 ) return - 1 ;
 if ( offset >= offset_end ) break ;
 endmarker = tvb_get_guint8 ( tvb , offset ) ;
 if ( endmarker == 0xff ) {
 proto_tree_add_item ( coap_tree , dissect_hf -> hf . opt_end_marker , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 break ;
 }
 }
 return offset ;
 }