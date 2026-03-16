TEST_F ( SyncBookmarkDataTypeControllerTest , StartAssociationFailed ) {
 CreateBookmarkModel ( LOAD_MODEL ) ;
 SetStartExpectations ( ) ;
 EXPECT_CALL ( * profile_sync_factory_ , CreateBookmarkSyncComponents ( _ , _ ) ) ;
 EXPECT_CALL ( * model_associator_ , CryptoReadyIfNecessary ( ) ) . WillRepeatedly ( Return ( true ) ) ;
 EXPECT_CALL ( * model_associator_ , SyncModelHasUserCreatedNodes ( _ ) ) . WillRepeatedly ( DoAll ( SetArgumentPointee < 0 > ( true ) , Return ( true ) ) ) ;
 EXPECT_CALL ( * model_associator_ , AssociateModels ( _ , _ ) ) . WillRepeatedly ( Return ( syncer : : SyncError ( FROM_HERE , syncer : : SyncError : : DATATYPE_ERROR , "error" , syncer : : BOOKMARKS ) ) ) ;
 EXPECT_CALL ( start_callback_ , Run ( DataTypeController : : ASSOCIATION_FAILED , _ , _ ) ) ;
 Start ( ) ;
 EXPECT_EQ ( DataTypeController : : DISABLED , bookmark_dtc_ -> state ( ) ) ;
 }