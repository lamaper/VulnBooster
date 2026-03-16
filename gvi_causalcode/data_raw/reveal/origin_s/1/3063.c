IN_PROC_BROWSER_TEST_F ( SingleClientSessionsSyncTest , TimestampMatchesHistory ) {
 ASSERT_TRUE ( SetupSync ( ) ) << "SetupSync() failed." ;
 ASSERT_TRUE ( CheckInitialState ( 0 ) ) ;
 const GURL url ( "about:version" ) ;
 ScopedWindowMap windows ;
 ASSERT_TRUE ( OpenTabAndGetLocalWindows ( 0 , url , windows . GetMutable ( ) ) ) ;
 int found_navigations = 0 ;
 for ( SessionWindowMap : : const_iterator it = windows . Get ( ) -> begin ( ) ;
 it != windows . Get ( ) -> end ( ) ;
 ++ it ) {
 for ( std : : vector < sessions : : SessionTab * > : : const_iterator it2 = it -> second -> tabs . begin ( ) ;
 it2 != it -> second -> tabs . end ( ) ;
 ++ it2 ) {
 for ( std : : vector < sessions : : SerializedNavigationEntry > : : const_iterator it3 = ( * it2 ) -> navigations . begin ( ) ;
 it3 != ( * it2 ) -> navigations . end ( ) ;
 ++ it3 ) {
 const base : : Time timestamp = it3 -> timestamp ( ) ;
 history : : URLRow virtual_row ;
 ASSERT_TRUE ( GetUrlFromClient ( 0 , it3 -> virtual_url ( ) , & virtual_row ) ) ;
 const base : : Time history_timestamp = virtual_row . last_visit ( ) ;
 ASSERT_EQ ( timestamp , history_timestamp ) ;
 ++ found_navigations ;
 }
 }
 }
 ASSERT_EQ ( 1 , found_navigations ) ;
 }