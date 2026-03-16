static int __inode_security_revalidate ( struct inode * inode , struct dentry * opt_dentry , bool may_sleep ) {
 struct inode_security_struct * isec = inode -> i_security ;
 might_sleep_if ( may_sleep ) ;
 if ( ss_initialized && isec -> initialized != LABEL_INITIALIZED ) {
 if ( ! may_sleep ) return - ECHILD ;
 inode_doinit_with_dentry ( inode , opt_dentry ) ;
 }
 return 0 ;
 }