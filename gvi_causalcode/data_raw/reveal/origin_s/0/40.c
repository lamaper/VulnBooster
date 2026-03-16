static int zforgetsave ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 alloc_save_t * asave ;
 vm_save_t * vmsave ;
 int code = restore_check_operand ( op , & asave , idmemory ) ;
 if ( code < 0 ) return 0 ;
 vmsave = alloc_save_client_data ( asave ) ;
 restore_fix_stack ( i_ctx_p , & o_stack , asave , false ) ;
 restore_fix_stack ( i_ctx_p , & e_stack , asave , false ) ;
 restore_fix_stack ( i_ctx_p , & d_stack , asave , false ) ;
 {
 gs_gstate * pgs = igs ;
 gs_gstate * last ;
 while ( gs_gstate_saved ( last = gs_gstate_saved ( pgs ) ) != 0 ) pgs = last ;
 gs_gstate_swap_saved ( last , vmsave -> gsave ) ;
 gs_grestore ( last ) ;
 gs_grestore ( last ) ;
 }
 code = alloc_forget_save_in ( idmemory , asave ) ;
 if ( code < 0 ) return code ;
 {
 uint space = icurrent_space ;
 ialloc_set_space ( idmemory , avm_local ) ;
 vmsave -> gsave = 0 ;
 ifree_object ( vmsave , "zrestore" ) ;
 ialloc_set_space ( idmemory , space ) ;
 }
 pop ( 1 ) ;
 return 0 ;
 }