static void rv4_weight ( RV34DecContext * r ) {
 r -> rdsp . rv40_weight_pixels_tab [ r -> scaled_weight ] [ 0 ] ( r -> s . dest [ 0 ] , r -> tmp_b_block_y [ 0 ] , r -> tmp_b_block_y [ 1 ] , r -> weight1 , r -> weight2 , r -> s . linesize ) ;
 r -> rdsp . rv40_weight_pixels_tab [ r -> scaled_weight ] [ 1 ] ( r -> s . dest [ 1 ] , r -> tmp_b_block_uv [ 0 ] , r -> tmp_b_block_uv [ 2 ] , r -> weight1 , r -> weight2 , r -> s . uvlinesize ) ;
 r -> rdsp . rv40_weight_pixels_tab [ r -> scaled_weight ] [ 1 ] ( r -> s . dest [ 2 ] , r -> tmp_b_block_uv [ 1 ] , r -> tmp_b_block_uv [ 3 ] , r -> weight1 , r -> weight2 , r -> s . uvlinesize ) ;
 }