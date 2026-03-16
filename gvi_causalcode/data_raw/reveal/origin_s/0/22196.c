my_bool mi_test_if_sort_rep ( MI_INFO * info , ha_rows rows , ulonglong key_map , my_bool force ) {
 MYISAM_SHARE * share = info -> s ;
 MI_KEYDEF * key = share -> keyinfo ;
 uint i ;
 if ( ! mi_is_any_key_active ( key_map ) ) return FALSE ;
 for ( i = 0 ;
 i < share -> base . keys ;
 i ++ , key ++ ) {
 if ( ! force && mi_too_big_key_for_sort ( key , rows ) ) return FALSE ;
 }
 return TRUE ;
 }