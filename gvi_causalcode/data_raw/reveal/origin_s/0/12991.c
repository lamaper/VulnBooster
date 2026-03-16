static void restore_fix_stack ( i_ctx_t * i_ctx_p , ref_stack_t * pstack , const alloc_save_t * asave , bool is_estack ) {
 ref_stack_enum_t rsenum ;
 ref_stack_enum_begin ( & rsenum , pstack ) ;
 do {
 ref * stkp = rsenum . ptr ;
 uint size = rsenum . size ;
 for ( ;
 size ;
 stkp ++ , size -- ) {
 r_clear_attrs ( stkp , l_new ) ;
 if ( is_estack ) {
 ref ofile ;
 ref_assign ( & ofile , stkp ) ;
 switch ( r_type ( stkp ) ) {
 case t_string : if ( r_size ( stkp ) == 0 && alloc_is_since_save ( stkp -> value . bytes , asave ) ) {
 make_empty_const_string ( stkp , avm_foreign ) ;
 break ;
 }
 continue ;
 case t_file : if ( alloc_is_since_save ( stkp -> value . pfile , asave ) ) {
 make_invalid_file ( i_ctx_p , stkp ) ;
 break ;
 }
 continue ;
 default : continue ;
 }
 r_copy_attrs ( stkp , a_all | a_executable , & ofile ) ;
 }
 }
 }
 while ( ref_stack_enum_next ( & rsenum ) ) ;
 }