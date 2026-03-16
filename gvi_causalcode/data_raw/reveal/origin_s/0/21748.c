TEST_F ( SyncBookmarkDataTypeControllerTest , Stop ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 SetAssociateExpectations ( ) ;
 SetStopExpectations ( ) ;
 EXPECT_EQ ( DataTypeController : : NOT_RUNNING , bookmark_dtc_ -> state ( ) ) ;
 EXPECT_CALL ( start_callback_ , Run ( DataTypeController : : OK , _ , _ ) ) ;
 Start ( ) ;
 EXPECT_EQ ( DataTypeController : : RUNNING , bookmark_dtc_ -> state ( ) ) ;
 bookmark_dtc_ -> Stop ( ) ;
 EXPECT_EQ ( DataTypeController : : NOT_RUNNING , bookmark_dtc_ -> state ( ) ) ;
 }