static int selinux_inode_getsecurity ( struct inode * inode , const char * name , void * * buffer , bool alloc ) {
 u32 size ;
 int error ;
 char * context = NULL ;
 struct inode_security_struct * isec ;
 if ( strcmp ( name , XATTR_SELINUX_SUFFIX ) ) return - EOPNOTSUPP ;
 error = cap_capable ( current_cred ( ) , & init_user_ns , CAP_MAC_ADMIN , SECURITY_CAP_NOAUDIT ) ;
 if ( ! error ) error = cred_has_capability ( current_cred ( ) , CAP_MAC_ADMIN , SECURITY_CAP_NOAUDIT , true ) ;
 isec = inode_security ( inode ) ;
 if ( ! error ) error = security_sid_to_context_force ( isec -> sid , & context , & size ) ;
 else error = security_sid_to_context ( isec -> sid , & context , & size ) ;
 if ( error ) return error ;
 error = size ;
 if ( alloc ) {
 * buffer = context ;
 goto out_nofree ;
 }
 kfree ( context ) ;
 out_nofree : return error ;
 }