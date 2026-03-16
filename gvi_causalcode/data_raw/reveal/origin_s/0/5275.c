static void dissect_glabel_evpl ( proto_tree * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset ) {
 int bit_offset ;
 guint16 vlan_id = ( ( tvb_get_ntohs ( tvb , offset ) << 4 ) & 0xFFFF ) ;
 bit_offset = ( offset << 2 ) + 3 ;
 proto_tree_add_bits_item ( rsvp_object_tree , hf_rsvp_label_generalized_label_evpl_vlad_id , tvb , bit_offset , 12 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , ": EVPL Generalized Label: " "VLAN ID = %u" , vlan_id ) ;
 }