TEST_F ( ExtensionServiceSyncTest , GetSyncDataDisableReasons ) {
 InitializeEmptyExtensionService ( ) ;
 const Extension * extension = InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 ASSERT_TRUE ( extension ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_TRUE ( data -> enabled ( ) ) ;
 EXPECT_TRUE ( data -> supports_disable_reasons ( ) ) ;
 EXPECT_EQ ( extensions : : disable_reason : : DISABLE_NONE , data -> disable_reasons ( ) ) ;
 }
 service ( ) -> DisableExtension ( good_crx , extensions : : disable_reason : : DISABLE_USER_ACTION ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_FALSE ( data -> enabled ( ) ) ;
 EXPECT_TRUE ( data -> supports_disable_reasons ( ) ) ;
 EXPECT_EQ ( extensions : : disable_reason : : DISABLE_USER_ACTION , data -> disable_reasons ( ) ) ;
 }
 service ( ) -> EnableExtension ( good_crx ) ;
 service ( ) -> DisableExtension ( good_crx , extensions : : disable_reason : : DISABLE_RELOAD ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_TRUE ( data -> enabled ( ) ) ;
 EXPECT_TRUE ( data -> supports_disable_reasons ( ) ) ;
 EXPECT_EQ ( extensions : : disable_reason : : DISABLE_NONE , data -> disable_reasons ( ) ) ;
 }
 service ( ) -> EnableExtension ( good_crx ) ;
 service ( ) -> DisableExtension ( good_crx , extensions : : disable_reason : : DISABLE_USER_ACTION | extensions : : disable_reason : : DISABLE_RELOAD ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_FALSE ( data -> enabled ( ) ) ;
 EXPECT_TRUE ( data -> supports_disable_reasons ( ) ) ;
 EXPECT_EQ ( extensions : : disable_reason : : DISABLE_USER_ACTION , data -> disable_reasons ( ) ) ;
 }
 service ( ) -> EnableExtension ( good_crx ) ;
 }