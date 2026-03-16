static void free_picture_tables ( Picture * pic ) {
 int i ;
 av_buffer_unref ( & pic -> mb_var_buf ) ;
 av_buffer_unref ( & pic -> mc_mb_var_buf ) ;
 av_buffer_unref ( & pic -> mb_mean_buf ) ;
 av_buffer_unref ( & pic -> mbskip_table_buf ) ;
 av_buffer_unref ( & pic -> qscale_table_buf ) ;
 av_buffer_unref ( & pic -> mb_type_buf ) ;
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 av_buffer_unref ( & pic -> motion_val_buf [ i ] ) ;
 av_buffer_unref ( & pic -> ref_index_buf [ i ] ) ;
 }
 }