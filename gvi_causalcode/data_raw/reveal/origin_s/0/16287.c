static void get_cx_data ( struct stream_state * stream , struct VpxEncoderConfig * global , int * got_data ) {
 const vpx_codec_cx_pkt_t * pkt ;
 const struct vpx_codec_enc_cfg * cfg = & stream -> config . cfg ;
 vpx_codec_iter_t iter = NULL ;
 * got_data = 0 ;
 while ( ( pkt = vpx_codec_get_cx_data ( & stream -> encoder , & iter ) ) ) {
 static size_t fsize = 0 ;
 static int64_t ivf_header_pos = 0 ;
 switch ( pkt -> kind ) {
 case VPX_CODEC_CX_FRAME_PKT : if ( ! ( pkt -> data . frame . flags & VPX_FRAME_IS_FRAGMENT ) ) {
 stream -> frames_out ++ ;
 }
 if ( ! global -> quiet ) fprintf ( stderr , " %6luF" , ( unsigned long ) pkt -> data . frame . sz ) ;
 update_rate_histogram ( stream -> rate_hist , cfg , pkt ) ;

 write_webm_block ( & stream -> ebml , cfg , pkt ) ;
 }

 if ( pkt -> data . frame . partition_id <= 0 ) {
 ivf_header_pos = ftello ( stream -> file ) ;
 fsize = pkt -> data . frame . sz ;
 ivf_write_frame_header ( stream -> file , pkt -> data . frame . pts , fsize ) ;
 }
 else {
 fsize += pkt -> data . frame . sz ;
 if ( ! ( pkt -> data . frame . flags & VPX_FRAME_IS_FRAGMENT ) ) {
 const int64_t currpos = ftello ( stream -> file ) ;
 fseeko ( stream -> file , ivf_header_pos , SEEK_SET ) ;
 ivf_write_frame_size ( stream -> file , fsize ) ;
 fseeko ( stream -> file , currpos , SEEK_SET ) ;
 }
 }
 ( void ) fwrite ( pkt -> data . frame . buf , 1 , pkt -> data . frame . sz , stream -> file ) ;
 }
 stream -> nbytes += pkt -> data . raw . sz ;
 * got_data = 1 ;

 vpx_codec_decode ( & stream -> decoder , pkt -> data . frame . buf , ( unsigned int ) pkt -> data . frame . sz , NULL , 0 ) ;
 if ( stream -> decoder . err ) {
 warn_or_exit_on_error ( & stream -> decoder , global -> test_decode == TEST_DECODE_FATAL , "Failed to decode frame %d in stream %d" , stream -> frames_out + 1 , stream -> index ) ;
 stream -> mismatch_seen = stream -> frames_out + 1 ;
 }
 }

 case VPX_CODEC_STATS_PKT : stream -> frames_out ++ ;
 stats_write ( & stream -> stats , pkt -> data . twopass_stats . buf , pkt -> data . twopass_stats . sz ) ;
 stream -> nbytes += pkt -> data . raw . sz ;
 break ;

 stream -> nbytes += pkt -> data . raw . sz ;
 break ;

 int i ;
 stream -> psnr_sse_total += pkt -> data . psnr . sse [ 0 ] ;
 stream -> psnr_samples_total += pkt -> data . psnr . samples [ 0 ] ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 if ( ! global -> quiet ) fprintf ( stderr , "%.3f " , pkt -> data . psnr . psnr [ i ] ) ;
 stream -> psnr_totals [ i ] += pkt -> data . psnr . psnr [ i ] ;
 }
 stream -> psnr_count ++ ;
 }
 break ;
 default : break ;
 }
 }
 }