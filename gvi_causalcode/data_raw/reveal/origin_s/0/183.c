static void end_header ( AVIOContext * pb , int64_t pos ) {
 int64_t pos1 ;
 pos1 = avio_tell ( pb ) ;
 avio_seek ( pb , pos + 16 , SEEK_SET ) ;
 avio_wl64 ( pb , pos1 - pos ) ;
 avio_seek ( pb , pos1 , SEEK_SET ) ;
 }