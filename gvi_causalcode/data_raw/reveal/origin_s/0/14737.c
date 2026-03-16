static int fts_build_mail_real ( struct fts_backend_update_context * update_ctx , struct mail * mail ) {
 struct fts_mail_build_context ctx ;
 struct istream * input ;
 struct message_parser_ctx * parser ;
 struct message_decoder_context * decoder ;
 struct message_block raw_block , block ;
 struct message_part * prev_part , * parts ;
 bool skip_body = FALSE , body_part = FALSE , body_added = FALSE ;
 bool binary_body ;
 const char * error ;
 int ret ;
 if ( mail_get_stream_because ( mail , NULL , NULL , "fts indexing" , & input ) < 0 ) {
 if ( mail -> expunged ) return 0 ;
 i_error ( "Failed to read mailbox %s mail UID=%u stream: %s" , mailbox_get_vname ( mail -> box ) , mail -> uid , mailbox_get_last_internal_error ( mail -> box , NULL ) ) ;
 return - 1 ;
 }
 i_zero ( & ctx ) ;
 ctx . update_ctx = update_ctx ;
 ctx . mail = mail ;
 if ( ( update_ctx -> backend -> flags & FTS_BACKEND_FLAG_TOKENIZED_INPUT ) != 0 ) ctx . pending_input = buffer_create_dynamic ( default_pool , 128 ) ;
 prev_part = NULL ;
 parser = message_parser_init ( pool_datastack_create ( ) , input , MESSAGE_HEADER_PARSER_FLAG_CLEAN_ONELINE , 0 ) ;
 decoder = message_decoder_init ( update_ctx -> normalizer , 0 ) ;
 for ( ;
 ;
 ) {
 ret = message_parser_parse_next_block ( parser , & raw_block ) ;
 i_assert ( ret != 0 ) ;
 if ( ret < 0 ) {
 if ( input -> stream_errno == 0 ) ret = 0 ;
 else {
 i_error ( "read(%s) failed: %s" , i_stream_get_name ( input ) , i_stream_get_error ( input ) ) ;
 }
 break ;
 }
 if ( raw_block . part != prev_part ) {
 if ( ctx . body_parser != NULL ) {
 if ( fts_body_parser_finish ( & ctx ) < 0 ) {
 ret = - 1 ;
 break ;
 }
 }
 message_decoder_set_return_binary ( decoder , FALSE ) ;
 fts_backend_update_unset_build_key ( update_ctx ) ;
 prev_part = raw_block . part ;
 i_free_and_null ( ctx . content_type ) ;
 i_free_and_null ( ctx . content_disposition ) ;
 if ( raw_block . size != 0 ) {
 skip_body = TRUE ;
 }
 }
 if ( raw_block . hdr != NULL ) {
 }
 else if ( raw_block . size == 0 ) {
 skip_body = ! fts_build_body_begin ( & ctx , raw_block . part , & binary_body ) ;
 if ( binary_body ) message_decoder_set_return_binary ( decoder , TRUE ) ;
 body_part = TRUE ;
 }
 else {
 if ( skip_body ) continue ;
 }
 if ( ! message_decoder_decode_next_block ( decoder , & raw_block , & block ) ) continue ;
 if ( block . hdr != NULL ) {
 fts_parse_mail_header ( & ctx , & raw_block ) ;
 if ( fts_build_mail_header ( & ctx , & block ) < 0 ) {
 ret = - 1 ;
 break ;
 }
 }
 else if ( block . size == 0 ) {
 }
 else {
 i_assert ( body_part ) ;
 if ( ctx . body_parser != NULL ) fts_parser_more ( ctx . body_parser , & block ) ;
 if ( fts_build_body_block ( & ctx , & block , FALSE ) < 0 ) {
 ret = - 1 ;
 break ;
 }
 body_added = TRUE ;
 }
 }
 if ( ctx . body_parser != NULL ) {
 if ( ret == 0 ) ret = fts_body_parser_finish ( & ctx ) ;
 else ( void ) fts_parser_deinit ( & ctx . body_parser ) ;
 }
 if ( ret == 0 && body_part && ! skip_body && ! body_added ) {
 block . data = NULL ;
 block . size = 0 ;
 ret = fts_build_body_block ( & ctx , & block , TRUE ) ;
 }
 if ( message_parser_deinit_from_parts ( & parser , & parts , & error ) < 0 ) index_mail_set_message_parts_corrupted ( mail , error ) ;
 message_decoder_deinit ( & decoder ) ;
 i_free ( ctx . content_type ) ;
 i_free ( ctx . content_disposition ) ;
 if ( ctx . word_buf != NULL ) buffer_free ( & ctx . word_buf ) ;
 if ( ctx . pending_input != NULL ) buffer_free ( & ctx . pending_input ) ;
 return ret < 0 ? - 1 : 1 ;
 }