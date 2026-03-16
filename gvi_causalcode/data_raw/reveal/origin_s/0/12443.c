static inline void rfc822_parser_deinit ( struct rfc822_parser_context * ctx ) {
 i_assert ( ctx -> data <= ctx -> end ) ;
 ctx -> data = ctx -> end = NULL ;
 }