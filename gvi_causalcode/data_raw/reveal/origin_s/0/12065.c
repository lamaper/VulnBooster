static void cpu_update_state ( void * opaque , int running , RunState state ) {
 CPUX86State * env = opaque ;
 if ( running ) {
 env -> tsc_valid = false ;
 }
 }