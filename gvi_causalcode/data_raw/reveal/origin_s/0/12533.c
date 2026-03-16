static inline tcg_target_ulong cpu_tb_exec ( CPUState * cpu , uint8_t * tb_ptr ) {
 CPUArchState * env = cpu -> env_ptr ;
 tcg_target_ulong next_tb = tcg_qemu_tb_exec ( env , tb_ptr ) ;
 if ( ( next_tb & TB_EXIT_MASK ) > TB_EXIT_IDX1 ) {
 TranslationBlock * tb = ( TranslationBlock * ) ( next_tb & ~ TB_EXIT_MASK ) ;
 cpu_pc_from_tb ( env , tb ) ;
 }
 if ( ( next_tb & TB_EXIT_MASK ) == TB_EXIT_REQUESTED ) {
 cpu -> tcg_exit_req = 0 ;
 }
 return next_tb ;
 }