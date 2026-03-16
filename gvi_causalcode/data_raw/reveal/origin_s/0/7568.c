void message_decoder_decode_reset ( struct message_decoder_context * ctx ) {
 const char * error ;
 if ( ctx -> qp != NULL ) ( void ) qp_decoder_finish ( ctx -> qp , & error ) ;
 i_free_and_null ( ctx -> content_type ) ;
 i_free_and_null ( ctx -> content_charset ) ;
 ctx -> message_cte = MESSAGE_CTE_78BIT ;
 buffer_set_used_size ( ctx -> encoding_buf , 0 ) ;
 }