static void create_clusters ( const AVFrame * frame , int w , int h , uint8_t * yuvClusters ) {
 int i , j , k , l ;
 for ( i = 0 ;
 i < h ;
 i += 4 ) for ( j = 0 ;
 j < w ;
 j += 4 ) {
 for ( k = 0 ;
 k < 2 ;
 k ++ ) for ( l = 0 ;
 l < 2 ;
 l ++ ) frame_block_to_cell ( yuvClusters + ( l + 2 * k ) * 6 , frame -> data , i + 2 * k , j + 2 * l , frame -> linesize ) ;
 yuvClusters += 24 ;
 }
 }