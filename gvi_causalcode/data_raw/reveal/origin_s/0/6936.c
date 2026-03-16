static int push_execstack ( i_ctx_t * i_ctx_p , os_ptr op1 , bool include_marks , op_proc_t cont ) {
 uint size ;
 uint depth ;
 if ( ! r_is_array ( op1 ) ) return_op_typecheck ( op1 ) ;
 size = r_size ( op1 ) ;
 depth = count_exec_stack ( i_ctx_p , include_marks ) ;
 if ( depth > size ) return_error ( gs_error_rangecheck ) ;
 check_write ( * op1 ) ;
 {
 int code = ref_stack_store_check ( & e_stack , op1 , size , 0 ) ;
 if ( code < 0 ) return code ;
 }
 check_estack ( 1 ) ;
 r_set_size ( op1 , depth ) ;
 push_op_estack ( cont ) ;
 return o_push_estack ;
 }