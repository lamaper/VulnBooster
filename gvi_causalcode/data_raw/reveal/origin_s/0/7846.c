static void dissect_rsvp_integrity ( proto_item * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 proto_tree * ti2 , * rsvp_integ_flags_tree ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_integrity_flags , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_integ_flags_tree = proto_item_add_subtree ( ti2 , TREE ( TT_INTEGRITY_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_integ_flags_tree , hf_rsvp_integrity_flags_handshake , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_integrity_key_identifier , tvb , offset2 + 2 , 6 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_integrity_sequence_number , tvb , offset2 + 8 , 8 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_integrity_hash , tvb , offset2 + 16 , obj_length - 20 , ENC_NA ) ;
 }