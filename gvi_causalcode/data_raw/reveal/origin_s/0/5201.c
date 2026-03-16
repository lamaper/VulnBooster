extern int as_mysql_get_fed_cluster_id ( mysql_conn_t * mysql_conn , const char * cluster , const char * federation , int last_id , int * ret_id ) {
 int id = 1 ;
 char * query = NULL ;
 MYSQL_ROW row ;
 MYSQL_RES * result = NULL ;
 xassert ( cluster ) ;
 xassert ( federation ) ;
 xassert ( ret_id ) ;
 xstrfmtcat ( query , "SELECT name, fed_id " "FROM %s " "WHERE deleted=0 AND name='%s' AND federation='%s';
" , cluster_table , cluster , federation ) ;
 if ( debug_flags & DEBUG_FLAG_FEDR ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 error ( "no result given for %s" , query ) ;
 return SLURM_ERROR ;
 }
 xfree ( query ) ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 int tmp_id = slurm_atoul ( row [ 1 ] ) ;
 if ( debug_flags & DEBUG_FLAG_FEDR ) info ( "cluster '%s' already part of federation '%s', " "using existing id %d" , cluster , federation , tmp_id ) ;
 mysql_free_result ( result ) ;
 * ret_id = tmp_id ;
 return SLURM_SUCCESS ;
 }
 mysql_free_result ( result ) ;
 xstrfmtcat ( query , "SELECT name, federation, fed_id " "FROM %s " "WHERE name!='%s' AND federation='%s' " "AND fed_id > %d AND deleted=0 ORDER BY fed_id;
" , cluster_table , cluster , federation , last_id ) ;
 if ( debug_flags & DEBUG_FLAG_FEDR ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 error ( "no result given for %s" , query ) ;
 return SLURM_ERROR ;
 }
 xfree ( query ) ;
 if ( last_id >= id ) id = last_id + 1 ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 if ( id != slurm_atoul ( row [ 2 ] ) ) break ;
 id ++ ;
 }
 mysql_free_result ( result ) ;
 if ( id > MAX_FED_CLUSTERS ) {
 error ( "Too many clusters in this federation." ) ;
 errno = ESLURM_FED_CLUSTER_MAX_CNT ;
 return ESLURM_FED_CLUSTER_MAX_CNT ;
 }
 * ret_id = id ;
 return SLURM_SUCCESS ;
 }