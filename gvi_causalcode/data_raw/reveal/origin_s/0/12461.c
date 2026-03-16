void vp9_find_mv_refs ( const VP9_COMMON * cm , const MACROBLOCKD * xd , const TileInfo * const tile , MODE_INFO * mi , MV_REFERENCE_FRAME ref_frame , int_mv * mv_ref_list , int mi_row , int mi_col ) {
 find_mv_refs_idx ( cm , xd , tile , mi , ref_frame , mv_ref_list , - 1 , mi_row , mi_col ) ;
 }