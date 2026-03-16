static void test_decode ( struct stream_state * stream , enum TestDecodeFatality fatal , const VpxInterface * codec ) {
 vpx_image_t enc_img , dec_img ;
 if ( stream -> mismatch_seen ) return ;
 if ( strcmp ( codec -> name , "vp8" ) == 0 ) {
 struct vpx_ref_frame ref_enc , ref_dec ;
 int width , height ;
 width = ( stream -> config . cfg . g_w + 15 ) & ~ 15 ;
 height = ( stream -> config . cfg . g_h + 15 ) & ~ 15 ;
 vpx_img_alloc ( & ref_enc . img , VPX_IMG_FMT_I420 , width , height , 1 ) ;
 enc_img = ref_enc . img ;
 vpx_img_alloc ( & ref_dec . img , VPX_IMG_FMT_I420 , width , height , 1 ) ;
 dec_img = ref_dec . img ;
 ref_enc . frame_type = VP8_LAST_FRAME ;
 ref_dec . frame_type = VP8_LAST_FRAME ;
 vpx_codec_control ( & stream -> encoder , VP8_COPY_REFERENCE , & ref_enc ) ;
 vpx_codec_control ( & stream -> decoder , VP8_COPY_REFERENCE , & ref_dec ) ;
 }
 else {
 struct vp9_ref_frame ref_enc , ref_dec ;
 ref_enc . idx = 0 ;
 ref_dec . idx = 0 ;
 vpx_codec_control ( & stream -> encoder , VP9_GET_REFERENCE , & ref_enc ) ;
 enc_img = ref_enc . img ;
 vpx_codec_control ( & stream -> decoder , VP9_GET_REFERENCE , & ref_dec ) ;
 dec_img = ref_dec . img ;

 if ( enc_img . fmt & VPX_IMG_FMT_HIGHBITDEPTH ) {
 vpx_img_alloc ( & enc_img , enc_img . fmt - VPX_IMG_FMT_HIGHBITDEPTH , enc_img . d_w , enc_img . d_h , 16 ) ;
 img_cast_16_to_8 ( & enc_img , & ref_enc . img ) ;
 }
 if ( dec_img . fmt & VPX_IMG_FMT_HIGHBITDEPTH ) {
 vpx_img_alloc ( & dec_img , dec_img . fmt - VPX_IMG_FMT_HIGHBITDEPTH , dec_img . d_w , dec_img . d_h , 16 ) ;
 img_cast_16_to_8 ( & dec_img , & ref_dec . img ) ;
 }
 }

 ctx_exit_on_error ( & stream -> encoder , "Failed to get encoder reference frame" ) ;
 ctx_exit_on_error ( & stream -> decoder , "Failed to get decoder reference frame" ) ;
 if ( ! compare_img ( & enc_img , & dec_img ) ) {
 int y [ 4 ] , u [ 4 ] , v [ 4 ] ;

 find_mismatch_high ( & enc_img , & dec_img , y , u , v ) ;
 }
 else {
 find_mismatch ( & enc_img , & dec_img , y , u , v ) ;
 }


 warn_or_exit_on_error ( & stream -> decoder , fatal == TEST_DECODE_FATAL , "Stream %d: Encode/decode mismatch on frame %d at" " Y[%d, %d] {
%d/%d}
," " U[%d, %d] {
%d/%d}
," " V[%d, %d] {
%d/%d}
" , stream -> index , stream -> frames_out , y [ 0 ] , y [ 1 ] , y [ 2 ] , y [ 3 ] , u [ 0 ] , u [ 1 ] , u [ 2 ] , u [ 3 ] , v [ 0 ] , v [ 1 ] , v [ 2 ] , v [ 3 ] ) ;
 stream -> mismatch_seen = stream -> frames_out ;
 }
 vpx_img_free ( & enc_img ) ;
 vpx_img_free ( & dec_img ) ;
 }