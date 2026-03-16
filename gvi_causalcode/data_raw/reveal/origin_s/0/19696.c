int open_grant_tables ( THD * thd , TABLE_LIST * tables ) {
 DBUG_ENTER ( "open_grant_tables" ) ;
 if ( ! initialized ) {
 my_error ( ER_OPTION_PREVENTS_STATEMENT , MYF ( 0 ) , "--skip-grant-tables" ) ;
 DBUG_RETURN ( - 1 ) ;
 }
 bzero ( ( char * ) tables , GRANT_TABLES * sizeof ( * tables ) ) ;
 tables -> alias = tables -> table_name = ( char * ) "user" ;
 ( tables + 1 ) -> alias = ( tables + 1 ) -> table_name = ( char * ) "db" ;
 ( tables + 2 ) -> alias = ( tables + 2 ) -> table_name = ( char * ) "tables_priv" ;
 ( tables + 3 ) -> alias = ( tables + 3 ) -> table_name = ( char * ) "columns_priv" ;
 ( tables + 4 ) -> alias = ( tables + 4 ) -> table_name = ( char * ) "procs_priv" ;
 tables -> next_local = tables -> next_global = tables + 1 ;
 ( tables + 1 ) -> next_local = ( tables + 1 ) -> next_global = tables + 2 ;
 ( tables + 2 ) -> next_local = ( tables + 2 ) -> next_global = tables + 3 ;
 ( tables + 3 ) -> next_local = ( tables + 3 ) -> next_global = tables + 4 ;
 tables -> lock_type = ( tables + 1 ) -> lock_type = ( tables + 2 ) -> lock_type = ( tables + 3 ) -> lock_type = ( tables + 4 ) -> lock_type = TL_WRITE ;
 tables -> db = ( tables + 1 ) -> db = ( tables + 2 ) -> db = ( tables + 3 ) -> db = ( tables + 4 ) -> db = ( char * ) "mysql" ;

 tables [ 0 ] . updating = tables [ 1 ] . updating = tables [ 2 ] . updating = tables [ 3 ] . updating = tables [ 4 ] . updating = 1 ;
 if ( ! ( thd -> spcont || rpl_filter -> tables_ok ( 0 , tables ) ) ) DBUG_RETURN ( 1 ) ;
 tables [ 0 ] . updating = tables [ 1 ] . updating = tables [ 2 ] . updating = tables [ 3 ] . updating = tables [ 4 ] . updating = 0 ;
 ;
 }

 close_thread_tables ( thd ) ;
 DBUG_RETURN ( - 1 ) ;
 }
 DBUG_RETURN ( 0 ) ;
 }