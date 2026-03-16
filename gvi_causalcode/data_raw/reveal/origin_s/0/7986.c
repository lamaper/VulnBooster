const gchar * rtp_dyn_payload_get_name ( rtp_dyn_payload_t * rtp_dyn_payload , const guint8 pt ) {
 encoding_name_and_rate_t * encoding_name_and_rate_pt ;
 if ( ! rtp_dyn_payload || ! rtp_dyn_payload -> table ) return NULL ;
 encoding_name_and_rate_pt = ( encoding_name_and_rate_t * ) g_hash_table_lookup ( rtp_dyn_payload -> table , GUINT_TO_POINTER ( pt ) ) ;
 return ( encoding_name_and_rate_pt ? encoding_name_and_rate_pt -> encoding_name : NULL ) ;
 }