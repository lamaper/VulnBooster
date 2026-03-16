void message_decoder_set_return_binary ( struct message_decoder_context * ctx , bool set ) {
 if ( set ) ctx -> flags |= MESSAGE_DECODER_FLAG_RETURN_BINARY ;
 else ctx -> flags &= ~ MESSAGE_DECODER_FLAG_RETURN_BINARY ;
 message_decode_body_init_charset ( ctx , ctx -> prev_part ) ;
 }