static void dissect_rsvp_vendor_private_use ( proto_tree * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 proto_item * hidden_item ;
 hidden_item = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_PRIVATE_OBJ ] , tvb , offset , obj_length , ENC_NA ) ;
 PROTO_ITEM_SET_HIDDEN ( hidden_item ) ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_ENT_CODE ] , tvb , offset + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_private_data , tvb , offset + 8 , obj_length - 8 , ENC_NA ) ;
 }