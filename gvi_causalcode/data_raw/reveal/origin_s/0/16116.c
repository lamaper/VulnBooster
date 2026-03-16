static int fpreg_post_load ( void * opaque , int version ) {
 x86_FPReg_tmp * tmp = opaque ;
 tmp -> parent -> d = cpu_set_fp80 ( tmp -> tmp_mant , tmp -> tmp_exp ) ;
 return 0 ;
 }