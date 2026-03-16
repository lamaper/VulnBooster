static Item * * resolve_ref_in_select_and_group ( THD * thd , Item_ident * ref , SELECT_LEX * select ) {
 Item * * group_by_ref = NULL ;
 Item * * select_ref = NULL ;
 ORDER * group_list = select -> group_list . first ;
 bool ambiguous_fields = FALSE ;
 uint counter ;
 enum_resolution_type resolution ;
 if ( ! ( select_ref = find_item_in_list ( ref , * ( select -> get_item_list ( ) ) , & counter , REPORT_EXCEPT_NOT_FOUND , & resolution ) ) ) return NULL ;
 if ( resolution == RESOLVED_AGAINST_ALIAS ) ref -> alias_name_used = TRUE ;
 if ( select -> having_fix_field && ! ref -> with_sum_func && group_list ) {
 group_by_ref = find_field_in_group_list ( ref , group_list ) ;
 if ( group_by_ref && ( select_ref != not_found_item ) && ! ( ( * group_by_ref ) -> eq ( * select_ref , 0 ) ) ) {
 ambiguous_fields = TRUE ;
 push_warning_printf ( thd , MYSQL_ERROR : : WARN_LEVEL_WARN , ER_NON_UNIQ_ERROR , ER ( ER_NON_UNIQ_ERROR ) , ref -> full_name ( ) , current_thd -> where ) ;
 }
 }
 if ( thd -> variables . sql_mode & MODE_ONLY_FULL_GROUP_BY && select -> having_fix_field && select_ref != not_found_item && ! group_by_ref ) {
 my_error ( ER_NON_GROUPING_FIELD_USED , MYF ( 0 ) , ref -> name , "HAVING" ) ;
 return NULL ;
 }
 if ( select_ref != not_found_item || group_by_ref ) {
 if ( select_ref != not_found_item && ! ambiguous_fields ) {
 DBUG_ASSERT ( * select_ref != 0 ) ;
 if ( ! select -> ref_pointer_array [ counter ] ) {
 my_error ( ER_ILLEGAL_REFERENCE , MYF ( 0 ) , ref -> name , "forward reference in item list" ) ;
 return NULL ;
 }
 DBUG_ASSERT ( ( * select_ref ) -> fixed ) ;
 return ( select -> ref_pointer_array + counter ) ;
 }
 if ( group_by_ref ) return group_by_ref ;
 DBUG_ASSERT ( FALSE ) ;
 return NULL ;
 }
 return ( Item * * ) not_found_item ;
 }