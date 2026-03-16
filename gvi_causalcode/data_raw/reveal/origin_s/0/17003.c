guint16 de_cld_party_bcd_num ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string , int string_len ) {
 const gchar * extr_addr ;
 de_bcd_num ( tvb , tree , pinfo , offset , len , hf_gsm_a_dtap_cld_party_bcd_num , & extr_addr ) ;
 if ( extr_addr ) {
 if ( sccp_assoc && ! sccp_assoc -> called_party ) {
 sccp_assoc -> called_party = wmem_strdup ( wmem_file_scope ( ) , extr_addr ) ;
 }
 if ( add_string ) g_snprintf ( add_string , string_len , " - (%s)" , extr_addr ) ;
 }
 return ( len ) ;
 }