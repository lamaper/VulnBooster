static void dissect_glabel_g709 ( proto_tree * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset ) {
 guint8 t1 , t2 , t3 ;
 proto_tree * g709_tree ;
 g709_tree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset , 4 , TREE ( TT_G709 ) , NULL , "G.709 ODUk Label" ) ;
 proto_tree_add_item ( g709_tree , hf_rsvp_g709_t3 , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( g709_tree , hf_rsvp_g709_t2 , tvb , offset + 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( g709_tree , hf_rsvp_g709_t1 , tvb , offset + 3 , 1 , ENC_BIG_ENDIAN ) ;
 t2 = ( ( tvb_get_guint8 ( tvb , offset + 3 ) & 0x0E ) >> 1 ) ;
 t1 = ( ( tvb_get_guint8 ( tvb , offset + 3 ) & 0x01 ) >> 0 ) ;
 t3 = ( ( tvb_get_guint8 ( tvb , offset + 2 ) & 0x03 ) << 4 ) ;
 t3 |= ( ( tvb_get_guint8 ( tvb , offset + 3 ) & 0xF0 ) >> 4 ) ;
 proto_item_append_text ( ti , ": G.709 ODUk: " "t3=%u, " "t2=%u, " "t1=%u" , t3 , t2 , t1 ) ;
 }