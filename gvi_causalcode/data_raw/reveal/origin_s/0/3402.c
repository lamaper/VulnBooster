static bool mpx_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 unsigned int i ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 if ( env -> bnd_regs [ i ] . lb || env -> bnd_regs [ i ] . ub ) {
 return true ;
 }
 }
 if ( env -> bndcs_regs . cfgu || env -> bndcs_regs . sts ) {
 return true ;
 }
 return ! ! env -> msr_bndcfgs ;
 }