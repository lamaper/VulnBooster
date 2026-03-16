bool agg_item_set_converter ( DTCollation & coll , const char * fname , Item * * args , uint nargs , uint flags , int item_sep ) {
 Item * * arg , * safe_args [ 2 ] = {
 NULL , NULL }
 ;
 if ( nargs >= 2 && nargs <= 3 ) {
 safe_args [ 0 ] = args [ 0 ] ;
 safe_args [ 1 ] = args [ item_sep ] ;
 }
 THD * thd = current_thd ;
 bool res = FALSE ;
 uint i ;
 Query_arena backup ;
 Query_arena * arena = thd -> stmt_arena -> is_stmt_prepare ( ) ? thd -> activate_stmt_arena_if_needed ( & backup ) : NULL ;
 for ( i = 0 , arg = args ;
 i < nargs ;
 i ++ , arg += item_sep ) {
 Item * conv ;
 uint32 dummy_offset ;
 if ( ! String : : needs_conversion ( 1 , ( * arg ) -> collation . collation , coll . collation , & dummy_offset ) ) continue ;
 if ( ( * arg ) -> collation . derivation == DERIVATION_NUMERIC && ( * arg ) -> collation . repertoire == MY_REPERTOIRE_ASCII && ! ( ( * arg ) -> collation . collation -> state & MY_CS_NONASCII ) && ! ( coll . collation -> state & MY_CS_NONASCII ) ) continue ;
 if ( ! ( conv = ( * arg ) -> safe_charset_converter ( coll . collation ) ) && ( ( * arg ) -> collation . repertoire == MY_REPERTOIRE_ASCII ) ) conv = new Item_func_conv_charset ( * arg , coll . collation , 1 ) ;
 if ( ! conv ) {
 if ( nargs >= 2 && nargs <= 3 ) {
 args [ 0 ] = safe_args [ 0 ] ;
 args [ item_sep ] = safe_args [ 1 ] ;
 }
 my_coll_agg_error ( args , nargs , fname , item_sep ) ;
 res = TRUE ;
 break ;
 }
 if ( ( * arg ) -> type ( ) == Item : : FIELD_ITEM ) ( ( Item_field * ) ( * arg ) ) -> no_const_subst = 1 ;
 if ( thd -> stmt_arena -> is_stmt_prepare ( ) ) * arg = conv ;
 else thd -> change_item_tree ( arg , conv ) ;
 if ( conv -> fix_fields ( thd , arg ) ) {
 res = TRUE ;
 break ;
 }
 }
 if ( arena ) thd -> restore_active_arena ( arena , & backup ) ;
 return res ;
 }