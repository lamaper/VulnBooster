TEST_F ( ExtensionServiceSyncTest , GetSyncAppDataUserSettings ) {
 InitializeEmptyExtensionService ( ) ;
 const Extension * app = PackAndInstallCRX ( data_dir ( ) . AppendASCII ( "app" ) , INSTALL_NEW ) ;
 ASSERT_TRUE ( app ) ;
 ASSERT_TRUE ( app -> is_app ( ) ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : APPS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 syncer : : StringOrdinal initial_ordinal = syncer : : StringOrdinal : : CreateInitialOrdinal ( ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : APPS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > app_sync_data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 EXPECT_TRUE ( initial_ordinal . Equals ( app_sync_data -> app_launch_ordinal ( ) ) ) ;
 EXPECT_TRUE ( initial_ordinal . Equals ( app_sync_data -> page_ordinal ( ) ) ) ;
 }
 AppSorting * sorting = ExtensionSystem : : Get ( profile ( ) ) -> app_sorting ( ) ;
 sorting -> SetAppLaunchOrdinal ( app -> id ( ) , initial_ordinal . CreateAfter ( ) ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : APPS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > app_sync_data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( app_sync_data . get ( ) ) ;
 EXPECT_TRUE ( initial_ordinal . LessThan ( app_sync_data -> app_launch_ordinal ( ) ) ) ;
 EXPECT_TRUE ( initial_ordinal . Equals ( app_sync_data -> page_ordinal ( ) ) ) ;
 }
 sorting -> SetPageOrdinal ( app -> id ( ) , initial_ordinal . CreateAfter ( ) ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : APPS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > app_sync_data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( app_sync_data . get ( ) ) ;
 EXPECT_TRUE ( initial_ordinal . LessThan ( app_sync_data -> app_launch_ordinal ( ) ) ) ;
 EXPECT_TRUE ( initial_ordinal . LessThan ( app_sync_data -> page_ordinal ( ) ) ) ;
 }
 }