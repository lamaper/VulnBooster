static void tokenize_b ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , void * arg ) {
 struct tokenize_b_args * const args = arg ;
 VP9_COMP * cpi = args -> cpi ;
 MACROBLOCKD * xd = args -> xd ;
 TOKENEXTRA * * tp = args -> tp ;
 uint8_t token_cache [ 32 * 32 ] ;
 struct macroblock_plane * p = & cpi -> mb . plane [ plane ] ;
 struct macroblockd_plane * pd = & xd -> plane [ plane ] ;
 MB_MODE_INFO * mbmi = & xd -> mi [ 0 ] -> mbmi ;
 int pt ;
 int c ;
 TOKENEXTRA * t = * tp ;
 int eob = p -> eobs [ block ] ;
 const PLANE_TYPE type = pd -> plane_type ;
 const int16_t * qcoeff = BLOCK_OFFSET ( p -> qcoeff , block ) ;
 const int segment_id = mbmi -> segment_id ;
 const int16_t * scan , * nb ;
 const scan_order * so ;
 const int ref = is_inter_block ( mbmi ) ;
 unsigned int ( * const counts ) [ COEFF_CONTEXTS ] [ ENTROPY_TOKENS ] = cpi -> coef_counts [ tx_size ] [ type ] [ ref ] ;
 vp9_prob ( * const coef_probs ) [ COEFF_CONTEXTS ] [ UNCONSTRAINED_NODES ] = cpi -> common . fc . coef_probs [ tx_size ] [ type ] [ ref ] ;
 unsigned int ( * const eob_branch ) [ COEFF_CONTEXTS ] = cpi -> common . counts . eob_branch [ tx_size ] [ type ] [ ref ] ;
 const uint8_t * const band = get_band_translate ( tx_size ) ;
 const int seg_eob = get_tx_eob ( & cpi -> common . seg , segment_id , tx_size ) ;
 int aoff , loff ;
 txfrm_block_to_raster_xy ( plane_bsize , tx_size , block , & aoff , & loff ) ;
 pt = get_entropy_context ( tx_size , pd -> above_context + aoff , pd -> left_context + loff ) ;
 so = get_scan ( xd , tx_size , type , block ) ;
 scan = so -> scan ;
 nb = so -> neighbors ;
 c = 0 ;
 while ( c < eob ) {
 int v = 0 ;
 int skip_eob = 0 ;
 v = qcoeff [ scan [ c ] ] ;
 while ( ! v ) {
 add_token_no_extra ( & t , coef_probs [ band [ c ] ] [ pt ] , ZERO_TOKEN , skip_eob , counts [ band [ c ] ] [ pt ] ) ;
 eob_branch [ band [ c ] ] [ pt ] += ! skip_eob ;
 skip_eob = 1 ;
 token_cache [ scan [ c ] ] = 0 ;
 ++ c ;
 pt = get_coef_context ( nb , token_cache , c ) ;
 v = qcoeff [ scan [ c ] ] ;
 }
 add_token ( & t , coef_probs [ band [ c ] ] [ pt ] , vp9_dct_value_tokens_ptr [ v ] . extra , ( uint8_t ) vp9_dct_value_tokens_ptr [ v ] . token , ( uint8_t ) skip_eob , counts [ band [ c ] ] [ pt ] ) ;
 eob_branch [ band [ c ] ] [ pt ] += ! skip_eob ;
 token_cache [ scan [ c ] ] = vp9_pt_energy_class [ vp9_dct_value_tokens_ptr [ v ] . token ] ;
 ++ c ;
 pt = get_coef_context ( nb , token_cache , c ) ;
 }
 if ( c < seg_eob ) {
 add_token_no_extra ( & t , coef_probs [ band [ c ] ] [ pt ] , EOB_TOKEN , 0 , counts [ band [ c ] ] [ pt ] ) ;
 ++ eob_branch [ band [ c ] ] [ pt ] ;
 }
 * tp = t ;
 vp9_set_contexts ( xd , pd , plane_bsize , tx_size , c > 0 , aoff , loff ) ;
 }