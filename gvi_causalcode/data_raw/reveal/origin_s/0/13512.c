static int restore_check_operand ( os_ptr op , alloc_save_t * * pasave , gs_dual_memory_t * idmem ) {
 vm_save_t * vmsave ;
 ulong sid ;
 alloc_save_t * asave ;
 check_type ( * op , t_save ) ;
 vmsave = r_ptr ( op , vm_save_t ) ;
 if ( vmsave == 0 ) return_error ( gs_error_invalidrestore ) ;
 sid = op -> value . saveid ;
 asave = alloc_find_save ( idmem , sid ) ;
 if ( asave == 0 ) return_error ( gs_error_invalidrestore ) ;
 * pasave = asave ;
 return 0 ;
 }