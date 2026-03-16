static void __attribute ( ( noinline ) ) print_statistics ( hp_timing_t * rtld_total_timep ) {

 char * cp ;
 char * wp ;
 if ( HP_SMALL_TIMING_AVAIL ) {
 HP_TIMING_PRINT ( buf , sizeof ( buf ) , * rtld_total_timep ) ;
 _dl_debug_printf ( "\nruntime linker statistics:\n" " total startup time in dynamic loader: %s\n" , buf ) ;
 char pbuf [ 30 ] ;
 HP_TIMING_PRINT ( buf , sizeof ( buf ) , relocate_time ) ;
 cp = _itoa ( ( 1000ULL * relocate_time ) / * rtld_total_timep , pbuf + sizeof ( pbuf ) , 10 , 0 ) ;
 wp = pbuf ;
 switch ( pbuf + sizeof ( pbuf ) - cp ) {
 case 3 : * wp ++ = * cp ++ ;
 case 2 : * wp ++ = * cp ++ ;
 case 1 : * wp ++ = '.' ;
 * wp ++ = * cp ++ ;
 }
 * wp = '\0' ;
 _dl_debug_printf ( "\ time needed for relocation: %s (%s%%)\n" , buf , pbuf ) ;
 }

 for ( Lmid_t ns = 0 ;
 ns < GL ( dl_nns ) ;
 ++ ns ) {
 if ( GL ( dl_ns ) [ ns ] . _ns_loaded == NULL ) continue ;
 struct r_scope_elem * scope = & GL ( dl_ns ) [ ns ] . _ns_loaded -> l_searchlist ;
 for ( unsigned int i = 0 ;
 i < scope -> r_nlist ;
 i ++ ) {
 struct link_map * l = scope -> r_list [ i ] ;
 if ( l -> l_addr != 0 && l -> l_info [ VERSYMIDX ( DT_RELCOUNT ) ] ) num_relative_relocations += l -> l_info [ VERSYMIDX ( DT_RELCOUNT ) ] -> d_un . d_val ;

 }
 }
 _dl_debug_printf ( " number of relocations: %lu\n" " number of relocations from cache: %lu\n" " number of relative relocations: %lu\n" , GL ( dl_num_relocations ) , GL ( dl_num_cache_relocations ) , num_relative_relocations ) ;

 char pbuf [ 30 ] ;
 HP_TIMING_PRINT ( buf , sizeof ( buf ) , load_time ) ;
 cp = _itoa ( ( 1000ULL * load_time ) / * rtld_total_timep , pbuf + sizeof ( pbuf ) , 10 , 0 ) ;
 wp = pbuf ;
 switch ( pbuf + sizeof ( pbuf ) - cp ) {
 case 3 : * wp ++ = * cp ++ ;
 case 2 : * wp ++ = * cp ++ ;
 case 1 : * wp ++ = '.' ;
 * wp ++ = * cp ++ ;
 }
 * wp = '\0' ;
 _dl_debug_printf ( "\ time needed to load objects: %s (%s%%)\n" , buf , pbuf ) ;
 }
