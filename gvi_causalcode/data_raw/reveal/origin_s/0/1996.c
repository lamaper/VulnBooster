static void inode_free_security ( struct inode * inode ) {
 struct inode_security_struct * isec = inode -> i_security ;
 struct superblock_security_struct * sbsec = inode -> i_sb -> s_security ;
 if ( ! list_empty_careful ( & isec -> list ) ) {
 spin_lock ( & sbsec -> isec_lock ) ;
 list_del_init ( & isec -> list ) ;
 spin_unlock ( & sbsec -> isec_lock ) ;
 }
 call_rcu ( & isec -> rcu , inode_free_rcu ) ;
 }