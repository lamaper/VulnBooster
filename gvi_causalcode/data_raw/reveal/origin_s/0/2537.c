TEST_F ( SyncBookmarkDataTypeControllerTest , StartDependentsReady ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 SetAssociateExpectations ( ) ;
 EXPECT_EQ ( DataTypeController : : NOT_RUNNING , bookmark_dtc_ -> state ( ) ) ;
 EXPECT_CALL ( start_callback_ , Run ( DataTypeController : : OK , _ , _ ) ) ;
 Start ( ) ;
 EXPECT_EQ ( DataTypeController : : RUNNING , bookmark_dtc_ -> state ( ) ) ;
 }