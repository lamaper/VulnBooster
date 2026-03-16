static bool async_pf_msr_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 return cpu -> env . async_pf_en_msr != 0 ;
 }