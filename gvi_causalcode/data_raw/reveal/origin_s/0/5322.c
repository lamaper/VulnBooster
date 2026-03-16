static int create_tmp_file ( const char * template , char * * r_bakfname , char * * r_tmpfname , IOBUF * r_fp ) {
 char * bakfname , * tmpfname ;
 mode_t oldmask ;
 * r_bakfname = NULL ;
 * r_tmpfname = NULL ;

 bakfname = xmalloc ( strlen ( template ) + 1 ) ;
 strcpy ( bakfname , template ) ;
 strcpy ( bakfname + strlen ( template ) - 4 , EXTSEP_S "bak" ) ;
 tmpfname = xmalloc ( strlen ( template ) + 1 ) ;
 strcpy ( tmpfname , template ) ;
 strcpy ( tmpfname + strlen ( template ) - 4 , EXTSEP_S "tmp" ) ;
 }
 else {
 bakfname = xmalloc ( strlen ( template ) + 5 ) ;
 strcpy ( stpcpy ( bakfname , template ) , EXTSEP_S "bak" ) ;
 tmpfname = xmalloc ( strlen ( template ) + 5 ) ;
 strcpy ( stpcpy ( tmpfname , template ) , EXTSEP_S "tmp" ) ;
 }

 strcpy ( stpcpy ( bakfname , template ) , "~" ) ;
 tmpfname = xmalloc ( strlen ( template ) + 5 ) ;
 strcpy ( stpcpy ( tmpfname , template ) , EXTSEP_S "tmp" ) ;

 if ( is_secured_filename ( tmpfname ) ) {
 * r_fp = NULL ;
 gpg_err_set_errno ( EPERM ) ;
 }
 else * r_fp = iobuf_create ( tmpfname , 1 ) ;
 umask ( oldmask ) ;
 if ( ! * r_fp ) {
 int rc = gpg_error_from_syserror ( ) ;
 log_error ( _ ( "can't create '%s': %s\n" ) , tmpfname , strerror ( errno ) ) ;
 xfree ( tmpfname ) ;
 xfree ( bakfname ) ;
 return rc ;
 }
 * r_bakfname = bakfname ;
 * r_tmpfname = tmpfname ;
 return 0 ;
 }
 static int rename_tmp_file ( const char * bakfname , const char * tmpfname , const char * fname ) {
 int rc = 0 ;
 if ( iobuf_ioctl ( NULL , IOBUF_IOCTL_INVALIDATE_CACHE , 0 , ( char * ) tmpfname ) ) {
 rc = gpg_error_from_syserror ( ) ;
 goto fail ;
 }
 iobuf_ioctl ( NULL , IOBUF_IOCTL_INVALIDATE_CACHE , 0 , ( char * ) bakfname ) ;
 iobuf_ioctl ( NULL , IOBUF_IOCTL_INVALIDATE_CACHE , 0 , ( char * ) fname ) ;


 rc = gpg_error_from_syserror ( ) ;
 log_error ( "renaming '%s' to '%s' failed: %s\n" , fname , bakfname , strerror ( errno ) ) ;
 return rc ;
 }


 rc = gpg_error_from_syserror ( ) ;
 log_error ( _ ( "renaming '%s' to '%s' failed: %s\n" ) , tmpfname , fname , strerror ( errno ) ) ;
 register_secured_file ( fname ) ;
 goto fail ;
 }

 struct stat statbuf ;
 statbuf . st_mode = S_IRUSR | S_IWUSR ;
 if ( ! stat ( bakfname , & statbuf ) && ! chmod ( fname , statbuf . st_mode ) ) ;
 else log_error ( "WARNING: unable to restore permissions to '%s': %s" , fname , strerror ( errno ) ) ;
 }

 fail : return rc ;
 }
 static int write_keyblock ( IOBUF fp , KBNODE keyblock ) {
 KBNODE kbctx = NULL , node ;
 int rc ;
 while ( ( node = walk_kbnode ( keyblock , & kbctx , 0 ) ) ) {
 if ( node -> pkt -> pkttype == PKT_RING_TRUST ) continue ;
 if ( ( rc = build_packet ( fp , node -> pkt ) ) ) {
 log_error ( "build_packet(%d) failed: %s\n" , node -> pkt -> pkttype , gpg_strerror ( rc ) ) ;
 return rc ;
 }
 if ( node -> pkt -> pkttype == PKT_SIGNATURE ) {
 PKT_signature * sig = node -> pkt -> pkt . signature ;
 unsigned int cacheval = 0 ;
 if ( sig -> flags . checked ) {
 cacheval |= 1 ;
 if ( sig -> flags . valid ) cacheval |= 2 ;
 }
 iobuf_put ( fp , 0xb0 ) ;
 iobuf_put ( fp , 2 ) ;
 iobuf_put ( fp , 0 ) ;
 if ( iobuf_put ( fp , cacheval ) ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( "writing sigcache packet failed\n" ) ;
 return rc ;
 }
 }
 }
 return 0 ;
 }
 int keyring_rebuild_cache ( void * token , int noisy ) {
 KEYRING_HANDLE hd ;
 KEYDB_SEARCH_DESC desc ;
 KBNODE keyblock = NULL , node ;
 const char * lastresname = NULL , * resname ;
 IOBUF tmpfp = NULL ;
 char * tmpfilename = NULL ;
 char * bakfilename = NULL ;
 int rc ;
 ulong count = 0 , sigcount = 0 ;
 hd = keyring_new ( token ) ;
 memset ( & desc , 0 , sizeof desc ) ;
 desc . mode = KEYDB_SEARCH_MODE_FIRST ;
 rc = keyring_lock ( hd , 1 ) ;
 if ( rc ) goto leave ;
 for ( ;
 ;
 ) {
 rc = keyring_search ( hd , & desc , 1 , NULL ) ;
 if ( rc && gpg_err_code ( rc ) != GPG_ERR_LEGACY_KEY ) break ;
 desc . mode = KEYDB_SEARCH_MODE_NEXT ;
 resname = keyring_get_resource_name ( hd ) ;
 if ( lastresname != resname ) {
 if ( tmpfp ) {
 if ( iobuf_close ( tmpfp ) ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( "error closing '%s': %s\n" , tmpfilename , strerror ( errno ) ) ;
 goto leave ;
 }
 tmpfp = NULL ;
 }
 rc = lastresname ? rename_tmp_file ( bakfilename , tmpfilename , lastresname ) : 0 ;
 xfree ( tmpfilename ) ;
 tmpfilename = NULL ;
 xfree ( bakfilename ) ;
 bakfilename = NULL ;
 if ( rc ) goto leave ;
 lastresname = resname ;
 if ( noisy && ! opt . quiet ) log_info ( _ ( "caching keyring '%s'\n" ) , resname ) ;
 rc = create_tmp_file ( resname , & bakfilename , & tmpfilename , & tmpfp ) ;
 if ( rc ) goto leave ;
 }
 if ( gpg_err_code ( rc ) == GPG_ERR_LEGACY_KEY ) continue ;
 release_kbnode ( keyblock ) ;
 rc = keyring_get_keyblock ( hd , & keyblock ) ;
 if ( rc ) {
 if ( gpg_err_code ( rc ) == GPG_ERR_LEGACY_KEY ) continue ;
 log_error ( "keyring_get_keyblock failed: %s\n" , gpg_strerror ( rc ) ) ;
 goto leave ;
 }
 if ( keyblock -> pkt -> pkttype != PKT_PUBLIC_KEY ) {
 log_error ( "unexpected keyblock found (pkttype=%d)%s\n" , keyblock -> pkt -> pkttype , noisy ? " - deleted" : "" ) ;
 if ( noisy ) continue ;
 log_info ( "Hint: backup your keys and try running '%s'\n" , "gpg --rebuild-keydb-caches" ) ;
 rc = gpg_error ( GPG_ERR_INV_KEYRING ) ;
 goto leave ;
 }
 if ( keyblock -> pkt -> pkt . public_key -> version < 4 ) {
 }
 else {
 for ( node = keyblock ;
 node ;
 node = node -> next ) {
 if ( node -> pkt -> pkttype == PKT_SIGNATURE ) {
 PKT_signature * sig = node -> pkt -> pkt . signature ;
 if ( ! opt . no_sig_cache && sig -> flags . checked && sig -> flags . valid && ( openpgp_md_test_algo ( sig -> digest_algo ) || openpgp_pk_test_algo ( sig -> pubkey_algo ) ) ) sig -> flags . checked = sig -> flags . valid = 0 ;
 else check_key_signature ( keyblock , node , NULL ) ;
 sigcount ++ ;
 }
 }
 rc = write_keyblock ( tmpfp , keyblock ) ;
 if ( rc ) goto leave ;
 if ( ! ( ++ count % 50 ) && noisy && ! opt . quiet ) log_info ( _ ( "%lu keys cached so far (%lu signatures)\n" ) , count , sigcount ) ;
 }
 }
 if ( rc == - 1 ) rc = 0 ;
 if ( rc ) {
 log_error ( "keyring_search failed: %s\n" , gpg_strerror ( rc ) ) ;
 goto leave ;
 }
 if ( noisy || opt . verbose ) log_info ( _ ( "%lu keys cached (%lu signatures)\n" ) , count , sigcount ) ;
 if ( tmpfp ) {
 if ( iobuf_close ( tmpfp ) ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( "error closing '%s': %s\n" , tmpfilename , strerror ( errno ) ) ;
 goto leave ;
 }
 tmpfp = NULL ;
 }
 rc = lastresname ? rename_tmp_file ( bakfilename , tmpfilename , lastresname ) : 0 ;
 xfree ( tmpfilename ) ;
 tmpfilename = NULL ;
 xfree ( bakfilename ) ;
 bakfilename = NULL ;
 leave : if ( tmpfp ) iobuf_cancel ( tmpfp ) ;
 xfree ( tmpfilename ) ;
 xfree ( bakfilename ) ;
 release_kbnode ( keyblock ) ;
 keyring_lock ( hd , 0 ) ;
 keyring_release ( hd ) ;
 return rc ;
 }
 \ f static int do_copy ( int mode , const char * fname , KBNODE root , off_t start_offset , unsigned int n_packets ) {
 IOBUF fp , newfp ;
 int rc = 0 ;
 char * bakfname = NULL ;
 char * tmpfname = NULL ;
 if ( access ( fname , W_OK ) ) return gpg_error_from_syserror ( ) ;
 fp = iobuf_open ( fname ) ;
 if ( mode == 1 && ! fp && errno == ENOENT ) {
 KBNODE kbctx , node ;
 mode_t oldmask ;
 oldmask = umask ( 077 ) ;
 if ( is_secured_filename ( fname ) ) {
 newfp = NULL ;
 gpg_err_set_errno ( EPERM ) ;
 }
 else newfp = iobuf_create ( fname , 1 ) ;
 umask ( oldmask ) ;
 if ( ! newfp ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( _ ( "can't create '%s': %s\n" ) , fname , strerror ( errno ) ) ;
 return rc ;
 }
 if ( ! opt . quiet ) log_info ( _ ( "%s: keyring created\n" ) , fname ) ;
 kbctx = NULL ;
 while ( ( node = walk_kbnode ( root , & kbctx , 0 ) ) ) {
 if ( ( rc = build_packet ( newfp , node -> pkt ) ) ) {
 log_error ( "build_packet(%d) failed: %s\n" , node -> pkt -> pkttype , gpg_strerror ( rc ) ) ;
 iobuf_cancel ( newfp ) ;
 return rc ;
 }
 }
 if ( iobuf_close ( newfp ) ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( "%s: close failed: %s\n" , fname , strerror ( errno ) ) ;
 return rc ;
 }
 return 0 ;
 }
 if ( ! fp ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( _ ( "can't open '%s': %s\n" ) , fname , strerror ( errno ) ) ;
 goto leave ;
 }
 rc = create_tmp_file ( fname , & bakfname , & tmpfname , & newfp ) ;
 if ( rc ) {
 iobuf_close ( fp ) ;
 goto leave ;
 }
 if ( mode == 1 ) {
 rc = copy_all_packets ( fp , newfp ) ;
 if ( rc != - 1 ) {
 log_error ( "%s: copy to '%s' failed: %s\n" , fname , tmpfname , gpg_strerror ( rc ) ) ;
 iobuf_close ( fp ) ;
 iobuf_cancel ( newfp ) ;
 goto leave ;
 }
 rc = 0 ;
 }
 if ( mode == 2 || mode == 3 ) {
 rc = copy_some_packets ( fp , newfp , start_offset ) ;
 if ( rc ) {
 log_error ( "%s: copy to '%s' failed: %s\n" , fname , tmpfname , gpg_strerror ( rc ) ) ;
 iobuf_close ( fp ) ;
 iobuf_cancel ( newfp ) ;
 goto leave ;
 }
 assert ( n_packets ) ;
 rc = skip_some_packets ( fp , n_packets ) ;
 if ( rc ) {
 log_error ( "%s: skipping %u packets failed: %s\n" , fname , n_packets , gpg_strerror ( rc ) ) ;
 iobuf_close ( fp ) ;
 iobuf_cancel ( newfp ) ;
 goto leave ;
 }
 }
 if ( mode == 1 || mode == 3 ) {
 rc = write_keyblock ( newfp , root ) ;
 if ( rc ) {
 iobuf_close ( fp ) ;
 iobuf_cancel ( newfp ) ;
 goto leave ;
 }
 }
 if ( mode == 2 || mode == 3 ) {
 rc = copy_all_packets ( fp , newfp ) ;
 if ( rc != - 1 ) {
 log_error ( "%s: copy to '%s' failed: %s\n" , fname , tmpfname , gpg_strerror ( rc ) ) ;
 iobuf_close ( fp ) ;
 iobuf_cancel ( newfp ) ;
 goto leave ;
 }
 rc = 0 ;
 }
 if ( iobuf_close ( fp ) ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( "%s: close failed: %s\n" , fname , strerror ( errno ) ) ;
 goto leave ;
 }
 if ( iobuf_close ( newfp ) ) {
 rc = gpg_error_from_syserror ( ) ;
 log_error ( "%s: close failed: %s\n" , tmpfname , strerror ( errno ) ) ;
 goto leave ;
 }
 rc = rename_tmp_file ( bakfname , tmpfname , fname ) ;
 leave : xfree ( bakfname ) ;
 xfree ( tmpfname ) ;
 return rc ;
 }