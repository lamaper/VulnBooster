static int fts_build_mail_header ( struct fts_mail_build_context * ctx , const struct message_block * block ) {
 const struct message_header_line * hdr = block -> hdr ;
 struct fts_backend_build_key key ;
 int ret ;
 if ( hdr -> eoh ) return 0 ;
 i_zero ( & key ) ;
 key . uid = ctx -> mail -> uid ;
 key . type = block -> part -> physical_pos == 0 ? FTS_BACKEND_BUILD_KEY_HDR : FTS_BACKEND_BUILD_KEY_MIME_HDR ;
 key . part = block -> part ;
 key . hdr_name = hdr -> name ;
 if ( ( ctx -> update_ctx -> backend -> flags & FTS_BACKEND_FLAG_TOKENIZED_INPUT ) != 0 ) fts_build_tokenized_hdr_update_lang ( ctx , hdr ) ;
 if ( ! fts_backend_update_set_build_key ( ctx -> update_ctx , & key ) ) return 0 ;
 if ( ! message_header_is_address ( hdr -> name ) ) {
 ret = fts_build_unstructured_header ( ctx , hdr ) ;
 }
 else T_BEGIN {
 struct message_address * addr ;
 string_t * str ;
 addr = message_address_parse ( pool_datastack_create ( ) , hdr -> full_value , hdr -> full_value_len , UINT_MAX , FALSE ) ;
 str = t_str_new ( hdr -> full_value_len ) ;
 message_address_write ( str , addr ) ;
 ret = fts_build_data ( ctx , str_data ( str ) , str_len ( str ) , TRUE ) ;
 }
 T_END ;
 if ( ( ctx -> update_ctx -> backend -> flags & FTS_BACKEND_FLAG_TOKENIZED_INPUT ) != 0 ) {
 struct fts_user_language * prev_lang = ctx -> cur_user_lang ;
 fts_mail_build_ctx_set_lang ( ctx , fts_user_get_data_lang ( ctx -> update_ctx -> backend -> ns -> user ) ) ;
 key . hdr_name = "" ;
 if ( fts_backend_update_set_build_key ( ctx -> update_ctx , & key ) ) {
 if ( fts_build_data ( ctx , ( const void * ) hdr -> name , strlen ( hdr -> name ) , TRUE ) < 0 ) ret = - 1 ;
 }
 fts_mail_build_ctx_set_lang ( ctx , prev_lang ) ;
 }
 return ret ;
 }