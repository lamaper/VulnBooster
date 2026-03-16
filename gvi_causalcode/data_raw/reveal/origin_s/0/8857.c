static uint64_t thd_channel_layout_extract_channel ( uint64_t channel_layout , int index ) {
 int i ;
 if ( av_get_channel_layout_nb_channels ( channel_layout ) <= index ) return 0 ;
 for ( i = 0 ;
 i < FF_ARRAY_ELEMS ( thd_channel_order ) ;
 i ++ ) if ( channel_layout & thd_channel_order [ i ] && ! index -- ) return thd_channel_order [ i ] ;
 return 0 ;
 }