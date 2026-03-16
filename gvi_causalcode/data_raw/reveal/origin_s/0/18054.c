static void tree_to_node ( void * data , BLOCK_SIZE bsize , variance_node * node ) {
 int i ;
 node -> part_variances = NULL ;
 vpx_memset ( node -> split , 0 , sizeof ( node -> split ) ) ;
 switch ( bsize ) {
 case BLOCK_64X64 : {
 v64x64 * vt = ( v64x64 * ) data ;
 node -> part_variances = & vt -> part_variances ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) node -> split [ i ] = & vt -> split [ i ] . part_variances . none ;
 break ;
 }
 case BLOCK_32X32 : {
 v32x32 * vt = ( v32x32 * ) data ;
 node -> part_variances = & vt -> part_variances ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) node -> split [ i ] = & vt -> split [ i ] . part_variances . none ;
 break ;
 }
 case BLOCK_16X16 : {
 v16x16 * vt = ( v16x16 * ) data ;
 node -> part_variances = & vt -> part_variances ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) node -> split [ i ] = & vt -> split [ i ] . part_variances . none ;
 break ;
 }
 case BLOCK_8X8 : {
 v8x8 * vt = ( v8x8 * ) data ;
 node -> part_variances = & vt -> part_variances ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) node -> split [ i ] = & vt -> split [ i ] ;
 break ;
 }
 default : {
 assert ( 0 ) ;
 break ;
 }
 }
 }