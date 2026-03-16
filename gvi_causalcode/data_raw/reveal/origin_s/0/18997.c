void selinux_complete_init ( void ) {
 printk ( KERN_DEBUG "SELinux: Completing initialization.\n" ) ;
 printk ( KERN_DEBUG "SELinux: Setting up existing superblocks.\n" ) ;
 iterate_supers ( delayed_superblock_init , NULL ) ;
 }