static int runandhide_restore_hidden ( i_ctx_t * i_ctx_p , ref * obj , ref * attrs ) {
 os_ptr op = osp ;
 push ( 1 ) ;
 ref_assign ( op , obj ) ;
 r_clear_attrs ( op , a_all ) ;
 r_set_attrs ( op , attrs -> value . intval ) ;
 return 0 ;
 }