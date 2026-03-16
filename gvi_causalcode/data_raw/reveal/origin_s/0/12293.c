static int unmatched_exit ( os_ptr op , op_proc_t opproc ) {
 make_oper ( op - 1 , 0 , opproc ) ;
 make_int ( op , gs_error_invalidexit ) ;
 return_error ( gs_error_Quit ) ;
 }