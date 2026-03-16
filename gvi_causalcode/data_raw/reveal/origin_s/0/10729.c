static guint16 de_tp_ms_positioning_technology ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guchar oct ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_ms_positioning_technology , tvb , curr_offset , 1 , oct , "%s" , val_to_str ( oct , gsm_positioning_technology_vals , "Reserved (%d)" ) ) ;
 curr_offset += 1 ;
 return ( curr_offset - offset ) ;
 }