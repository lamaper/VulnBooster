int gdev_mem_set_line_ptrs ( gx_device_memory * mdev , byte * base , int raster , byte * * line_ptrs , int setup_height ) {
 int num_planes = ( mdev -> is_planar ? mdev -> color_info . num_components : 0 ) ;
 byte * * pline ;
 byte * data ;
 int pi ;
 if ( line_ptrs ) mdev -> line_ptrs = line_ptrs ;
 pline = mdev -> line_ptrs ;
 if ( base == NULL ) {
 base = mdev -> base ;
 raster = mdev -> raster ;
 }
 else {
 mdev -> base = base ;
 mdev -> raster = raster ;
 }
 if ( mdev -> log2_align_mod > log2_align_bitmap_mod ) {
 int align = 1 << mdev -> log2_align_mod ;
 align = ( - ( int ) ( intptr_t ) base ) & ( align - 1 ) ;
 data = base + align ;
 }
 else {
 data = mdev -> base ;
 }
 if ( num_planes ) {
 if ( base && ! mdev -> plane_depth ) return_error ( gs_error_rangecheck ) ;
 }
 else {
 num_planes = 1 ;
 }
 for ( pi = 0 ;
 pi < num_planes ;
 ++ pi ) {
 byte * * pptr = pline ;
 byte * * pend = pptr + setup_height ;
 byte * scan_line = data ;
 while ( pptr < pend ) {
 * pptr ++ = scan_line ;
 scan_line += raster ;
 }
 data += raster * mdev -> height ;
 pline += setup_height ;
 }
 return 0 ;
 }