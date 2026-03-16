static int nntp_mbox_sync ( struct Context * ctx , int * index_hint ) {
 struct NntpData * nntp_data = ctx -> data ;
 int rc ;


 rc = check_mailbox ( ctx ) ;
 if ( rc ) return rc ;

 hc = nntp_hcache_open ( nntp_data ) ;

 i < ctx -> msgcount ;
 i ++ ) {
 struct Header * hdr = ctx -> hdrs [ i ] ;
 char buf [ 16 ] ;
 snprintf ( buf , sizeof ( buf ) , "%d" , NHDR ( hdr ) -> article_num ) ;
 if ( nntp_data -> bcache && hdr -> deleted ) {
 mutt_debug ( 2 , "mutt_bcache_del %s\n" , buf ) ;
 mutt_bcache_del ( nntp_data -> bcache , buf ) ;
 }

 if ( hdr -> deleted && ! hdr -> read ) nntp_data -> unread -- ;
 mutt_debug ( 2 , "mutt_hcache_store %s\n" , buf ) ;
 mutt_hcache_store ( hc , buf , strlen ( buf ) , hdr , 0 ) ;
 }


 mutt_hcache_close ( hc ) ;
 nntp_data -> last_cached = nntp_data -> last_loaded ;
 }

 nntp_newsrc_update ( nntp_data -> nserv ) ;
 nntp_newsrc_close ( nntp_data -> nserv ) ;
 return 0 ;
 }