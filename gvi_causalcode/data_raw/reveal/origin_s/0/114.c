int dorestore ( i_ctx_t * i_ctx_p , alloc_save_t * asave ) {
 os_ptr op = osp ;
 bool last ;
 vm_save_t * vmsave ;
 int code ;
 osp -- ;
 restore_fix_stack ( i_ctx_p , & o_stack , asave , false ) ;
 restore_fix_stack ( i_ctx_p , & e_stack , asave , true ) ;
 restore_fix_stack ( i_ctx_p , & d_stack , asave , false ) ;
 do {
 vmsave = alloc_save_client_data ( alloc_save_current ( idmemory ) ) ;
 gs_grestoreall_for_restore ( igs , vmsave -> gsave ) ;
 vmsave -> gsave = 0 ;
 code = alloc_restore_step_in ( idmemory , asave ) ;
 if ( code < 0 ) return code ;
 last = code ;
 }
 while ( ! last ) ;
 {
 uint space = icurrent_space ;
 ialloc_set_space ( idmemory , avm_local ) ;
 ifree_object ( vmsave , "zrestore" ) ;
 ialloc_set_space ( idmemory , space ) ;
 }
 dict_set_top ( ) ;
 if ( I_VALIDATE_AFTER_RESTORE ) ivalidate_clean_spaces ( i_ctx_p ) ;
 i_ctx_p -> LockFilePermissions = false ;
 return 0 ;
 }