static TranslationBlock * tb_find_pc ( uintptr_t tc_ptr ) {
 int m_min , m_max , m ;
 uintptr_t v ;
 TranslationBlock * tb ;
 if ( tcg_ctx . tb_ctx . nb_tbs <= 0 ) {
 return NULL ;
 }
 if ( tc_ptr < ( uintptr_t ) tcg_ctx . code_gen_buffer || tc_ptr >= ( uintptr_t ) tcg_ctx . code_gen_ptr ) {
 return NULL ;
 }
 m_min = 0 ;
 m_max = tcg_ctx . tb_ctx . nb_tbs - 1 ;
 while ( m_min <= m_max ) {
 m = ( m_min + m_max ) >> 1 ;
 tb = & tcg_ctx . tb_ctx . tbs [ m ] ;
 v = ( uintptr_t ) tb -> tc_ptr ;
 if ( v == tc_ptr ) {
 return tb ;
 }
 else if ( tc_ptr < v ) {
 m_max = m - 1 ;
 }
 else {
 m_min = m + 1 ;
 }
 }
 return & tcg_ctx . tb_ctx . tbs [ m_max ] ;
 }