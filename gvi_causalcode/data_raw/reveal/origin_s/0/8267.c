static bool message_decode_body ( struct message_decoder_context * ctx , struct message_block * input , struct message_block * output ) {
 const unsigned char * data = NULL ;
 size_t pos = 0 , size = 0 ;
 const char * error ;
 int ret ;
 if ( ctx -> encoding_buf -> used != 0 ) buffer_append ( ctx -> encoding_buf , input -> data , input -> size ) ;
 switch ( ctx -> message_cte ) {
 case MESSAGE_CTE_UNKNOWN : return FALSE ;
 case MESSAGE_CTE_78BIT : case MESSAGE_CTE_BINARY : i_assert ( ctx -> encoding_buf -> used == 0 ) ;
 data = input -> data ;
 size = pos = input -> size ;
 break ;
 case MESSAGE_CTE_QP : {
 i_assert ( ctx -> encoding_buf -> used == 0 ) ;
 buffer_set_used_size ( ctx -> buf , 0 ) ;
 if ( ctx -> qp == NULL ) ctx -> qp = qp_decoder_init ( ctx -> buf ) ;
 ( void ) qp_decoder_more ( ctx -> qp , input -> data , input -> size , & pos , & error ) ;
 data = ctx -> buf -> data ;
 size = ctx -> buf -> used ;
 pos = input -> size ;
 break ;
 }
 case MESSAGE_CTE_BASE64 : buffer_set_used_size ( ctx -> buf , 0 ) ;
 if ( ctx -> encoding_buf -> used != 0 ) {
 ret = base64_decode ( ctx -> encoding_buf -> data , ctx -> encoding_buf -> used , & pos , ctx -> buf ) ;
 }
 else {
 ret = base64_decode ( input -> data , input -> size , & pos , ctx -> buf ) ;
 }
 if ( ret < 0 ) {
 return FALSE ;
 }
 if ( ret == 0 ) {
 pos = input -> size ;
 buffer_set_used_size ( ctx -> encoding_buf , 0 ) ;
 }
 data = ctx -> buf -> data ;
 size = ctx -> buf -> used ;
 break ;
 }
 if ( ctx -> encoding_buf -> used != 0 ) buffer_delete ( ctx -> encoding_buf , 0 , pos ) ;
 else if ( pos != input -> size ) {
 buffer_append ( ctx -> encoding_buf , input -> data + pos , input -> size - pos ) ;
 }
 if ( ctx -> binary_input ) {
 output -> data = data ;
 output -> size = size ;
 }
 else {
 buffer_set_used_size ( ctx -> buf2 , 0 ) ;
 if ( ctx -> translation_size != 0 ) translation_buf_decode ( ctx , & data , & size ) ;
 pos = size ;
 ( void ) charset_to_utf8 ( ctx -> charset_trans , data , & pos , ctx -> buf2 ) ;
 if ( pos != size ) {
 ctx -> translation_size = size - pos ;
 i_assert ( ctx -> translation_size <= sizeof ( ctx -> translation_buf ) ) ;
 memcpy ( ctx -> translation_buf , data + pos , ctx -> translation_size ) ;
 }
 output -> data = ctx -> buf2 -> data ;
 output -> size = ctx -> buf2 -> used ;
 }
 output -> hdr = NULL ;
 return TRUE ;
 }