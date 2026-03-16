gboolean rtp_dyn_payload_get_full ( rtp_dyn_payload_t * rtp_dyn_payload , const guint8 pt , const gchar * * encoding_name , int * sample_rate ) {
 encoding_name_and_rate_t * encoding_name_and_rate_pt ;
 * encoding_name = NULL ;
 * sample_rate = 0 ;
 if ( ! rtp_dyn_payload || ! rtp_dyn_payload -> table ) return FALSE ;
 encoding_name_and_rate_pt = ( encoding_name_and_rate_t * ) g_hash_table_lookup ( rtp_dyn_payload -> table , GUINT_TO_POINTER ( pt ) ) ;
 if ( encoding_name_and_rate_pt ) {
 * encoding_name = encoding_name_and_rate_pt -> encoding_name ;
 * sample_rate = encoding_name_and_rate_pt -> sample_rate ;
 }
 return ( encoding_name_and_rate_pt != NULL ) ;
 }