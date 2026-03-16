static int display_end_segment ( AVCodecContext * avctx , void * data , const uint8_t * buf , int buf_size ) {
 AVSubtitle * sub = data ;
 PGSSubContext * ctx = avctx -> priv_data ;
 int64_t pts ;
 uint16_t rect ;
 pts = ctx -> pts != AV_NOPTS_VALUE ? ctx -> pts : sub -> pts ;
 memset ( sub , 0 , sizeof ( * sub ) ) ;
 sub -> pts = pts ;
 ctx -> pts = AV_NOPTS_VALUE ;
 if ( ! ctx -> presentation . object_count ) return 1 ;
 sub -> start_display_time = 0 ;
 sub -> end_display_time = 20000 ;
 sub -> format = 0 ;
 sub -> num_rects = ctx -> presentation . object_count ;
 sub -> rects = av_mallocz ( sizeof ( * sub -> rects ) * sub -> num_rects ) ;
 for ( rect = 0 ;
 rect < sub -> num_rects ;
 ++ rect ) {
 uint16_t picture_id = ctx -> presentation . objects [ rect ] . picture_id ;
 sub -> rects [ rect ] = av_mallocz ( sizeof ( * sub -> rects [ rect ] ) ) ;
 sub -> rects [ rect ] -> x = ctx -> presentation . objects [ rect ] . x ;
 sub -> rects [ rect ] -> y = ctx -> presentation . objects [ rect ] . y ;
 sub -> rects [ rect ] -> w = ctx -> pictures [ picture_id ] . w ;
 sub -> rects [ rect ] -> h = ctx -> pictures [ picture_id ] . h ;
 sub -> rects [ rect ] -> type = SUBTITLE_BITMAP ;
 sub -> rects [ rect ] -> pict . linesize [ 0 ] = ctx -> pictures [ picture_id ] . w ;
 if ( ctx -> pictures [ picture_id ] . rle ) {
 if ( ctx -> pictures [ picture_id ] . rle_remaining_len ) av_log ( avctx , AV_LOG_ERROR , "RLE data length %u is %u bytes shorter than expected\n" , ctx -> pictures [ picture_id ] . rle_data_len , ctx -> pictures [ picture_id ] . rle_remaining_len ) ;
 if ( decode_rle ( avctx , sub , rect , ctx -> pictures [ picture_id ] . rle , ctx -> pictures [ picture_id ] . rle_data_len ) < 0 ) return 0 ;
 }
 sub -> rects [ rect ] -> nb_colors = 256 ;
 sub -> rects [ rect ] -> pict . data [ 1 ] = av_mallocz ( AVPALETTE_SIZE ) ;
 sub -> rects [ rect ] -> flags = ( ctx -> presentation . objects [ rect ] . composition & 0x40 ) != 0 ? AV_SUBTITLE_FLAG_FORCED : 0 ;
 if ( ! ctx -> forced_subs_only || ctx -> presentation . objects [ rect ] . composition & 0x40 ) memcpy ( sub -> rects [ rect ] -> pict . data [ 1 ] , ctx -> clut , sub -> rects [ rect ] -> nb_colors * sizeof ( uint32_t ) ) ;
 }
 return 1 ;
 }