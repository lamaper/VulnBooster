gboolean rtp_dyn_payload_remove ( rtp_dyn_payload_t * rtp_dyn_payload , const guint8 pt ) {
 return ( rtp_dyn_payload && rtp_dyn_payload -> table && g_hash_table_remove ( rtp_dyn_payload -> table , GUINT_TO_POINTER ( pt ) ) ) ;
 }