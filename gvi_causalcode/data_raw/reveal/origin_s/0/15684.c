void gdev_mem_mono_set_inverted ( gx_device_memory * dev , bool black_is_1 ) {
 if ( black_is_1 ) dev -> palette = mem_mono_b_w_palette ;
 else dev -> palette = mem_mono_w_b_palette ;
 }