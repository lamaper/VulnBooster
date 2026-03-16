static guint16 de_tp_epc_ellipsoid_point_with_alt ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint32 longitude ;
 curr_offset = offset ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_latitude_sign , tvb , curr_offset << 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_degrees_latitude , tvb , ( curr_offset << 3 ) + 1 , 23 , ENC_BIG_ENDIAN ) ;
 curr_offset += 3 ;
 longitude = tvb_get_ntoh24 ( tvb , curr_offset ) ;
 proto_tree_add_int_format ( tree , hf_gsm_a_dtap_epc_degrees_longitude , tvb , curr_offset , 3 , longitude , "%s = %s: %d" , decode_bits_in_field ( curr_offset << 3 , 24 , longitude ) , proto_registrar_get_name ( hf_gsm_a_dtap_epc_degrees_longitude ) , longitude - 8388608 ) ;
 curr_offset += 3 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_altitude_dir , tvb , curr_offset << 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_altitude , tvb , ( curr_offset << 3 ) + 1 , 15 , ENC_BIG_ENDIAN ) ;
 curr_offset += 2 ;
 return ( curr_offset - offset ) ;
 }