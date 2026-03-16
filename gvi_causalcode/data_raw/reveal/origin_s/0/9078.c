static void astream_add_body ( struct attachment_istream * astream , const struct message_block * block ) {
 struct attachment_istream_part * part = & astream -> part ;
 buffer_t * part_buf ;
 size_t new_size ;
 switch ( part -> state ) {
 case MAIL_ATTACHMENT_STATE_NO : stream_add_data ( astream , block -> data , block -> size ) ;
 break ;
 case MAIL_ATTACHMENT_STATE_MAYBE : if ( part -> part_buf == NULL ) {
 part -> part_buf = buffer_create_dynamic ( default_pool , astream -> set . min_size ) ;
 }
 part_buf = part -> part_buf ;
 new_size = part_buf -> used + block -> size ;
 if ( new_size < astream -> set . min_size ) {
 buffer_append ( part_buf , block -> data , block -> size ) ;
 break ;
 }
 if ( astream_open_output ( astream ) < 0 ) {
 part -> state = MAIL_ATTACHMENT_STATE_NO ;
 stream_add_data ( astream , part_buf -> data , part_buf -> used ) ;
 stream_add_data ( astream , block -> data , block -> size ) ;
 break ;
 }
 part -> state = MAIL_ATTACHMENT_STATE_YES ;
 astream_try_base64_decode ( part , part_buf -> data , part_buf -> used ) ;
 hash_format_loop ( astream -> set . hash_format , part_buf -> data , part_buf -> used ) ;
 o_stream_nsend ( part -> temp_output , part_buf -> data , part_buf -> used ) ;
 buffer_set_used_size ( part_buf , 0 ) ;
 case MAIL_ATTACHMENT_STATE_YES : astream_try_base64_decode ( part , block -> data , block -> size ) ;
 hash_format_loop ( astream -> set . hash_format , block -> data , block -> size ) ;
 o_stream_nsend ( part -> temp_output , block -> data , block -> size ) ;
 break ;
 }
 }