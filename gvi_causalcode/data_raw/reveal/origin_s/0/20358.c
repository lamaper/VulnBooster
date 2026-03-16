static int write_skip ( const VP9_COMMON * cm , const MACROBLOCKD * xd , int segment_id , const MODE_INFO * mi , vp9_writer * w ) {
 if ( vp9_segfeature_active ( & cm -> seg , segment_id , SEG_LVL_SKIP ) ) {
 return 1 ;
 }
 else {
 const int skip = mi -> mbmi . skip ;
 vp9_write ( w , skip , vp9_get_skip_prob ( cm , xd ) ) ;
 return skip ;
 }
 }