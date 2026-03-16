static void generate_psnr_packet ( VP9_COMP * cpi ) {
 struct vpx_codec_cx_pkt pkt ;
 int i ;
 PSNR_STATS psnr ;
 calc_psnr ( cpi -> Source , cpi -> common . frame_to_show , & psnr ) ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 pkt . data . psnr . samples [ i ] = psnr . samples [ i ] ;
 pkt . data . psnr . sse [ i ] = psnr . sse [ i ] ;
 pkt . data . psnr . psnr [ i ] = psnr . psnr [ i ] ;
 }
 pkt . kind = VPX_CODEC_PSNR_PKT ;
 if ( is_two_pass_svc ( cpi ) ) cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] . psnr_pkt = pkt . data . psnr ;
 else vpx_codec_pkt_list_add ( cpi -> output_pkt_list , & pkt ) ;
 }