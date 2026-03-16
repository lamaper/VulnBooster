static guint16 tree_add_common_dcch_dtch_fields ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , guint16 bitoffs , fp_info * fpinf , umts_mac_info * macinf , rlc_info * rlcinf ) {
 guint8 ueid_type ;
 ueid_type = tvb_get_bits8 ( tvb , bitoffs , 2 ) ;
 proto_tree_add_bits_item ( tree , hf_mac_ueid_type , tvb , bitoffs , 2 , ENC_BIG_ENDIAN ) ;
 bitoffs += 2 ;
 if ( ueid_type == MAC_UEID_TYPE_URNTI ) {
 proto_tree_add_bits_item ( tree , hf_mac_urnti , tvb , bitoffs , 32 , ENC_BIG_ENDIAN ) ;
 rlcinf -> urnti [ fpinf -> cur_tb ] = tvb_get_bits32 ( tvb , bitoffs , 32 , ENC_BIG_ENDIAN ) ;
 bitoffs += 32 ;
 }
 else if ( ueid_type == MAC_UEID_TYPE_CRNTI ) {
 proto_tree_add_bits_item ( tree , hf_mac_crnti , tvb , 4 , 16 , ENC_BIG_ENDIAN ) ;
 rlcinf -> urnti [ fpinf -> cur_tb ] = tvb_get_bits16 ( tvb , bitoffs , 16 , ENC_BIG_ENDIAN ) ;
 bitoffs += 16 ;
 }
 if ( macinf -> ctmux [ fpinf -> cur_tb ] ) {
 proto_item * temp ;
 if ( rlcinf ) {
 rlcinf -> rbid [ fpinf -> cur_tb ] = tvb_get_bits8 ( tvb , bitoffs , 4 ) + 1 ;
 }
 proto_tree_add_bits_item ( tree , hf_mac_ct , tvb , bitoffs , 4 , ENC_BIG_ENDIAN ) ;
 bitoffs += 4 ;
 if ( rlcinf ) {
 temp = proto_tree_add_uint ( tree , hf_mac_lch_id , tvb , 0 , 0 , rlcinf -> rbid [ fpinf -> cur_tb ] ) ;
 PROTO_ITEM_SET_GENERATED ( temp ) ;
 }
 }
 return bitoffs ;
 }