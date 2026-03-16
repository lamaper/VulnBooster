static int zcurrentfile ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 ref * fp ;
 push ( 1 ) ;
 if ( esfile != 0 ) {

 if ( esfile != efp ) {
 lprintf2 ( "currentfile: esfile=0x%lx, efp=0x%lx\n" , ( ulong ) esfile , ( ulong ) efp ) ;
 ref_assign ( op , efp ) ;
 }
 else # endif ref_assign ( op , esfile ) ;
 }
 else if ( ( fp = zget_current_file ( i_ctx_p ) ) == 0 ) {
 make_invalid_file ( i_ctx_p , op ) ;
 }
 else {
 ref_assign ( op , fp ) ;
 esfile_set_cache ( fp ) ;
 }
 r_clear_attrs ( op , a_executable ) ;
 return 0 ;
 }