static int libopenjpeg_matches_pix_fmt ( const opj_image_t * img , enum AVPixelFormat pix_fmt ) {
 const AVPixFmtDescriptor * desc = av_pix_fmt_desc_get ( pix_fmt ) ;
 int match = 1 ;
 if ( desc -> nb_components != img -> numcomps ) {
 return 0 ;
 }
 switch ( desc -> nb_components ) {
 case 4 : match = match && desc -> comp [ 3 ] . depth_minus1 + 1 >= img -> comps [ 3 ] . prec && 1 == img -> comps [ 3 ] . dx && 1 == img -> comps [ 3 ] . dy ;
 case 3 : match = match && desc -> comp [ 2 ] . depth_minus1 + 1 >= img -> comps [ 2 ] . prec && 1 << desc -> log2_chroma_w == img -> comps [ 2 ] . dx && 1 << desc -> log2_chroma_h == img -> comps [ 2 ] . dy ;
 case 2 : match = match && desc -> comp [ 1 ] . depth_minus1 + 1 >= img -> comps [ 1 ] . prec && 1 << desc -> log2_chroma_w == img -> comps [ 1 ] . dx && 1 << desc -> log2_chroma_h == img -> comps [ 1 ] . dy ;
 case 1 : match = match && desc -> comp [ 0 ] . depth_minus1 + 1 >= img -> comps [ 0 ] . prec && 1 == img -> comps [ 0 ] . dx && 1 == img -> comps [ 0 ] . dy ;
 default : break ;
 }
 return match ;
 }