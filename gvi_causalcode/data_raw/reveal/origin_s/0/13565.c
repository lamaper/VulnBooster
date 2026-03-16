static guint16 de_lsa_id ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 if ( len == 0 ) {
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_lsa_id , tvb , curr_offset , len , 0 , "not included" ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_lsa_id , tvb , curr_offset , 3 , ENC_BIG_ENDIAN ) ;
 }
 curr_offset += len ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }