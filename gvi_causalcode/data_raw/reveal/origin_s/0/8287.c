TEST_F ( SyncBookmarkDataTypeControllerTest , StartHistoryServiceNotReady ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 EXPECT_CALL ( * history_service_ . get ( ) , BackendLoaded ( ) ) . WillRepeatedly ( Return ( false ) ) ;
 bookmark_dtc_ -> LoadModels ( base : : Bind ( & ModelLoadCallbackMock : : Run , base : : Unretained ( & model_load_callback_ ) ) ) ;
 EXPECT_EQ ( DataTypeController : : MODEL_STARTING , bookmark_dtc_ -> state ( ) ) ;
 testing : : Mock : : VerifyAndClearExpectations ( history_service_ . get ( ) ) ;
 EXPECT_CALL ( * history_service_ . get ( ) , BackendLoaded ( ) ) . WillRepeatedly ( Return ( true ) ) ;
 NotifyHistoryServiceLoaded ( ) ;
 EXPECT_EQ ( DataTypeController : : MODEL_LOADED , bookmark_dtc_ -> state ( ) ) ;
 }