static bool avx512_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 unsigned int i ;
 for ( i = 0 ;
 i < NB_OPMASK_REGS ;
 i ++ ) {
 if ( env -> opmask_regs [ i ] ) {
 return true ;
 }
 }
 for ( i = 0 ;
 i < CPU_NB_REGS ;
 i ++ ) {

 return true ;
 }

 return true ;
 }

 return false ;
 }