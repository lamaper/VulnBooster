bool message_decoder_decode_next_block ( struct message_decoder_context * ctx , struct message_block * input , struct message_block * output ) {
 if ( input -> part != ctx -> prev_part ) {
 message_decoder_decode_reset ( ctx ) ;
 }
 output -> part = input -> part ;
 ctx -> prev_part = input -> part ;
 if ( input -> hdr != NULL ) {
 output -> size = 0 ;
 return message_decode_header ( ctx , input -> hdr , output ) ;
 }
 else if ( input -> size != 0 ) return message_decode_body ( ctx , input , output ) ;
 else {
 output -> hdr = NULL ;
 output -> size = 0 ;
 message_decode_body_init_charset ( ctx , input -> part ) ;
 return TRUE ;
 }
 }