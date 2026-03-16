static int selinux_inode_removexattr ( struct dentry * dentry , const char * name ) {
 if ( strcmp ( name , XATTR_NAME_SELINUX ) ) return selinux_inode_setotherxattr ( dentry , name ) ;
 return - EACCES ;
 }