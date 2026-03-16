int file_is_raw ( struct VpxInputContext * input ) {
 uint8_t buf [ 32 ] ;
 int is_raw = 0 ;
 vpx_codec_stream_info_t si ;
 si . sz = sizeof ( si ) ;
 if ( fread ( buf , 1 , 32 , input -> file ) == 32 ) {
 int i ;
 if ( mem_get_le32 ( buf ) < 256 * 1024 * 1024 ) {
 for ( i = 0 ;
 i < get_vpx_decoder_count ( ) ;
 ++ i ) {
 const VpxInterface * const decoder = get_vpx_decoder_by_index ( i ) ;
 if ( ! vpx_codec_peek_stream_info ( decoder -> codec_interface ( ) , buf + 4 , 32 - 4 , & si ) ) {
 is_raw = 1 ;
 input -> fourcc = decoder -> fourcc ;
 input -> width = si . w ;
 input -> height = si . h ;
 input -> framerate . numerator = 30 ;
 input -> framerate . denominator = 1 ;
 break ;
 }
 }
 }
 }
 rewind ( input -> file ) ;
 return is_raw ;
 }