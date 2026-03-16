static void matroska_fix_ass_packet ( MatroskaDemuxContext * matroska , AVPacket * pkt , uint64_t display_duration ) {
 AVBufferRef * line ;
 char * layer , * ptr = pkt -> data , * end = ptr + pkt -> size ;
 for ( ;
 * ptr != ',' && ptr < end - 1 ;
 ptr ++ ) ;
 if ( * ptr == ',' ) layer = ++ ptr ;
 for ( ;
 * ptr != ',' && ptr < end - 1 ;
 ptr ++ ) ;
 if ( * ptr == ',' ) {
 int64_t end_pts = pkt -> pts + display_duration ;
 int sc = matroska -> time_scale * pkt -> pts / 10000000 ;
 int ec = matroska -> time_scale * end_pts / 10000000 ;
 int sh , sm , ss , eh , em , es , len ;
 sh = sc / 360000 ;
 sc -= 360000 * sh ;
 sm = sc / 6000 ;
 sc -= 6000 * sm ;
 ss = sc / 100 ;
 sc -= 100 * ss ;
 eh = ec / 360000 ;
 ec -= 360000 * eh ;
 em = ec / 6000 ;
 ec -= 6000 * em ;
 es = ec / 100 ;
 ec -= 100 * es ;
 * ptr ++ = '\0' ;
 len = 50 + end - ptr + FF_INPUT_BUFFER_PADDING_SIZE ;
 if ( ! ( line = av_buffer_alloc ( len ) ) ) return ;
 snprintf ( line -> data , len , "Dialogue: %s,%d:%02d:%02d.%02d,%d:%02d:%02d.%02d,%s\r\n" , layer , sh , sm , ss , sc , eh , em , es , ec , ptr ) ;
 av_buffer_unref ( & pkt -> buf ) ;
 pkt -> buf = line ;
 pkt -> data = line -> data ;
 pkt -> size = strlen ( line -> data ) ;
 }
 }