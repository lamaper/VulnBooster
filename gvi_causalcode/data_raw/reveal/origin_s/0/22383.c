static bool pv_eoi_msr_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 return cpu -> env . pv_eoi_en_msr != 0 ;
 }