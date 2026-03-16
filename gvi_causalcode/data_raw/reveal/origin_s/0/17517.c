static guint16 de_ca_of_no_cli ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string , int string_len ) {
 guint32 curr_offset ;
 guint8 oct ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_cause_of_no_cli , tvb , curr_offset , 1 , oct , "%s (%u)" , val_to_str_const ( oct , gsm_a_cause_of_no_cli_values , "Unavailable" ) , oct ) ;
 curr_offset ++ ;
 if ( add_string ) g_snprintf ( add_string , string_len , " - (%s)" , val_to_str_const ( oct , gsm_a_cause_of_no_cli_values , "Unavailable" ) ) ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( len ) ;
 }