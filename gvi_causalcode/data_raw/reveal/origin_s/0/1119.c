static inline size_t size_code_gen_buffer ( size_t tb_size ) {
 if ( tb_size == 0 ) {



 if ( tb_size < MIN_CODE_GEN_BUFFER_SIZE ) {
 tb_size = MIN_CODE_GEN_BUFFER_SIZE ;
 }
 if ( tb_size > MAX_CODE_GEN_BUFFER_SIZE ) {
 tb_size = MAX_CODE_GEN_BUFFER_SIZE ;
 }
 tcg_ctx . code_gen_buffer_size = tb_size ;
 return tb_size ;
 }