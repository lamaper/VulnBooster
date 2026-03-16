void free_grant_table ( GRANT_TABLE * grant_table ) {
 hash_free ( & grant_table -> hash_columns ) ;
 }