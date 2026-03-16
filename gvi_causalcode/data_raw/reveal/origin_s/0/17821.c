TEST_F ( SyncBookmarkDataTypeControllerTest , StartAssociationTriggersUnrecoverableError ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 EXPECT_CALL ( * profile_sync_factory_ , CreateBookmarkSyncComponents ( _ , _ ) ) ;
 EXPECT_CALL ( * model_associator_ , CryptoReadyIfNecessary ( ) ) . WillRepeatedly ( Return ( true ) ) ;
 EXPECT_CALL ( * model_associator_ , SyncModelHasUserCreatedNodes ( _ ) ) . WillRepeatedly ( DoAll ( SetArgumentPointee < 0 > ( false ) , Return ( false ) ) ) ;
 EXPECT_CALL ( start_callback_ , Run ( DataTypeController : : UNRECOVERABLE_ERROR , _ , _ ) ) ;
 Start ( ) ;
 EXPECT_EQ ( DataTypeController : : NOT_RUNNING , bookmark_dtc_ -> state ( ) ) ;
 }