static int fpreg_pre_save ( void * opaque ) {
 x86_FPReg_tmp * tmp = opaque ;
 cpu_get_fp80 ( & tmp -> tmp_mant , & tmp -> tmp_exp , tmp -> parent -> d ) ;
 return 0 ;
 }