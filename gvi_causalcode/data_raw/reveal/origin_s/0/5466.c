void rtp_dyn_payload_replace ( rtp_dyn_payload_t * rtp_dyn_payload , const guint8 pt , const gchar * encoding_name , const int sample_rate ) {
 if ( rtp_dyn_payload && rtp_dyn_payload -> table ) {
 encoding_name_and_rate_t * encoding_name_and_rate_pt = wmem_new ( wmem_file_scope ( ) , encoding_name_and_rate_t ) ;
 encoding_name_and_rate_pt -> encoding_name = wmem_strdup ( wmem_file_scope ( ) , encoding_name ) ;
 encoding_name_and_rate_pt -> sample_rate = sample_rate ;
 g_hash_table_replace ( rtp_dyn_payload -> table , GUINT_TO_POINTER ( pt ) , encoding_name_and_rate_pt ) ;
 }
 }