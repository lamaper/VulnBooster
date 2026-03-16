static int ogg_read_close ( AVFormatContext * s ) {
 struct ogg * ogg = s -> priv_data ;
 int i ;
 for ( i = 0 ;
 i < ogg -> nstreams ;
 i ++ ) {
 av_freep ( & ogg -> streams [ i ] . buf ) ;
 if ( ogg -> streams [ i ] . codec && ogg -> streams [ i ] . codec -> cleanup ) {
 ogg -> streams [ i ] . codec -> cleanup ( s , i ) ;
 }
 av_freep ( & ogg -> streams [ i ] . private ) ;
 av_freep ( & ogg -> streams [ i ] . new_metadata ) ;
 }
 ogg -> nstreams = 0 ;
 av_freep ( & ogg -> streams ) ;
 return 0 ;
 }