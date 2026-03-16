static guint16 de_repeat_ind ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct ;
 guint32 curr_offset ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_repeat_indicator , tvb , curr_offset , 1 , oct , "%s" , val_to_str_const ( oct & 0xF , gsm_a_dtap_repeat_indicator_vals , "Reserved" ) ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }