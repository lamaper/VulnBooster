static void parse_presentation_segment ( AVCodecContext * avctx , const uint8_t * buf , int buf_size ) {
 PGSSubContext * ctx = avctx -> priv_data ;
 int w = bytestream_get_be16 ( & buf ) ;
 int h = bytestream_get_be16 ( & buf ) ;
 uint16_t object_index ;
 av_dlog ( avctx , "Video Dimensions %dx%d\n" , w , h ) ;
 if ( av_image_check_size ( w , h , 0 , avctx ) >= 0 ) avcodec_set_dimensions ( avctx , w , h ) ;
 buf ++ ;
 ctx -> presentation . id_number = bytestream_get_be16 ( & buf ) ;
 buf += 3 ;
 ctx -> presentation . object_count = bytestream_get_byte ( & buf ) ;
 if ( ! ctx -> presentation . object_count ) return ;
 buf_size -= 11 ;
 if ( buf_size < ctx -> presentation . object_count * 8 ) {
 ctx -> presentation . object_count = 0 ;
 return ;
 }
 av_freep ( & ctx -> presentation . objects ) ;
 ctx -> presentation . objects = av_malloc ( sizeof ( PGSSubPictureReference ) * ctx -> presentation . object_count ) ;
 if ( ! ctx -> presentation . objects ) {
 ctx -> presentation . object_count = 0 ;
 return ;
 }
 for ( object_index = 0 ;
 object_index < ctx -> presentation . object_count ;
 ++ object_index ) {
 PGSSubPictureReference * reference = & ctx -> presentation . objects [ object_index ] ;
 reference -> picture_id = bytestream_get_be16 ( & buf ) ;
 buf ++ ;
 reference -> composition = bytestream_get_byte ( & buf ) ;
 reference -> x = bytestream_get_be16 ( & buf ) ;
 reference -> y = bytestream_get_be16 ( & buf ) ;
 av_dlog ( avctx , "Subtitle Placement ID=%d, x=%d, y=%d\n" , reference -> picture_id , reference -> x , reference -> y ) ;
 if ( reference -> x > avctx -> width || reference -> y > avctx -> height ) {
 av_log ( avctx , AV_LOG_ERROR , "Subtitle out of video bounds. x = %d, y = %d, video width = %d, video height = %d.\n" , reference -> x , reference -> y , avctx -> width , avctx -> height ) ;
 reference -> x = 0 ;
 reference -> y = 0 ;
 }
 }
 }