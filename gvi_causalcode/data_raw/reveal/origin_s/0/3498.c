static int fts_body_parser_finish ( struct fts_mail_build_context * ctx ) {
 struct message_block block ;
 int ret = 0 ;
 do {
 i_zero ( & block ) ;
 fts_parser_more ( ctx -> body_parser , & block ) ;
 if ( fts_build_body_block ( ctx , & block , FALSE ) < 0 ) {
 ret = - 1 ;
 break ;
 }
 }
 while ( block . size > 0 ) ;
 if ( fts_parser_deinit ( & ctx -> body_parser ) < 0 ) ret = - 1 ;
 return ret ;
 }