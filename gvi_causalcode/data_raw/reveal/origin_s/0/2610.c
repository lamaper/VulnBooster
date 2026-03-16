static inline void tb_reset_jump ( TranslationBlock * tb , int n ) {
 tb_set_jmp_target ( tb , n , ( uintptr_t ) ( tb -> tc_ptr + tb -> tb_next_offset [ n ] ) ) ;
 }