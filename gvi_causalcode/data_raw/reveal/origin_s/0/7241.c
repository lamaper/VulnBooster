static gpg_error_t build_keyblock_image ( kbnode_t keyblock , iobuf_t * r_iobuf , u32 * * r_sigstatus ) {
 gpg_error_t err ;
 iobuf_t iobuf ;
 kbnode_t kbctx , node ;
 u32 n_sigs ;
 u32 * sigstatus ;
 * r_iobuf = NULL ;
 if ( r_sigstatus ) * r_sigstatus = NULL ;
 if ( r_sigstatus ) {
 for ( kbctx = NULL , n_sigs = 0 ;
 ( node = walk_kbnode ( keyblock , & kbctx , 0 ) ) ;
 ) if ( node -> pkt -> pkttype == PKT_SIGNATURE ) n_sigs ++ ;
 sigstatus = xtrycalloc ( 1 + n_sigs , sizeof * sigstatus ) ;
 if ( ! sigstatus ) return gpg_error_from_syserror ( ) ;
 }
 else sigstatus = NULL ;
 iobuf = iobuf_temp ( ) ;
 for ( kbctx = NULL , n_sigs = 0 ;
 ( node = walk_kbnode ( keyblock , & kbctx , 0 ) ) ;
 ) {
 switch ( node -> pkt -> pkttype ) {
 case PKT_PUBLIC_KEY : case PKT_PUBLIC_SUBKEY : case PKT_SIGNATURE : case PKT_USER_ID : case PKT_ATTRIBUTE : break ;
 default : continue ;
 }
 err = build_packet ( iobuf , node -> pkt ) ;
 if ( err ) {
 iobuf_close ( iobuf ) ;
 return err ;
 }
 if ( node -> pkt -> pkttype == PKT_SIGNATURE ) {
 PKT_signature * sig = node -> pkt -> pkt . signature ;
 n_sigs ++ ;
 if ( sig -> flags . checked && sigstatus ) {
 if ( sig -> flags . valid ) {
 if ( ! sig -> expiredate ) sigstatus [ n_sigs ] = 0xffffffff ;
 else if ( sig -> expiredate < 0x1000000 ) sigstatus [ n_sigs ] = 0x10000000 ;
 else sigstatus [ n_sigs ] = sig -> expiredate ;
 }
 else sigstatus [ n_sigs ] = 0x00000002 ;
 }
 }
 }
 if ( sigstatus ) sigstatus [ 0 ] = n_sigs ;
 * r_iobuf = iobuf ;
 if ( r_sigstatus ) * r_sigstatus = sigstatus ;
 return 0 ;
 }