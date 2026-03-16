bool cpu_is_stopped ( CPUState * cpu ) {
 return ! runstate_is_running ( ) || cpu -> stopped ;
 }