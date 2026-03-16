static int _setup_cluster_cond_limits ( slurmdb_cluster_cond_t * cluster_cond , char * * extra ) {
 int set = 0 ;
 ListIterator itr = NULL ;
 char * object = NULL ;
 if ( ! cluster_cond ) return 0 ;
 if ( cluster_cond -> with_deleted ) xstrcat ( * extra , " where (deleted=0 || deleted=1)" ) ;
 else xstrcat ( * extra , " where deleted=0" ) ;
 if ( cluster_cond -> cluster_list && list_count ( cluster_cond -> cluster_list ) ) {
 set = 0 ;
 xstrcat ( * extra , " && (" ) ;
 itr = list_iterator_create ( cluster_cond -> cluster_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( * extra , " || " ) ;
 xstrfmtcat ( * extra , "name='%s'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( * extra , ")" ) ;
 }
 if ( cluster_cond -> federation_list && list_count ( cluster_cond -> federation_list ) ) {
 set = 0 ;
 xstrcat ( * extra , " && (" ) ;
 itr = list_iterator_create ( cluster_cond -> federation_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( * extra , " || " ) ;
 xstrfmtcat ( * extra , "federation='%s'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( * extra , ")" ) ;
 }
 if ( cluster_cond -> plugin_id_select_list && list_count ( cluster_cond -> plugin_id_select_list ) ) {
 set = 0 ;
 xstrcat ( * extra , " && (" ) ;
 itr = list_iterator_create ( cluster_cond -> plugin_id_select_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( * extra , " || " ) ;
 xstrfmtcat ( * extra , "plugin_id_select='%s'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( * extra , ")" ) ;
 }
 if ( cluster_cond -> rpc_version_list && list_count ( cluster_cond -> rpc_version_list ) ) {
 set = 0 ;
 xstrcat ( * extra , " && (" ) ;
 itr = list_iterator_create ( cluster_cond -> rpc_version_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( * extra , " || " ) ;
 xstrfmtcat ( * extra , "rpc_version='%s'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( * extra , ")" ) ;
 }
 if ( cluster_cond -> classification ) {
 xstrfmtcat ( * extra , " && (classification & %u)" , cluster_cond -> classification ) ;
 }
 if ( cluster_cond -> flags != NO_VAL ) {
 xstrfmtcat ( * extra , " && (flags & %u)" , cluster_cond -> flags ) ;
 }
 return set ;
 }