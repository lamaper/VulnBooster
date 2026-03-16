void cpu_io_recompile ( CPUArchState * env , uintptr_t retaddr ) {
 TranslationBlock * tb ;
 uint32_t n , cflags ;
 target_ulong pc , cs_base ;
 uint64_t flags ;
 tb = tb_find_pc ( retaddr ) ;
 if ( ! tb ) {
 cpu_abort ( env , "cpu_io_recompile: could not find TB for pc=%p" , ( void * ) retaddr ) ;
 }
 n = env -> icount_decr . u16 . low + tb -> icount ;
 cpu_restore_state_from_tb ( tb , env , retaddr ) ;
 n = n - env -> icount_decr . u16 . low ;
 n ++ ;

 env -> active_tc . PC -= 4 ;
 env -> icount_decr . u16 . low ++ ;
 env -> hflags &= ~ MIPS_HFLAG_BMASK ;
 }

 env -> pc -= 2 ;
 env -> icount_decr . u16 . low ++ ;
 env -> flags &= ~ ( DELAY_SLOT | DELAY_SLOT_CONDITIONAL ) ;
 }

 cpu_abort ( env , "TB too big during recompile" ) ;
 }
 cflags = n | CF_LAST_IO ;
 pc = tb -> pc ;
 cs_base = tb -> cs_base ;
 flags = tb -> flags ;
 tb_phys_invalidate ( tb , - 1 ) ;
 tb_gen_code ( env , pc , cs_base , flags , cflags ) ;
 cpu_resume_from_signal ( env , NULL ) ;
 }