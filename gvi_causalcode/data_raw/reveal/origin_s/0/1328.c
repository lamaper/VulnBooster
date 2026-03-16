static void dissect_rsvp_juniper ( proto_tree * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 proto_item * hidden_item ;
 hidden_item = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_JUNIPER ] , tvb , offset , obj_length , ENC_NA ) ;
 PROTO_ITEM_SET_HIDDEN ( hidden_item ) ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 offset += 4 ;
 if ( type == 1 ) {
 guint tlvs , pad ;
 tlvs = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_numtlvs , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 pad = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_padlength , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 while ( tlvs > 0 ) {
 guint8 t , l ;
 t = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 l = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 switch ( t ) {
 case 0x01 : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_attrib_cos , tvb , offset , l - 2 , ENC_BIG_ENDIAN ) ;
 offset += ( l - 2 ) ;
 break ;
 case 0x02 : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_attrib_metric1 , tvb , offset , l - 2 , ENC_BIG_ENDIAN ) ;
 offset += ( l - 2 ) ;
 break ;
 case 0x04 : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_attrib_metric2 , tvb , offset , l - 2 , ENC_BIG_ENDIAN ) ;
 offset += ( l - 2 ) ;
 break ;
 case 0x08 : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_attrib_ccc_status , tvb , offset , l - 2 , ENC_BIG_ENDIAN ) ;
 offset += ( l - 2 ) ;
 break ;
 case 0x10 : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_attrib_path , tvb , offset , l - 2 , ENC_BIG_ENDIAN ) ;
 offset += ( l - 2 ) ;
 break ;
 default : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_attrib_unknown , tvb , offset , l - 2 , ENC_NA ) ;
 offset += ( l - 2 ) ;
 break ;
 }
 tlvs -- ;
 }
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_pad , tvb , offset , pad , ENC_NA ) ;
 }
 else if ( obj_length > 4 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_juniper_unknown , tvb , offset , obj_length , ENC_NA ) ;
 }
 }