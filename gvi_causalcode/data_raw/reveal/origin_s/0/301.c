static int selinux_sb_show_options ( struct seq_file * m , struct super_block * sb ) {
 struct security_mnt_opts opts ;
 int rc ;
 rc = selinux_get_mnt_opts ( sb , & opts ) ;
 if ( rc ) {
 if ( rc == - EINVAL ) rc = 0 ;
 return rc ;
 }
 selinux_write_opts ( m , & opts ) ;
 security_free_mnt_opts ( & opts ) ;
 return rc ;
 }