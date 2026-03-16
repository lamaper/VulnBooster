static int read_skip ( VP9_COMMON * cm , const MACROBLOCKD * xd , int segment_id , vp9_reader * r ) {
 if ( vp9_segfeature_active ( & cm -> seg , segment_id , SEG_LVL_SKIP ) ) {
 return 1 ;
 }
 else {
 const int ctx = vp9_get_skip_context ( xd ) ;
 const int skip = vp9_read ( r , cm -> fc . skip_probs [ ctx ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ cm -> counts . skip [ ctx ] [ skip ] ;
 return skip ;
 }
 }