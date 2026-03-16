static int message_search_msg_real ( struct message_search_context * ctx , struct istream * input , struct message_part * parts , const char * * error_r ) {
 const enum message_header_parser_flags hdr_parser_flags = MESSAGE_HEADER_PARSER_FLAG_CLEAN_ONELINE ;
 struct message_parser_ctx * parser_ctx ;
 struct message_block raw_block ;
 struct message_part * new_parts ;
 int ret ;
 message_search_reset ( ctx ) ;
 if ( parts != NULL ) {
 parser_ctx = message_parser_init_from_parts ( parts , input , hdr_parser_flags , 0 ) ;
 }
 else {
 parser_ctx = message_parser_init ( pool_datastack_create ( ) , input , hdr_parser_flags , 0 ) ;
 }
 while ( ( ret = message_parser_parse_next_block ( parser_ctx , & raw_block ) ) > 0 ) {
 if ( message_search_more ( ctx , & raw_block ) ) {
 ret = 1 ;
 break ;
 }
 }
 i_assert ( ret != 0 ) ;
 if ( ret < 0 && input -> stream_errno == 0 ) {
 ret = 0 ;
 }
 if ( message_parser_deinit_from_parts ( & parser_ctx , & new_parts , error_r ) < 0 ) {
 ret = - 1 ;
 }
 return ret ;
 }