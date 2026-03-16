static guint16 de_ss_ver_ind ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct ;
 guint32 curr_offset ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_ss_version_indicator , tvb , curr_offset , 1 , oct , "%s" , val_to_str_const ( oct , gsm_a_dtap_ss_ver_ind_vals , "Reserved" ) ) ;
 curr_offset ++ ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }