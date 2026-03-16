static bool cpu_can_run ( CPUState * cpu ) {
 if ( cpu -> stop ) {
 return false ;
 }
 if ( cpu -> stopped || ! runstate_is_running ( ) ) {
 return false ;
 }
 return true ;
 }