static void i_enable_free ( gs_memory_t * mem , bool enable ) {
 if ( enable ) mem -> procs . free_object = i_free_object , mem -> procs . free_string = i_free_string ;
 else mem -> procs . free_object = gs_ignore_free_object , mem -> procs . free_string = gs_ignore_free_string ;
 }