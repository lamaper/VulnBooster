vpx_codec_err_t vp9_parse_superframe_index ( const uint8_t * data , size_t data_sz , uint32_t sizes [ 8 ] , int * count , vpx_decrypt_cb decrypt_cb , void * decrypt_state ) {
 uint8_t marker ;
 assert ( data_sz ) ;
 marker = read_marker ( decrypt_cb , decrypt_state , data + data_sz - 1 ) ;
 * count = 0 ;
 if ( ( marker & 0xe0 ) == 0xc0 ) {
 const uint32_t frames = ( marker & 0x7 ) + 1 ;
 const uint32_t mag = ( ( marker >> 3 ) & 0x3 ) + 1 ;
 const size_t index_sz = 2 + mag * frames ;
 if ( data_sz < index_sz ) return VPX_CODEC_CORRUPT_FRAME ;
 {
 const uint8_t marker2 = read_marker ( decrypt_cb , decrypt_state , data + data_sz - index_sz ) ;
 if ( marker != marker2 ) return VPX_CODEC_CORRUPT_FRAME ;
 }
 {
 uint32_t i , j ;
 const uint8_t * x = & data [ data_sz - index_sz + 1 ] ;
 uint8_t clear_buffer [ 32 ] ;
 assert ( sizeof ( clear_buffer ) >= frames * mag ) ;
 if ( decrypt_cb ) {
 decrypt_cb ( decrypt_state , x , clear_buffer , frames * mag ) ;
 x = clear_buffer ;
 }
 for ( i = 0 ;
 i < frames ;
 ++ i ) {
 uint32_t this_sz = 0 ;
 for ( j = 0 ;
 j < mag ;
 ++ j ) this_sz |= ( * x ++ ) << ( j * 8 ) ;
 sizes [ i ] = this_sz ;
 }
 * count = frames ;
 }
 }
 return VPX_CODEC_OK ;
 }