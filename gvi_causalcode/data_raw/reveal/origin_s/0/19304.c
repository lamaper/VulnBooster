static int ogg_reset ( AVFormatContext * s ) {
 struct ogg * ogg = s -> priv_data ;
 int i ;
 int64_t start_pos = avio_tell ( s -> pb ) ;
 for ( i = 0 ;
 i < ogg -> nstreams ;
 i ++ ) {
 struct ogg_stream * os = ogg -> streams + i ;
 os -> bufpos = 0 ;
 os -> pstart = 0 ;
 os -> psize = 0 ;
 os -> granule = - 1 ;
 os -> lastpts = AV_NOPTS_VALUE ;
 os -> lastdts = AV_NOPTS_VALUE ;
 os -> sync_pos = - 1 ;
 os -> page_pos = 0 ;
 os -> nsegs = 0 ;
 os -> segp = 0 ;
 os -> incomplete = 0 ;
 os -> got_data = 0 ;
 if ( start_pos <= s -> internal -> data_offset ) {
 os -> lastpts = 0 ;
 }
 os -> end_trimming = 0 ;
 av_freep ( & os -> new_metadata ) ;
 os -> new_metadata_size = 0 ;
 }
 ogg -> page_pos = - 1 ;
 ogg -> curidx = - 1 ;
 return 0 ;
 }