static guint16 de_cp_user_data ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 tvbuff_t * rp_tvb ;
 curr_offset = offset ;
 proto_tree_add_bytes_format ( tree , hf_gsm_a_dtap_rpdu , tvb , curr_offset , len , NULL , "RPDU (not displayed)" ) ;
 rp_tvb = tvb_new_subset_length ( tvb , curr_offset , len ) ;
 call_dissector ( rp_handle , rp_tvb , pinfo , g_tree ) ;
 curr_offset += len ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }