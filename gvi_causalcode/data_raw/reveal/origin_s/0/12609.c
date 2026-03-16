bool cpu_restore_state ( CPUArchState * env , uintptr_t retaddr ) {
 TranslationBlock * tb ;
 tb = tb_find_pc ( retaddr ) ;
 if ( tb ) {
 cpu_restore_state_from_tb ( tb , env , retaddr ) ;
 return true ;
 }
 return false ;
 }