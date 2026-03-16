TEST_F ( SyncBookmarkDataTypeControllerTest , StartBusy ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 EXPECT_CALL ( * history_service_ . get ( ) , BackendLoaded ( ) ) . WillRepeatedly ( Return ( false ) ) ;
 EXPECT_CALL ( model_load_callback_ , Run ( _ , _ ) ) ;
 bookmark_dtc_ -> LoadModels ( base : : Bind ( & ModelLoadCallbackMock : : Run , base : : Unretained ( & model_load_callback_ ) ) ) ;
 bookmark_dtc_ -> LoadModels ( base : : Bind ( & ModelLoadCallbackMock : : Run , base : : Unretained ( & model_load_callback_ ) ) ) ;
 }