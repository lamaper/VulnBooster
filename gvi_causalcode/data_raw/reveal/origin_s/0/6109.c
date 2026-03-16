TEST_F ( SyncBookmarkDataTypeControllerTest , StartAborted ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 EXPECT_CALL ( * history_service_ . get ( ) , BackendLoaded ( ) ) . WillRepeatedly ( Return ( false ) ) ;
 bookmark_dtc_ -> LoadModels ( base : : Bind ( & ModelLoadCallbackMock : : Run , base : : Unretained ( & model_load_callback_ ) ) ) ;
 bookmark_dtc_ -> Stop ( ) ;
 EXPECT_EQ ( DataTypeController : : NOT_RUNNING , bookmark_dtc_ -> state ( ) ) ;
 }