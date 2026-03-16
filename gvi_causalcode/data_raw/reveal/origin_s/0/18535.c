int gdev_mem_bits_size ( const gx_device_memory * dev , int width , int height , ulong * psize ) {
 int num_planes = dev -> is_planar ? dev -> color_info . num_components : 0 ;
 gx_render_plane_t plane1 ;
 const gx_render_plane_t * planes ;
 ulong size ;
 int pi ;
 if ( num_planes ) planes = dev -> planes ;
 else planes = & plane1 , plane1 . depth = dev -> color_info . depth , num_planes = 1 ;
 for ( size = 0 , pi = 0 ;
 pi < num_planes ;
 ++ pi ) size += bitmap_raster_pad_align ( width * planes [ pi ] . depth , dev -> pad , dev -> log2_align_mod ) ;
 if ( height != 0 ) if ( size > ( max_ulong - ARCH_ALIGN_PTR_MOD ) / ( ulong ) height ) return_error ( gs_error_VMerror ) ;
 size = ROUND_UP ( size * height , ARCH_ALIGN_PTR_MOD ) ;
 if ( dev -> log2_align_mod > log2_align_bitmap_mod ) size += 1 << dev -> log2_align_mod ;
 * psize = size ;
 return 0 ;
 }