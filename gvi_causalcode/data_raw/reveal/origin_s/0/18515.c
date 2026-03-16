int restore_check_save ( i_ctx_t * i_ctx_p , alloc_save_t * * asave ) {
 os_ptr op = osp ;
 int code = restore_check_operand ( op , asave , idmemory ) ;
 if ( code < 0 ) return code ;
 if_debug2m ( 'u' , imemory , "[u]vmrestore 0x%lx, id = %lu\n" , ( ulong ) alloc_save_client_data ( * asave ) , ( ulong ) op -> value . saveid ) ;
 if ( I_VALIDATE_BEFORE_RESTORE ) ivalidate_clean_spaces ( i_ctx_p ) ;
 osp -- ;
 {
 int code ;
 if ( ( code = restore_check_stack ( i_ctx_p , & o_stack , * asave , false ) ) < 0 || ( code = restore_check_stack ( i_ctx_p , & e_stack , * asave , true ) ) < 0 || ( code = restore_check_stack ( i_ctx_p , & d_stack , * asave , false ) ) < 0 ) {
 osp ++ ;
 return code ;
 }
 }
 osp ++ ;
 return 0 ;
 }