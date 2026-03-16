static gboolean wmem_rtp_dyn_payload_destroy_cb ( wmem_allocator_t * allocator _U_ , wmem_cb_event_t event _U_ , void * user_data _U_ ) {
 g_assert ( rtp_dyn_payloads ) ;
 DPRINT ( ( "destroying %u remaining rtp_dyn_payload_t's" , g_hash_table_size ( rtp_dyn_payloads ) ) ) ;
 g_hash_table_foreach_steal ( rtp_dyn_payloads , rtp_dyn_payloads_table_steal_func , NULL ) ;
 g_hash_table_destroy ( rtp_dyn_payloads ) ;
 rtp_dyn_payloads = NULL ;
 return FALSE ;
 }