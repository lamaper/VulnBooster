static int write_superframe_index ( vpx_codec_alg_priv_t * ctx ) {
 uint8_t marker = 0xc0 ;
 unsigned int mask ;
 int mag , index_sz ;
 assert ( ctx -> pending_frame_count ) ;
 assert ( ctx -> pending_frame_count <= 8 ) ;
 marker |= ctx -> pending_frame_count - 1 ;
 for ( mag = 0 , mask = 0xff ;
 mag < 4 ;
 mag ++ ) {
 if ( ctx -> pending_frame_magnitude < mask ) break ;
 mask <<= 8 ;
 mask |= 0xff ;
 }
 marker |= mag << 3 ;
 index_sz = 2 + ( mag + 1 ) * ctx -> pending_frame_count ;
 if ( ctx -> pending_cx_data_sz + index_sz < ctx -> cx_data_sz ) {
 uint8_t * x = ctx -> pending_cx_data + ctx -> pending_cx_data_sz ;
 int i , j ;

 int mag_test = 2 ;
 int frames_test = 4 ;
 int index_sz_test = 2 + mag_test * frames_test ;
 marker_test |= frames_test - 1 ;
 marker_test |= ( mag_test - 1 ) << 3 ;
 * x ++ = marker_test ;
 for ( i = 0 ;
 i < mag_test * frames_test ;
 ++ i ) * x ++ = 0 ;
 * x ++ = marker_test ;
 ctx -> pending_cx_data_sz += index_sz_test ;
 printf ( "Added supplemental superframe data\n" ) ;

 for ( i = 0 ;
 i < ctx -> pending_frame_count ;
 i ++ ) {
 unsigned int this_sz = ( unsigned int ) ctx -> pending_frame_sizes [ i ] ;
 for ( j = 0 ;
 j <= mag ;
 j ++ ) {
 * x ++ = this_sz & 0xff ;
 this_sz >>= 8 ;
 }
 }
 * x ++ = marker ;
 ctx -> pending_cx_data_sz += index_sz ;


 return index_sz ;
 }