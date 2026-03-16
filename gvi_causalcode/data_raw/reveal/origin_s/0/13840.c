TEST_F ( SyncBookmarkDataTypeControllerTest , StartFirstRun ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 SetAssociateExpectations ( ) ;
 EXPECT_CALL ( * model_associator_ , SyncModelHasUserCreatedNodes ( _ ) ) . WillRepeatedly ( DoAll ( SetArgumentPointee < 0 > ( false ) , Return ( true ) ) ) ;
 EXPECT_CALL ( start_callback_ , Run ( DataTypeController : : OK_FIRST_RUN , _ , _ ) ) ;
 Start ( ) ;
 }