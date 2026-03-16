static REFERENCE_MODE read_block_reference_mode ( VP9_COMMON * cm , const MACROBLOCKD * xd , vp9_reader * r ) {
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) {
 const int ctx = vp9_get_reference_mode_context ( cm , xd ) ;
 const REFERENCE_MODE mode = ( REFERENCE_MODE ) vp9_read ( r , cm -> fc . comp_inter_prob [ ctx ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ cm -> counts . comp_inter [ ctx ] [ mode ] ;
 return mode ;
 }
 else {
 return cm -> reference_mode ;
 }
 }