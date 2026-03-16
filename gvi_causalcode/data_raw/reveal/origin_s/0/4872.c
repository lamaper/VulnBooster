static void dissect_glabel_sdh ( proto_tree * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset ) {
 guint16 s ;
 guint8 u , k , l , m ;
 proto_tree * sonet_tree ;
 sonet_tree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset , 4 , TREE ( TT_SONET_SDH ) , NULL , "SONET/SDH Label" ) ;
 proto_tree_add_item ( sonet_tree , hf_rsvp_sonet_s , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( sonet_tree , hf_rsvp_sonet_u , tvb , offset + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( sonet_tree , hf_rsvp_sonet_k , tvb , offset + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( sonet_tree , hf_rsvp_sonet_l , tvb , offset + 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( sonet_tree , hf_rsvp_sonet_m , tvb , offset + 3 , 1 , ENC_BIG_ENDIAN ) ;
 s = tvb_get_ntohs ( tvb , offset ) ;
 u = ( ( tvb_get_guint8 ( tvb , offset + 2 ) & 0xF0 ) >> 4 ) ;
 k = ( ( tvb_get_guint8 ( tvb , offset + 2 ) & 0x0F ) >> 0 ) ;
 l = ( ( tvb_get_guint8 ( tvb , offset + 3 ) & 0xF0 ) >> 4 ) ;
 m = ( ( tvb_get_guint8 ( tvb , offset + 3 ) & 0x0F ) >> 0 ) ;
 proto_item_append_text ( ti , ": SONET/SDH: S=%u, U=%u, K=%u, L=%u, M=%u" , s , u , k , l , m ) ;
 }