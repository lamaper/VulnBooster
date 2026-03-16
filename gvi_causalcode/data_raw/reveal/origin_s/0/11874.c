void vp9_get_entropy_contexts ( BLOCK_SIZE bsize , TX_SIZE tx_size , const struct macroblockd_plane * pd , ENTROPY_CONTEXT t_above [ 16 ] , ENTROPY_CONTEXT t_left [ 16 ] ) {
 const BLOCK_SIZE plane_bsize = get_plane_block_size ( bsize , pd ) ;
 const int num_4x4_w = num_4x4_blocks_wide_lookup [ plane_bsize ] ;
 const int num_4x4_h = num_4x4_blocks_high_lookup [ plane_bsize ] ;
 const ENTROPY_CONTEXT * const above = pd -> above_context ;
 const ENTROPY_CONTEXT * const left = pd -> left_context ;
 int i ;
 switch ( tx_size ) {
 case TX_4X4 : vpx_memcpy ( t_above , above , sizeof ( ENTROPY_CONTEXT ) * num_4x4_w ) ;
 vpx_memcpy ( t_left , left , sizeof ( ENTROPY_CONTEXT ) * num_4x4_h ) ;
 break ;
 case TX_8X8 : for ( i = 0 ;
 i < num_4x4_w ;
 i += 2 ) t_above [ i ] = ! ! * ( const uint16_t * ) & above [ i ] ;
 for ( i = 0 ;
 i < num_4x4_h ;
 i += 2 ) t_left [ i ] = ! ! * ( const uint16_t * ) & left [ i ] ;
 break ;
 case TX_16X16 : for ( i = 0 ;
 i < num_4x4_w ;
 i += 4 ) t_above [ i ] = ! ! * ( const uint32_t * ) & above [ i ] ;
 for ( i = 0 ;
 i < num_4x4_h ;
 i += 4 ) t_left [ i ] = ! ! * ( const uint32_t * ) & left [ i ] ;
 break ;
 case TX_32X32 : for ( i = 0 ;
 i < num_4x4_w ;
 i += 8 ) t_above [ i ] = ! ! * ( const uint64_t * ) & above [ i ] ;
 for ( i = 0 ;
 i < num_4x4_h ;
 i += 8 ) t_left [ i ] = ! ! * ( const uint64_t * ) & left [ i ] ;
 break ;
 default : assert ( 0 && "Invalid transform size." ) ;
 break ;
 }
 }