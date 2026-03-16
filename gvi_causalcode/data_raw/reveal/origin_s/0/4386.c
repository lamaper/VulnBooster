static guint16 de_cp_cause ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string , int string_len ) {
 guint8 oct ;
 guint32 curr_offset ;
 const gchar * str ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 str = val_to_str_const ( oct , gsm_a_dtap_cp_cause_values , "Reserved, treat as Protocol error, unspecified" ) ;
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_cp_cause , tvb , curr_offset , 1 , oct , "(%u) %s" , oct , str ) ;
 curr_offset ++ ;
 if ( add_string ) g_snprintf ( add_string , string_len , " - (%u) %s" , oct , str ) ;
 return ( curr_offset - offset ) ;
 }