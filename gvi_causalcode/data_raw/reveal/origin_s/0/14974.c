static int inode_doinit_with_dentry ( struct inode * inode , struct dentry * opt_dentry ) {
 struct superblock_security_struct * sbsec = NULL ;
 struct inode_security_struct * isec = inode -> i_security ;
 u32 task_sid , sid = 0 ;
 u16 sclass ;
 struct dentry * dentry ;

 unsigned len = 0 ;
 int rc = 0 ;
 if ( isec -> initialized == LABEL_INITIALIZED ) return 0 ;
 spin_lock ( & isec -> lock ) ;
 if ( isec -> initialized == LABEL_INITIALIZED ) goto out_unlock ;
 if ( isec -> sclass == SECCLASS_FILE ) isec -> sclass = inode_mode_to_security_class ( inode -> i_mode ) ;
 sbsec = inode -> i_sb -> s_security ;
 if ( ! ( sbsec -> flags & SE_SBINITIALIZED ) ) {
 spin_lock ( & sbsec -> isec_lock ) ;
 if ( list_empty ( & isec -> list ) ) list_add ( & isec -> list , & sbsec -> isec_head ) ;
 spin_unlock ( & sbsec -> isec_lock ) ;
 goto out_unlock ;
 }
 sclass = isec -> sclass ;
 task_sid = isec -> task_sid ;
 sid = isec -> sid ;
 isec -> initialized = LABEL_PENDING ;
 spin_unlock ( & isec -> lock ) ;
 switch ( sbsec -> behavior ) {
 case SECURITY_FS_USE_NATIVE : break ;
 case SECURITY_FS_USE_XATTR : if ( ! ( inode -> i_opflags & IOP_XATTR ) ) {
 sid = sbsec -> def_sid ;
 break ;
 }
 if ( opt_dentry ) {
 dentry = dget ( opt_dentry ) ;
 }
 else {
 dentry = d_find_alias ( inode ) ;
 }
 if ( ! dentry ) {
 goto out ;
 }
 len = INITCONTEXTLEN ;
 context = kmalloc ( len + 1 , GFP_NOFS ) ;
 if ( ! context ) {
 rc = - ENOMEM ;
 dput ( dentry ) ;
 goto out ;
 }
 context [ len ] = '\0' ;
 rc = __vfs_getxattr ( dentry , inode , XATTR_NAME_SELINUX , context , len ) ;
 if ( rc == - ERANGE ) {
 kfree ( context ) ;
 rc = __vfs_getxattr ( dentry , inode , XATTR_NAME_SELINUX , NULL , 0 ) ;
 if ( rc < 0 ) {
 dput ( dentry ) ;
 goto out ;
 }
 len = rc ;
 context = kmalloc ( len + 1 , GFP_NOFS ) ;
 if ( ! context ) {
 rc = - ENOMEM ;
 dput ( dentry ) ;
 goto out ;
 }
 context [ len ] = '\0' ;
 rc = __vfs_getxattr ( dentry , inode , XATTR_NAME_SELINUX , context , len ) ;
 }
 dput ( dentry ) ;
 if ( rc < 0 ) {
 if ( rc != - ENODATA ) {
 printk ( KERN_WARNING "SELinux: %s: getxattr returned " "%d for dev=%s ino=%ld\n" , __func__ , - rc , inode -> i_sb -> s_id , inode -> i_ino ) ;
 kfree ( context ) ;
 goto out ;
 }
 sid = sbsec -> def_sid ;
 rc = 0 ;
 }
 else {
 rc = security_context_to_sid_default ( context , rc , & sid , sbsec -> def_sid , GFP_NOFS ) ;
 if ( rc ) {
 char * dev = inode -> i_sb -> s_id ;
 unsigned long ino = inode -> i_ino ;
 if ( rc == - EINVAL ) {
 if ( printk_ratelimit ( ) ) printk ( KERN_NOTICE "SELinux: inode=%lu on dev=%s was found to have an invalid " "context=%s. This indicates you may need to relabel the inode or the " "filesystem in question.\n" , ino , dev , context ) ;
 }
 else {
 printk ( KERN_WARNING "SELinux: %s: context_to_sid(%s) " "returned %d for dev=%s ino=%ld\n" , __func__ , context , - rc , dev , ino ) ;
 }
 kfree ( context ) ;
 rc = 0 ;
 break ;
 }
 }
 kfree ( context ) ;
 break ;
 case SECURITY_FS_USE_TASK : sid = task_sid ;
 break ;
 case SECURITY_FS_USE_TRANS : sid = sbsec -> sid ;
 rc = security_transition_sid ( task_sid , sid , sclass , NULL , & sid ) ;
 if ( rc ) goto out ;
 break ;
 case SECURITY_FS_USE_MNTPOINT : sid = sbsec -> mntpoint_sid ;
 break ;
 default : sid = sbsec -> sid ;
 if ( ( sbsec -> flags & SE_SBGENFS ) && ! S_ISLNK ( inode -> i_mode ) ) {
 if ( opt_dentry ) dentry = dget ( opt_dentry ) ;
 else dentry = d_find_alias ( inode ) ;
 if ( ! dentry ) goto out ;
 rc = selinux_genfs_get_sid ( dentry , sclass , sbsec -> flags , & sid ) ;
 dput ( dentry ) ;
 if ( rc ) goto out ;
 }
 break ;
 }
 out : spin_lock ( & isec -> lock ) ;
 if ( isec -> initialized == LABEL_PENDING ) {
 if ( ! sid || rc ) {
 isec -> initialized = LABEL_INVALID ;
 goto out_unlock ;
 }
 isec -> initialized = LABEL_INITIALIZED ;
 isec -> sid = sid ;
 }
 out_unlock : spin_unlock ( & isec -> lock ) ;
 return rc ;
 }