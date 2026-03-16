static inline void flush_unauthorized_files ( const struct cred * cred , struct files_struct * files ) {
 struct file * file , * devnull = NULL ;
 struct tty_struct * tty ;
 int drop_tty = 0 ;
 unsigned n ;
 tty = get_current_tty ( ) ;
 if ( tty ) {
 spin_lock ( & tty -> files_lock ) ;
 if ( ! list_empty ( & tty -> tty_files ) ) {
 struct tty_file_private * file_priv ;
 file_priv = list_first_entry ( & tty -> tty_files , struct tty_file_private , list ) ;
 file = file_priv -> file ;
 if ( file_path_has_perm ( cred , file , FILE__READ | FILE__WRITE ) ) drop_tty = 1 ;
 }
 spin_unlock ( & tty -> files_lock ) ;
 tty_kref_put ( tty ) ;
 }
 if ( drop_tty ) no_tty ( ) ;
 n = iterate_fd ( files , 0 , match_file , cred ) ;
 if ( ! n ) return ;
 devnull = dentry_open ( & selinux_null , O_RDWR , cred ) ;
 if ( IS_ERR ( devnull ) ) devnull = NULL ;
 do {
 replace_fd ( n - 1 , devnull , 0 ) ;
 }
 while ( ( n = iterate_fd ( files , n , match_file , cred ) ) != 0 ) ;
 if ( devnull ) fput ( devnull ) ;
 }