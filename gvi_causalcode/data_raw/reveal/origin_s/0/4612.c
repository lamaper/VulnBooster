struct message_decoder_context * message_decoder_init ( normalizer_func_t * normalizer , enum message_decoder_flags flags ) {
 struct message_decoder_context * ctx ;
 ctx = i_new ( struct message_decoder_context , 1 ) ;
 ctx -> flags = flags ;
 ctx -> normalizer = normalizer ;
 ctx -> buf = buffer_create_dynamic ( default_pool , 8192 ) ;
 ctx -> buf2 = buffer_create_dynamic ( default_pool , 8192 ) ;
 ctx -> encoding_buf = buffer_create_dynamic ( default_pool , 128 ) ;
 return ctx ;
 }