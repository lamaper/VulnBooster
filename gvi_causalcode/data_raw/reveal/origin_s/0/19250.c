static int restore_check_stack ( const i_ctx_t * i_ctx_p , const ref_stack_t * pstack , const alloc_save_t * asave , bool is_estack ) {
 ref_stack_enum_t rsenum ;
 ref_stack_enum_begin ( & rsenum , pstack ) ;
 do {
 const ref * stkp = rsenum . ptr ;
 uint size = rsenum . size ;
 for ( ;
 size ;
 stkp ++ , size -- ) {
 const void * ptr ;
 switch ( r_type ( stkp ) ) {
 case t_array : if ( r_size ( stkp ) == 0 ) {
 continue ;
 }
 ptr = stkp -> value . refs ;
 break ;
 case t_dictionary : ptr = stkp -> value . pdict ;
 break ;
 case t_file : {
 stream * s ;
 if ( is_estack && ( r_has_attr ( stkp , a_executable ) || file_is_invalid ( s , stkp ) ) ) continue ;
 }
 ptr = stkp -> value . pfile ;
 break ;
 case t_name : if ( alloc_name_is_since_save ( ( const gs_memory_t * ) pstack -> memory , stkp , asave ) ) return_error ( gs_error_invalidrestore ) ;
 continue ;
 case t_string : if ( r_size ( stkp ) == 0 && r_has_attr ( stkp , a_executable ) && is_estack ) continue ;
 ptr = stkp -> value . bytes ;
 break ;
 case t_mixedarray : case t_shortarray : if ( r_size ( stkp ) == 0 ) {
 continue ;
 }
 ptr = stkp -> value . packed ;
 break ;
 case t_device : ptr = stkp -> value . pdevice ;
 break ;
 case t_fontID : case t_struct : case t_astruct : ptr = stkp -> value . pstruct ;
 break ;
 case t_save : if ( i_ctx_p -> language_level <= 2 ) continue ;
 ptr = alloc_find_save ( & gs_imemory , stkp -> value . saveid ) ;
 if ( ptr == 0 ) return_error ( gs_error_invalidrestore ) ;
 if ( ptr == asave ) continue ;
 break ;
 default : continue ;
 }
 if ( alloc_is_since_save ( ptr , asave ) ) return_error ( gs_error_invalidrestore ) ;
 }
 }
 while ( ref_stack_enum_next ( & rsenum ) ) ;
 return 0 ;
 }