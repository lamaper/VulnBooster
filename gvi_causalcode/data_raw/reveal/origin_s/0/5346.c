static int dissect_mac_fdd_edch_type2 ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 guint sdu_no , subframe_bytes = 0 , offset = 0 ;
 guint8 ss ;
 guint16 tsn ;
 proto_item * pi , * temp ;
 proto_tree * macis_pdu_tree , * macis_sdu_tree ;
 umts_mac_is_info * mac_is_info = ( umts_mac_is_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_umts_mac , 0 ) ;
 rlc_info * rlcinf = ( rlc_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_rlc , 0 ) ;
 struct fp_info * p_fp_info = ( struct fp_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_fp , 0 ) ;
 DISSECTOR_ASSERT ( mac_is_info != NULL && rlcinf != NULL && p_fp_info != NULL ) ;
 pi = proto_tree_add_item ( tree , proto_umts_mac , tvb , 0 , - 1 , ENC_NA ) ;
 macis_pdu_tree = proto_item_add_subtree ( pi , ett_mac_edch_type2 ) ;
 ss = ( tvb_get_guint8 ( tvb , offset ) & 0xc0 ) >> 6 ;
 proto_tree_add_item ( macis_pdu_tree , hf_mac_edch_type2_ss , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 ss_interpretation ( tvb , macis_pdu_tree , ss , mac_is_info -> number_of_mac_is_sdus , offset ) ;
 tsn = tvb_get_bits8 ( tvb , offset * 8 + 2 , mac_tsn_size ) ;
 proto_tree_add_bits_item ( macis_pdu_tree , hf_mac_edch_type2_tsn , tvb , offset * 8 + 2 , mac_tsn_size , ENC_BIG_ENDIAN ) ;
 offset += ( 2 + mac_tsn_size ) / 8 ;
 for ( sdu_no = 0 ;
 sdu_no < mac_is_info -> number_of_mac_is_sdus ;
 sdu_no ++ ) {
 proto_item * ti ;
 tvbuff_t * asm_tvb ;
 guint8 lchid = mac_is_info -> lchid [ sdu_no ] + 1 ;
 guint sdulength = mac_is_info -> sdulength [ sdu_no ] ;
 ti = proto_tree_add_item ( tree , hf_mac_edch_type2_sdu , tvb , offset , sdulength , ENC_NA ) ;
 macis_sdu_tree = proto_item_add_subtree ( ti , ett_mac_edch_type2_sdu ) ;
 proto_item_append_text ( ti , " (Logical channel=%u, Len=%u)" , lchid , sdulength ) ;
 temp = proto_tree_add_uint ( ti , hf_mac_lch_id , tvb , 0 , 0 , lchid ) ;
 PROTO_ITEM_SET_GENERATED ( temp ) ;
 rlcinf -> mode [ sdu_no ] = lchId_rlc_map [ lchid ] ;
 rlcinf -> urnti [ sdu_no ] = p_fp_info -> com_context_id ;
 rlcinf -> rbid [ sdu_no ] = lchid ;
 rlcinf -> li_size [ sdu_no ] = RLC_LI_7BITS ;
 rlcinf -> ciphered [ sdu_no ] = FALSE ;
 rlcinf -> deciphered [ sdu_no ] = FALSE ;
 asm_tvb = mac_is_add_fragment ( tvb , pinfo , macis_sdu_tree , lchid , p_fp_info -> com_context_id , offset , ss , tsn , sdu_no , mac_is_info -> number_of_mac_is_sdus , sdulength ) ;
 if ( asm_tvb != NULL ) {
 call_rlc ( asm_tvb , pinfo , tree , ti , lchid , data ) ;
 }
 offset += sdulength ;
 subframe_bytes += sdulength ;
 }
 proto_item_append_text ( pi , "-is PDU (SS=%u, TSN=%u, %u bytes in %u SDU fragments)" , ss , tsn , subframe_bytes , mac_is_info -> number_of_mac_is_sdus ) ;
 proto_item_set_len ( pi , 1 + subframe_bytes ) ;
 return tvb_captured_length ( tvb ) ;
 }