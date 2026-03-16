IN_PROC_BROWSER_TEST_F ( SingleClientSessionsSyncTest , ResponseCodeIsPreserved ) {
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
 EXPECT_EQ ( 200 , it3 -> http_status_code ( ) ) ;
 ++ found_navigations ;
 }
 }
 }
 ASSERT_EQ ( 1 , found_navigations ) ;
 }