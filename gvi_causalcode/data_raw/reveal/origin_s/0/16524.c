void resolve_const_item ( THD * thd , Item * * ref , Item * comp_item ) {
 Item * item = * ref ;
 Item * new_item = NULL ;
 if ( item -> basic_const_item ( ) ) return ;
 Item_result res_type = item_cmp_type ( comp_item -> cmp_type ( ) , item -> cmp_type ( ) ) ;
 char * name = item -> name ;
 switch ( res_type ) {
 case TIME_RESULT : {
 bool is_null ;
 Item * * ref_copy = ref ;
 get_datetime_value ( thd , & ref_copy , & new_item , comp_item , & is_null ) ;
 if ( is_null ) new_item = new Item_null ( name ) ;
 break ;
 }
 case STRING_RESULT : {
 char buff [ MAX_FIELD_WIDTH ] ;
 String tmp ( buff , sizeof ( buff ) , & my_charset_bin ) , * result ;
 result = item -> val_str ( & tmp ) ;
 if ( item -> null_value ) new_item = new Item_null ( name ) ;
 else {
 uint length = result -> length ( ) ;
 char * tmp_str = sql_strmake ( result -> ptr ( ) , length ) ;
 new_item = new Item_string ( name , tmp_str , length , result -> charset ( ) ) ;
 }
 break ;
 }
 case INT_RESULT : {
 longlong result = item -> val_int ( ) ;
 uint length = item -> max_length ;
 bool null_value = item -> null_value ;
 new_item = ( null_value ? ( Item * ) new Item_null ( name ) : ( Item * ) new Item_int ( name , result , length ) ) ;
 break ;
 }
 case ROW_RESULT : if ( item -> type ( ) == Item : : ROW_ITEM && comp_item -> type ( ) == Item : : ROW_ITEM ) {
 Item_row * item_row = ( Item_row * ) item ;
 Item_row * comp_item_row = ( Item_row * ) comp_item ;
 uint col ;
 new_item = 0 ;
 DBUG_ASSERT ( item -> result_type ( ) == comp_item -> result_type ( ) ) ;
 DBUG_ASSERT ( item_row -> cols ( ) == comp_item_row -> cols ( ) ) ;
 col = item_row -> cols ( ) ;
 while ( col -- > 0 ) resolve_const_item ( thd , item_row -> addr ( col ) , comp_item_row -> element_index ( col ) ) ;
 break ;
 }
 case REAL_RESULT : {
 double result = item -> val_real ( ) ;
 uint length = item -> max_length , decimals = item -> decimals ;
 bool null_value = item -> null_value ;
 new_item = ( null_value ? ( Item * ) new Item_null ( name ) : ( Item * ) new Item_float ( name , result , decimals , length ) ) ;
 break ;
 }
 case DECIMAL_RESULT : {
 my_decimal decimal_value ;
 my_decimal * result = item -> val_decimal ( & decimal_value ) ;
 uint length = item -> max_length , decimals = item -> decimals ;
 bool null_value = item -> null_value ;
 new_item = ( null_value ? ( Item * ) new Item_null ( name ) : ( Item * ) new Item_decimal ( name , result , length , decimals ) ) ;
 break ;
 }
 case IMPOSSIBLE_RESULT : DBUG_ASSERT ( 0 ) ;
 break ;
 }
 if ( new_item ) thd -> change_item_tree ( ref , new_item ) ;
 }