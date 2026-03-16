static int maybe_create_keyring_or_box ( char * filename , int is_box , int force_create ) {
 dotlock_t lockhd = NULL ;
 IOBUF iobuf ;
 int rc ;
 mode_t oldmask ;
 char * last_slash_in_filename ;
 int save_slash ;
 if ( ! access ( filename , F_OK ) ) return 0 ;
 if ( ! force_create ) return gpg_error ( GPG_ERR_ENOENT ) ;
 last_slash_in_filename = strrchr ( filename , DIRSEP_C ) ;

 char * p = strrchr ( filename , '/' ) ;
 if ( ! last_slash_in_filename || p > last_slash_in_filename ) last_slash_in_filename = p ;
 }

 save_slash = * last_slash_in_filename ;
 * last_slash_in_filename = 0 ;
 if ( access ( filename , F_OK ) ) {
 static int tried ;
 if ( ! tried ) {
 tried = 1 ;
 try_make_homedir ( filename ) ;
 }
 if ( access ( filename , F_OK ) ) {
 rc = gpg_error_from_syserror ( ) ;
 * last_slash_in_filename = save_slash ;
 goto leave ;
 }
 }
 * last_slash_in_filename = save_slash ;
 lockhd = dotlock_create ( filename , 0 ) ;
 if ( ! lockhd ) {
 rc = gpg_error_from_syserror ( ) ;
 if ( opt . verbose ) log_info ( "can't allocate lock for '%s': %s\n" , filename , gpg_strerror ( rc ) ) ;
 if ( ! force_create ) return gpg_error ( GPG_ERR_ENOENT ) ;
 else return rc ;
 }
 if ( dotlock_take ( lockhd , - 1 ) ) {
 rc = gpg_error_from_syserror ( ) ;
 log_info ( "can't lock '%s': %s\n" , filename , gpg_strerror ( rc ) ) ;
 goto leave ;
 }
 if ( ! access ( filename , F_OK ) ) {
 rc = 0 ;
 goto leave ;
 }
 oldmask = umask ( 077 ) ;
 if ( is_secured_filename ( filename ) ) {
 iobuf = NULL ;
 gpg_err_set_errno ( EPERM ) ;
 }
 else iobuf = iobuf_create ( filename , 0 ) ;
 umask ( oldmask ) ;
 if ( ! iobuf ) {
 rc = gpg_error_from_syserror ( ) ;
 if ( is_box ) log_error ( _ ( "error creating keybox '%s': %s\n" ) , filename , gpg_strerror ( rc ) ) ;
 else log_error ( _ ( "error creating keyring '%s': %s\n" ) , filename , gpg_strerror ( rc ) ) ;
 goto leave ;
 }
 iobuf_close ( iobuf ) ;
 iobuf_ioctl ( NULL , IOBUF_IOCTL_INVALIDATE_CACHE , 0 , filename ) ;
 if ( is_box ) {
 FILE * fp = fopen ( filename , "w" ) ;
 if ( ! fp ) rc = gpg_error_from_syserror ( ) ;
 else {
 rc = _keybox_write_header_blob ( fp , 1 ) ;
 fclose ( fp ) ;
 }
 if ( rc ) {
 if ( is_box ) log_error ( _ ( "error creating keybox '%s': %s\n" ) , filename , gpg_strerror ( rc ) ) ;
 else log_error ( _ ( "error creating keyring '%s': %s\n" ) , filename , gpg_strerror ( rc ) ) ;
 goto leave ;
 }
 }
 if ( ! opt . quiet ) {
 if ( is_box ) log_info ( _ ( "keybox '%s' created\n" ) , filename ) ;
 else log_info ( _ ( "keyring '%s' created\n" ) , filename ) ;
 }
 rc = 0 ;
 leave : if ( lockhd ) {
 dotlock_release ( lockhd ) ;
 dotlock_destroy ( lockhd ) ;
 }
 return rc ;
 }