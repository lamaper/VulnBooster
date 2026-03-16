static bool steal_time_msr_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 return cpu -> env . steal_time_msr != 0 ;
 }