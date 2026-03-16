TEST_F ( SyncBookmarkDataTypeControllerTest , StartBookmarkModelNotReady ) {
 CreateBookmarkModel ( DONT_LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 SetAssociateExpectations ( ) ;
 EXPECT_CALL ( start_callback_ , Run ( DataTypeController : : OK , _ , _ ) ) ;
 bookmark_dtc_ -> LoadModels ( base : : Bind ( & ModelLoadCallbackMock : : Run , base : : Unretained ( & model_load_callback_ ) ) ) ;
 EXPECT_EQ ( DataTypeController : : MODEL_STARTING , bookmark_dtc_ -> state ( ) ) ;
 TestingPrefServiceSimple prefs ;
 bookmark_model_ -> Load ( & prefs , base : : FilePath ( ) , base : : ThreadTaskRunnerHandle : : Get ( ) , base : : ThreadTaskRunnerHandle : : Get ( ) ) ;
 bookmarks : : test : : WaitForBookmarkModelToLoad ( bookmark_model_ . get ( ) ) ;
 EXPECT_EQ ( DataTypeController : : MODEL_LOADED , bookmark_dtc_ -> state ( ) ) ;
 bookmark_dtc_ -> StartAssociating ( base : : Bind ( & StartCallbackMock : : Run , base : : Unretained ( & start_callback_ ) ) ) ;
 base : : MessageLoop : : current ( ) -> RunUntilIdle ( ) ;
 EXPECT_EQ ( DataTypeController : : RUNNING , bookmark_dtc_ -> state ( ) ) ;
 }