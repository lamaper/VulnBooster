guint16 de_cn_common_gsm_map_nas_sys_info ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_lac , tvb , curr_offset , 2 , ENC_BIG_ENDIAN ) ;
 curr_offset += 2 ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }