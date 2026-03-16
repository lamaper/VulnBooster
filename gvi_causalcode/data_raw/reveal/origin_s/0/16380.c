static int file_map_prot_check ( struct file * file , unsigned long prot , int shared ) {
 const struct cred * cred = current_cred ( ) ;
 int rc = 0 ;
 if ( default_noexec && ( prot & PROT_EXEC ) && ( ! file || IS_PRIVATE ( file_inode ( file ) ) || ( ! shared && ( prot & PROT_WRITE ) ) ) ) {
 rc = cred_has_perm ( cred , cred , PROCESS__EXECMEM ) ;
 if ( rc ) goto error ;
 }
 if ( file ) {
 u32 av = FILE__READ ;
 if ( shared && ( prot & PROT_WRITE ) ) av |= FILE__WRITE ;
 if ( prot & PROT_EXEC ) av |= FILE__EXECUTE ;
 return file_has_perm ( cred , file , av ) ;
 }
 error : return rc ;
 }