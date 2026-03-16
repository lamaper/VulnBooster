IN_PROC_BROWSER_TEST_F ( SingleClientSessionsSyncTest , MAYBE_Sanity ) {
 ASSERT_TRUE ( SetupSync ( ) ) << "SetupSync() failed." ;
 ASSERT_TRUE ( CheckInitialState ( 0 ) ) ;
 ScopedWindowMap old_windows ;
 ASSERT_TRUE ( OpenTabAndGetLocalWindows ( 0 , GURL ( "http://127.0.0.1/bubba" ) , old_windows . GetMutable ( ) ) ) ;
 ASSERT_TRUE ( AwaitCommitActivityCompletion ( GetSyncService ( ( 0 ) ) ) ) ;
 SyncedSessionVector sessions ;
 ASSERT_FALSE ( GetSessionData ( 0 , & sessions ) ) ;
 ASSERT_EQ ( 0U , sessions . size ( ) ) ;
 ScopedWindowMap new_windows ;
 ASSERT_TRUE ( GetLocalWindows ( 0 , new_windows . GetMutable ( ) ) ) ;
 ASSERT_TRUE ( WindowsMatch ( * old_windows . Get ( ) , * new_windows . Get ( ) ) ) ;
 }