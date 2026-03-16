static void rv34_mc_2mv_skip ( RV34DecContext * r ) {
 int i , j ;
 int weighted = ! r -> rv30 && r -> weight1 != 8192 ;
 for ( j = 0 ;
 j < 2 ;
 j ++ ) for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 rv34_mc ( r , RV34_MB_P_8x8 , i * 8 , j * 8 , i + j * r -> s . b8_stride , 1 , 1 , 0 , r -> rv30 , weighted , r -> rdsp . put_pixels_tab , r -> rdsp . put_chroma_pixels_tab ) ;
 rv34_mc ( r , RV34_MB_P_8x8 , i * 8 , j * 8 , i + j * r -> s . b8_stride , 1 , 1 , 1 , r -> rv30 , weighted , weighted ? r -> rdsp . put_pixels_tab : r -> rdsp . avg_pixels_tab , weighted ? r -> rdsp . put_chroma_pixels_tab : r -> rdsp . avg_chroma_pixels_tab ) ;
 }
 if ( weighted ) rv4_weight ( r ) ;
 }