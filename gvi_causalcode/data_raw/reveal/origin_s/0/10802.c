TEST_F ( SyncBookmarkDataTypeControllerTest , StartOk ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 SetAssociateExpectations ( ) ;
 EXPECT_CALL ( * model_associator_ , SyncModelHasUserCreatedNodes ( _ ) ) . WillRepeatedly ( DoAll ( SetArgumentPointee < 0 > ( true ) , Return ( true ) ) ) ;
 EXPECT_CALL ( start_callback_ , Run ( DataTypeController : : OK , _ , _ ) ) ;
 Start ( ) ;
 }