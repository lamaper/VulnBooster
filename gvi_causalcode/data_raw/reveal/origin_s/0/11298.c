static int selinux_file_open ( struct file * file , const struct cred * cred ) {
 struct file_security_struct * fsec ;
 struct inode_security_struct * isec ;
 fsec = file -> f_security ;
 isec = inode_security ( file_inode ( file ) ) ;
 fsec -> isid = isec -> sid ;
 fsec -> pseqno = avc_policy_seqno ( ) ;
 return file_path_has_perm ( cred , file , open_file_to_av ( file ) ) ;
 }