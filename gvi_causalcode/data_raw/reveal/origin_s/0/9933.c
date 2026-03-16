static char * _get_user_from_associd ( mysql_conn_t * mysql_conn , char * cluster , uint32_t associd ) {
 char * user = NULL ;
 char * query = NULL ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 query = xstrdup_printf ( "select user from \"%s_%s\" where id_assoc=%u" , cluster , assoc_table , associd ) ;
 debug4 ( "%d(%s:%d) query\n%s" , mysql_conn -> conn , THIS_FILE , __LINE__ , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 return NULL ;
 }
 xfree ( query ) ;
 if ( ( row = mysql_fetch_row ( result ) ) && row [ 0 ] [ 0 ] ) user = xstrdup ( row [ 0 ] ) ;
 mysql_free_result ( result ) ;
 return user ;
 }