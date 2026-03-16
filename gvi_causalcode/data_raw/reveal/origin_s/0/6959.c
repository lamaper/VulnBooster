static void tm2_free_codes ( TM2Codes * code ) {
 av_free ( code -> recode ) ;
 if ( code -> vlc . table ) ff_free_vlc ( & code -> vlc ) ;
 }