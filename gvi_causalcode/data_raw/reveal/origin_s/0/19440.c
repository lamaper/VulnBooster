static void dissect_rsvp_call_attributes ( proto_tree * ti _U_ , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length _U_ , int rsvp_class _U_ , int type _U_ ) {
 int offset2 = offset + 4 ;
 guint16 tlv_type ;
 guint16 tlv_len ;
 tlv_type = tvb_get_ntohs ( tvb , offset2 ) ;
 tlv_len = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 if ( tlv_len < 4 ) {
 proto_tree_add_expert_format ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , offset2 + 2 , 2 , "Invalid TLV length" ) ;
 return ;
 }
 switch ( tlv_type ) {
 case 2 : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_attributes_endpont_id , tvb , offset2 + 4 , tlv_len - 4 , ENC_NA | ENC_ASCII ) ;
 break ;
 }
 }