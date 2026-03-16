static int fts_build_full_words ( struct fts_mail_build_context * ctx , const unsigned char * data , size_t size , bool last ) {
 size_t i ;
 if ( ctx -> word_buf != NULL && ctx -> word_buf -> used > 0 ) {
 for ( i = 0 ;
 i < size ;
 i ++ ) {
 if ( IS_WORD_WHITESPACE ( data [ i ] ) ) break ;
 }
 buffer_append ( ctx -> word_buf , data , i ) ;
 data += i ;
 size -= i ;
 if ( size == 0 && ctx -> word_buf -> used < MAX_WORD_SIZE && ! last ) {
 return 0 ;
 }
 if ( fts_backend_update_build_more ( ctx -> update_ctx , ctx -> word_buf -> data , ctx -> word_buf -> used ) < 0 ) return - 1 ;
 buffer_set_used_size ( ctx -> word_buf , 0 ) ;
 }
 if ( last ) i = size ;
 else {
 for ( i = size ;
 i > 0 ;
 i -- ) {
 if ( IS_WORD_WHITESPACE ( data [ i - 1 ] ) ) break ;
 }
 }
 if ( fts_backend_update_build_more ( ctx -> update_ctx , data , i ) < 0 ) return - 1 ;
 if ( i < size ) {
 if ( ctx -> word_buf == NULL ) {
 ctx -> word_buf = buffer_create_dynamic ( default_pool , 128 ) ;
 }
 buffer_append ( ctx -> word_buf , data + i , size - i ) ;
 }
 return 0 ;
 }