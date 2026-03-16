hb_bool_t _hb_graphite2_shape ( hb_shape_plan_t * shape_plan , hb_font_t * font , hb_buffer_t * buffer , const hb_feature_t * features , unsigned int num_features ) {
 hb_face_t * face = font -> face ;
 gr_face * grface = HB_SHAPER_DATA_GET ( face ) -> grface ;
 gr_font * grfont = HB_SHAPER_DATA_GET ( font ) ;
 const char * lang = hb_language_to_string ( hb_buffer_get_language ( buffer ) ) ;
 const char * lang_end = lang ? strchr ( lang , '-' ) : NULL ;
 int lang_len = lang_end ? lang_end - lang : - 1 ;
 gr_feature_val * feats = gr_face_featureval_for_lang ( grface , lang ? hb_tag_from_string ( lang , lang_len ) : 0 ) ;
 for ( unsigned int i = 0 ;
 i < num_features ;
 i ++ ) {
 const gr_feature_ref * fref = gr_face_find_fref ( grface , features [ i ] . tag ) ;
 if ( fref ) gr_fref_set_feature_value ( fref , features [ i ] . value , feats ) ;
 }
 gr_segment * seg = NULL ;
 const gr_slot * is ;
 unsigned int ci = 0 , ic = 0 ;
 float curradvx = 0. , curradvy = 0. ;
 unsigned int scratch_size ;
 hb_buffer_t : : scratch_buffer_t * scratch = buffer -> get_scratch_buffer ( & scratch_size ) ;
 uint32_t * chars = ( uint32_t * ) scratch ;
 for ( unsigned int i = 0 ;
 i < buffer -> len ;
 ++ i ) chars [ i ] = buffer -> info [ i ] . codepoint ;
 hb_tag_t script_tag [ 2 ] ;
 hb_ot_tags_from_script ( hb_buffer_get_script ( buffer ) , & script_tag [ 0 ] , & script_tag [ 1 ] ) ;
 seg = gr_make_seg ( grfont , grface , script_tag [ 1 ] == HB_TAG_NONE ? script_tag [ 0 ] : script_tag [ 1 ] , feats , gr_utf32 , chars , buffer -> len , | ( hb_buffer_get_direction ( buffer ) == HB_DIRECTION_RTL ? 1 : 0 ) ) ;
 if ( unlikely ( ! seg ) ) {
 if ( feats ) gr_featureval_destroy ( feats ) ;
 return false ;
 }
 unsigned int glyph_count = gr_seg_n_slots ( seg ) ;
 if ( unlikely ( ! glyph_count ) ) {
 if ( feats ) gr_featureval_destroy ( feats ) ;
 gr_seg_destroy ( seg ) ;
 buffer -> len = 0 ;
 return true ;
 }
 buffer -> ensure ( glyph_count ) ;
 scratch = buffer -> get_scratch_buffer ( & scratch_size ) ;
 while ( ( DIV_CEIL ( sizeof ( hb_graphite2_cluster_t ) * buffer -> len , sizeof ( * scratch ) ) + DIV_CEIL ( sizeof ( hb_codepoint_t ) * glyph_count , sizeof ( * scratch ) ) ) > scratch_size ) {
 if ( unlikely ( ! buffer -> ensure ( buffer -> allocated * 2 ) ) ) {
 if ( feats ) gr_featureval_destroy ( feats ) ;
 gr_seg_destroy ( seg ) ;
 return false ;
 }
 scratch = buffer -> get_scratch_buffer ( & scratch_size ) ;
 }

 {
 unsigned int _consumed = DIV_CEIL ( ( len ) * sizeof ( Type ) , sizeof ( * scratch ) ) ;
 assert ( _consumed <= scratch_size ) ;
 scratch += _consumed ;
 scratch_size -= _consumed ;
 }
 ALLOCATE_ARRAY ( hb_graphite2_cluster_t , clusters , buffer -> len ) ;
 ALLOCATE_ARRAY ( hb_codepoint_t , gids , glyph_count ) ;

 hb_codepoint_t * pg = gids ;
 clusters [ 0 ] . cluster = buffer -> info [ 0 ] . cluster ;
 for ( is = gr_seg_first_slot ( seg ) , ic = 0 ;
 is ;
 is = gr_slot_next_in_segment ( is ) , ic ++ ) {
 unsigned int before = gr_slot_before ( is ) ;
 unsigned int after = gr_slot_after ( is ) ;
 * pg = gr_slot_gid ( is ) ;
 pg ++ ;
 while ( clusters [ ci ] . base_char > before && ci ) {
 clusters [ ci - 1 ] . num_chars += clusters [ ci ] . num_chars ;
 clusters [ ci - 1 ] . num_glyphs += clusters [ ci ] . num_glyphs ;
 ci -- ;
 }
 if ( gr_slot_can_insert_before ( is ) && clusters [ ci ] . num_chars && before >= clusters [ ci ] . base_char + clusters [ ci ] . num_chars ) {
 hb_graphite2_cluster_t * c = clusters + ci + 1 ;
 c -> base_char = clusters [ ci ] . base_char + clusters [ ci ] . num_chars ;
 c -> cluster = buffer -> info [ c -> base_char ] . cluster ;
 c -> num_chars = before - c -> base_char ;
 c -> base_glyph = ic ;
 c -> num_glyphs = 0 ;
 ci ++ ;
 }
 clusters [ ci ] . num_glyphs ++ ;
 if ( clusters [ ci ] . base_char + clusters [ ci ] . num_chars < after + 1 ) clusters [ ci ] . num_chars = after + 1 - clusters [ ci ] . base_char ;
 }
 ci ++ ;
 for ( unsigned int i = 0 ;
 i < ci ;
 ++ i ) {
 for ( unsigned int j = 0 ;
 j < clusters [ i ] . num_glyphs ;
 ++ j ) {
 hb_glyph_info_t * info = & buffer -> info [ clusters [ i ] . base_glyph + j ] ;
 info -> codepoint = gids [ clusters [ i ] . base_glyph + j ] ;
 info -> cluster = clusters [ i ] . cluster ;
 }
 }
 buffer -> len = glyph_count ;
 if ( ! HB_DIRECTION_IS_BACKWARD ( buffer -> props . direction ) ) {
 hb_glyph_position_t * pPos ;
 for ( pPos = hb_buffer_get_glyph_positions ( buffer , NULL ) , is = gr_seg_first_slot ( seg ) ;
 is ;
 pPos ++ , is = gr_slot_next_in_segment ( is ) ) {
 pPos -> x_offset = gr_slot_origin_X ( is ) - curradvx ;
 pPos -> y_offset = gr_slot_origin_Y ( is ) - curradvy ;
 pPos -> x_advance = gr_slot_advance_X ( is , grface , grfont ) ;
 pPos -> y_advance = gr_slot_advance_Y ( is , grface , grfont ) ;
 curradvx += pPos -> x_advance ;
 curradvy += pPos -> y_advance ;
 }
 pPos [ - 1 ] . x_advance += gr_seg_advance_X ( seg ) - curradvx ;
 }
 else {
 hb_glyph_position_t * pPos = hb_buffer_get_glyph_positions ( buffer , NULL ) + buffer -> len - 1 ;
 const hb_glyph_info_t * info = buffer -> info + buffer -> len - 1 ;
 const hb_glyph_info_t * tinfo ;
 const gr_slot * tis ;
 int currclus = - 1 ;
 float clusx = 0. , clusy = 0. ;
 for ( is = gr_seg_last_slot ( seg ) ;
 is ;
 pPos -- , info -- , is = gr_slot_prev_in_segment ( is ) ) {
 if ( info -> cluster != currclus ) {
 curradvx += clusx ;
 curradvy += clusy ;
 currclus = info -> cluster ;
 clusx = 0. ;
 clusy = 0. ;
 for ( tis = is , tinfo = info ;
 tis && tinfo -> cluster == currclus ;
 tis = gr_slot_prev_in_segment ( tis ) , tinfo -- ) {
 clusx += gr_slot_advance_X ( tis , grface , grfont ) ;
 clusy += gr_slot_advance_Y ( tis , grface , grfont ) ;
 }
 curradvx += clusx ;
 curradvy += clusy ;
 }
 pPos -> x_advance = gr_slot_advance_X ( is , grface , grfont ) ;
 pPos -> y_advance = gr_slot_advance_Y ( is , grface , grfont ) ;
 curradvx -= pPos -> x_advance ;
 curradvy -= pPos -> y_advance ;
 pPos -> x_offset = gr_slot_origin_X ( is ) - curradvx ;
 pPos -> y_offset = gr_slot_origin_Y ( is ) - curradvy ;
 }
 hb_buffer_reverse_clusters ( buffer ) ;
 }
 if ( feats ) gr_featureval_destroy ( feats ) ;
 gr_seg_destroy ( seg ) ;
 return true ;
 }