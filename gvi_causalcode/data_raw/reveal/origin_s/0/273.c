static void cpu_handle_debug_exception ( CPUArchState * env ) {
 CPUWatchpoint * wp ;
 if ( ! env -> watchpoint_hit ) {
 QTAILQ_FOREACH ( wp , & env -> watchpoints , entry ) {
 wp -> flags &= ~ BP_WATCHPOINT_HIT ;
 }
 }
 if ( debug_excp_handler ) {
 debug_excp_handler ( env ) ;
 }
 }