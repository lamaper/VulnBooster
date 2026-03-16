static int64_t put_header ( AVIOContext * pb , const ff_asf_guid * g ) {
 int64_t pos ;
 pos = avio_tell ( pb ) ;
 ff_put_guid ( pb , g ) ;
 avio_wl64 ( pb , 24 ) ;
 return pos ;
 }