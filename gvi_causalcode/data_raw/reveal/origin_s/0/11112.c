void ff_ivi_init_static_vlc ( void ) {
 int i ;
 static VLC_TYPE table_data [ 8192 * 16 ] [ 2 ] ;
 static int initialized_vlcs = 0 ;
 if ( initialized_vlcs ) return ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 ivi_mb_vlc_tabs [ i ] . table = table_data + i * 2 * 8192 ;
 ivi_mb_vlc_tabs [ i ] . table_allocated = 8192 ;
 ivi_create_huff_from_desc ( & ff_ivi_mb_huff_desc [ i ] , & ivi_mb_vlc_tabs [ i ] , 1 ) ;
 ivi_blk_vlc_tabs [ i ] . table = table_data + ( i * 2 + 1 ) * 8192 ;
 ivi_blk_vlc_tabs [ i ] . table_allocated = 8192 ;
 ivi_create_huff_from_desc ( & ff_ivi_blk_huff_desc [ i ] , & ivi_blk_vlc_tabs [ i ] , 1 ) ;
 }
 initialized_vlcs = 1 ;
 }