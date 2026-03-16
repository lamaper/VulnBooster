void ff_cavs_load_intra_pred_luma ( AVSContext * h , uint8_t * top , uint8_t * * left , int block ) {
 int i ;
 switch ( block ) {
 case 0 : * left = h -> left_border_y ;
 h -> left_border_y [ 0 ] = h -> left_border_y [ 1 ] ;
 memset ( & h -> left_border_y [ 17 ] , h -> left_border_y [ 16 ] , 9 ) ;
 memcpy ( & top [ 1 ] , & h -> top_border_y [ h -> mbx * 16 ] , 16 ) ;
 top [ 17 ] = top [ 16 ] ;
 top [ 0 ] = top [ 1 ] ;
 if ( ( h -> flags & A_AVAIL ) && ( h -> flags & B_AVAIL ) ) h -> left_border_y [ 0 ] = top [ 0 ] = h -> topleft_border_y ;
 break ;
 case 1 : * left = h -> intern_border_y ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) h -> intern_border_y [ i + 1 ] = * ( h -> cy + 7 + i * h -> l_stride ) ;
 memset ( & h -> intern_border_y [ 9 ] , h -> intern_border_y [ 8 ] , 9 ) ;
 h -> intern_border_y [ 0 ] = h -> intern_border_y [ 1 ] ;
 memcpy ( & top [ 1 ] , & h -> top_border_y [ h -> mbx * 16 + 8 ] , 8 ) ;
 if ( h -> flags & C_AVAIL ) memcpy ( & top [ 9 ] , & h -> top_border_y [ ( h -> mbx + 1 ) * 16 ] , 8 ) ;
 else memset ( & top [ 9 ] , top [ 8 ] , 9 ) ;
 top [ 17 ] = top [ 16 ] ;
 top [ 0 ] = top [ 1 ] ;
 if ( h -> flags & B_AVAIL ) h -> intern_border_y [ 0 ] = top [ 0 ] = h -> top_border_y [ h -> mbx * 16 + 7 ] ;
 break ;
 case 2 : * left = & h -> left_border_y [ 8 ] ;
 memcpy ( & top [ 1 ] , h -> cy + 7 * h -> l_stride , 16 ) ;
 top [ 17 ] = top [ 16 ] ;
 top [ 0 ] = top [ 1 ] ;
 if ( h -> flags & A_AVAIL ) top [ 0 ] = h -> left_border_y [ 8 ] ;
 break ;
 case 3 : * left = & h -> intern_border_y [ 8 ] ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) h -> intern_border_y [ i + 9 ] = * ( h -> cy + 7 + ( i + 8 ) * h -> l_stride ) ;
 memset ( & h -> intern_border_y [ 17 ] , h -> intern_border_y [ 16 ] , 9 ) ;
 memcpy ( & top [ 0 ] , h -> cy + 7 + 7 * h -> l_stride , 9 ) ;
 memset ( & top [ 9 ] , top [ 8 ] , 9 ) ;
 break ;
 }
 }