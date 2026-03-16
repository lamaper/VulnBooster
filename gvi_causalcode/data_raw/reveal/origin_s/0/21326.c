static int mi_drop_all_indexes ( MI_CHECK * param , MI_INFO * info , my_bool force ) {
 MYISAM_SHARE * share = info -> s ;
 MI_STATE_INFO * state = & share -> state ;
 uint i ;
 int error ;
 DBUG_ENTER ( "mi_drop_all_indexes" ) ;
 if ( ! force && ( param -> testflag & T_CREATE_MISSING_KEYS ) ) {
 DBUG_PRINT ( "repair" , ( "creating missing indexes" ) ) ;
 for ( i = 0 ;
 i < share -> base . keys ;
 i ++ ) {
 DBUG_PRINT ( "repair" , ( "index #: %u key_root: 0x%lx active: %d" , i , ( long ) state -> key_root [ i ] , mi_is_key_active ( state -> key_map , i ) ) ) ;
 if ( ( state -> key_root [ i ] != HA_OFFSET_ERROR ) && ! mi_is_key_active ( state -> key_map , i ) ) {
 DBUG_PRINT ( "repair" , ( "nonempty and disabled: recreate all" ) ) ;
 break ;
 }
 }
 if ( i >= share -> base . keys ) {
 DBUG_PRINT ( "repair" , ( "all disabled are empty: create missing" ) ) ;
 error = flush_key_blocks ( share -> key_cache , share -> kfile , FLUSH_FORCE_WRITE ) ;
 goto end ;
 }
 mi_clear_all_keys_active ( state -> key_map ) ;
 DBUG_PRINT ( "repair" , ( "declared all indexes disabled" ) ) ;
 }
 if ( ( error = flush_key_blocks ( share -> key_cache , share -> kfile , FLUSH_IGNORE_CHANGED ) ) ) goto end ;
 for ( i = 0 ;
 i < share -> base . keys ;
 i ++ ) state -> key_root [ i ] = HA_OFFSET_ERROR ;
 for ( i = 0 ;
 i < state -> header . max_block_size_index ;
 i ++ ) state -> key_del [ i ] = HA_OFFSET_ERROR ;
 info -> state -> key_file_length = share -> base . keystart ;
 DBUG_PRINT ( "repair" , ( "dropped all indexes" ) ) ;
 end : DBUG_RETURN ( error ) ;
 }