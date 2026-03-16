static bool update_schema_privilege ( THD * thd , TABLE * table , char * buff , const char * db , const char * t_name , const char * column , uint col_length , const char * priv , uint priv_length , const char * is_grantable ) {
 int i = 2 ;
 CHARSET_INFO * cs = system_charset_info ;
 restore_record ( table , s -> default_values ) ;
 table -> field [ 0 ] -> store ( buff , ( uint ) strlen ( buff ) , cs ) ;
 if ( db ) table -> field [ i ++ ] -> store ( db , ( uint ) strlen ( db ) , cs ) ;
 if ( t_name ) table -> field [ i ++ ] -> store ( t_name , ( uint ) strlen ( t_name ) , cs ) ;
 if ( column ) table -> field [ i ++ ] -> store ( column , col_length , cs ) ;
 table -> field [ i ++ ] -> store ( priv , priv_length , cs ) ;
 table -> field [ i ] -> store ( is_grantable , strlen ( is_grantable ) , cs ) ;
 return schema_table_store_record ( thd , table ) ;
 }