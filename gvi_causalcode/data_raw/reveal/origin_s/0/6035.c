static guint16 de_facility ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint fac_len , gchar * add_string _U_ , int string_len _U_ ) {
 guint saved_offset ;
 gint8 appclass ;
 gboolean pc ;
 gboolean ind = FALSE ;
 guint32 component_len = 0 ;
 guint32 header_end_offset ;
 guint32 header_len ;
 asn1_ctx_t asn1_ctx ;
 tvbuff_t * SS_tvb = NULL ;
 static gint comp_type_tag ;
 asn1_ctx_init ( & asn1_ctx , ASN1_ENC_BER , TRUE , pinfo ) ;
 saved_offset = offset ;
 col_append_str ( pinfo -> cinfo , COL_PROTOCOL , "/" ) ;
 col_set_fence ( pinfo -> cinfo , COL_PROTOCOL ) ;
 while ( fac_len > ( offset - saved_offset ) ) {
 header_end_offset = get_ber_identifier ( tvb , offset , & appclass , & pc , & comp_type_tag ) ;
 header_end_offset = get_ber_length ( tvb , header_end_offset , & component_len , & ind ) ;
 header_len = header_end_offset - offset ;
 component_len = header_len + component_len ;
 SS_tvb = tvb_new_subset_length ( tvb , offset , component_len ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "(GSM MAP) " ) ;
 col_set_fence ( pinfo -> cinfo , COL_INFO ) ;
 call_dissector ( gsm_map_handle , SS_tvb , pinfo , tree ) ;
 offset = offset + component_len ;
 }
 return ( fac_len ) ;
 }