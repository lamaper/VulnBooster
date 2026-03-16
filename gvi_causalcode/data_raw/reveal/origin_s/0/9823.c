void vm_stop_force_state ( RunState state ) {
 if ( runstate_is_running ( ) ) {
 vm_stop ( state ) ;
 }
 else {
 runstate_set ( state ) ;
 }
 }