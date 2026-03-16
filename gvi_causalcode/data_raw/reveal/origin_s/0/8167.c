guint16 de_rej_cause ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct ;
 const gchar * str ;
 oct = tvb_get_guint8 ( tvb , offset ) ;
 str = try_rval_to_str ( oct , gsm_a_dtap_rej_cause_vals ) ;
 if ( ! str ) {
 if ( is_uplink == IS_UPLINK_TRUE ) str = "Protocol error, unspecified" ;
 else str = "Service option temporarily out of order" ;
 }
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_rej_cause , tvb , offset , 1 , oct , "%s (%u)" , str , oct ) ;
 return ( 1 ) ;
 }