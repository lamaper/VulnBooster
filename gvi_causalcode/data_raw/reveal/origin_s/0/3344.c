static void reset_coders ( MSS3Context * ctx , int quality ) {
 int i , j ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) {
 ctx -> btype [ i ] . last_type = SKIP_BLOCK ;
 for ( j = 0 ;
 j < 5 ;
 j ++ ) model_reset ( & ctx -> btype [ i ] . bt_model [ j ] ) ;
 ctx -> fill_coder [ i ] . fill_val = 0 ;
 model_reset ( & ctx -> fill_coder [ i ] . coef_model ) ;
 model256_reset ( & ctx -> image_coder [ i ] . esc_model ) ;
 model256_reset ( & ctx -> image_coder [ i ] . vec_entry_model ) ;
 model_reset ( & ctx -> image_coder [ i ] . vec_size_model ) ;
 for ( j = 0 ;
 j < 125 ;
 j ++ ) model_reset ( & ctx -> image_coder [ i ] . vq_model [ j ] ) ;
 if ( ctx -> dct_coder [ i ] . quality != quality ) {
 ctx -> dct_coder [ i ] . quality = quality ;
 ff_mss34_gen_quant_mat ( ctx -> dct_coder [ i ] . qmat , quality , ! i ) ;
 }
 memset ( ctx -> dct_coder [ i ] . prev_dc , 0 , sizeof ( * ctx -> dct_coder [ i ] . prev_dc ) * ctx -> dct_coder [ i ] . prev_dc_stride * ctx -> dct_coder [ i ] . prev_dc_height ) ;
 model_reset ( & ctx -> dct_coder [ i ] . dc_model ) ;
 model2_reset ( & ctx -> dct_coder [ i ] . sign_model ) ;
 model256_reset ( & ctx -> dct_coder [ i ] . ac_model ) ;
 if ( ctx -> haar_coder [ i ] . quality != quality ) {
 ctx -> haar_coder [ i ] . quality = quality ;
 ctx -> haar_coder [ i ] . scale = 17 - 7 * quality / 50 ;
 }
 model_reset ( & ctx -> haar_coder [ i ] . coef_hi_model ) ;
 model256_reset ( & ctx -> haar_coder [ i ] . coef_model ) ;
 }
 }