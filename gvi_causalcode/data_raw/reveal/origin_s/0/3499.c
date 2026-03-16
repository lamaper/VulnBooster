static void rsvp_init_protocol ( void ) {
 rsvp_request_hash = g_hash_table_new ( rsvp_hash , rsvp_equal ) ;
 }