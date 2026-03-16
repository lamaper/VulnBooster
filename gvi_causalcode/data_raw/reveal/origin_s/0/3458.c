static void test_priorities ( int npriorities ) {
 char buf [ 32 ] ;
 struct test_pri_event one , two ;
 struct timeval tv ;
 evutil_snprintf ( buf , sizeof ( buf ) , "Testing Priorities %d: " , npriorities ) ;
 setup_test ( buf ) ;
 event_base_priority_init ( global_base , npriorities ) ;
 memset ( & one , 0 , sizeof ( one ) ) ;
 memset ( & two , 0 , sizeof ( two ) ) ;
 timeout_set ( & one . ev , test_priorities_cb , & one ) ;
 if ( event_priority_set ( & one . ev , 0 ) == - 1 ) {
 fprintf ( stderr , "%s: failed to set priority" , __func__ ) ;
 exit ( 1 ) ;
 }
 timeout_set ( & two . ev , test_priorities_cb , & two ) ;
 if ( event_priority_set ( & two . ev , npriorities - 1 ) == - 1 ) {
 fprintf ( stderr , "%s: failed to set priority" , __func__ ) ;
 exit ( 1 ) ;
 }
 evutil_timerclear ( & tv ) ;
 if ( event_add ( & one . ev , & tv ) == - 1 ) exit ( 1 ) ;
 if ( event_add ( & two . ev , & tv ) == - 1 ) exit ( 1 ) ;
 event_dispatch ( ) ;
 event_del ( & one . ev ) ;
 event_del ( & two . ev ) ;
 if ( npriorities == 1 ) {
 if ( one . count == 3 && two . count == 3 ) test_ok = 1 ;
 }
 else if ( npriorities == 2 ) {
 if ( one . count == 3 && two . count == 1 ) test_ok = 1 ;
 }
 else {
 if ( one . count == 3 && two . count == 0 ) test_ok = 1 ;
 }
 cleanup_test ( ) ;
 }