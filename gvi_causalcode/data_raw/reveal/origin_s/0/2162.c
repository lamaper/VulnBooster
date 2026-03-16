static int _setup_resv_cond_limits ( slurmdb_reservation_cond_t * resv_cond , char * * extra ) {
 int set = 0 ;
 ListIterator itr = NULL ;
 char * object = NULL ;
 char * prefix = "t1" ;
 time_t now = time ( NULL ) ;
 if ( ! resv_cond ) return 0 ;
 if ( resv_cond -> id_list && list_count ( resv_cond -> id_list ) ) {
 set = 0 ;
 if ( * extra ) xstrcat ( * extra , " && (" ) ;
 else xstrcat ( * extra , " where (" ) ;
 itr = list_iterator_create ( resv_cond -> id_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( * extra , " || " ) ;
 xstrfmtcat ( * extra , "%s.id_resv=%s" , prefix , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( * extra , ")" ) ;
 }
 if ( resv_cond -> name_list && list_count ( resv_cond -> name_list ) ) {
 set = 0 ;
 if ( * extra ) xstrcat ( * extra , " && (" ) ;
 else xstrcat ( * extra , " where (" ) ;
 itr = list_iterator_create ( resv_cond -> name_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( * extra , " || " ) ;
 xstrfmtcat ( * extra , "%s.resv_name='%s'" , prefix , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( * extra , ")" ) ;
 }
 if ( resv_cond -> time_start ) {
 if ( ! resv_cond -> time_end ) resv_cond -> time_end = now ;
 if ( * extra ) xstrcat ( * extra , " && (" ) ;
 else xstrcat ( * extra , " where (" ) ;
 xstrfmtcat ( * extra , "(t1.time_start < %ld " "&& (t1.time_end >= %ld || t1.time_end = 0)))" , resv_cond -> time_end , resv_cond -> time_start ) ;
 }
 else if ( resv_cond -> time_end ) {
 if ( * extra ) xstrcat ( * extra , " && (" ) ;
 else xstrcat ( * extra , " where (" ) ;
 xstrfmtcat ( * extra , "(t1.time_start < %ld))" , resv_cond -> time_end ) ;
 }
 return set ;
 }