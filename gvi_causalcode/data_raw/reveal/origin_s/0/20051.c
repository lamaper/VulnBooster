TEST_F ( ExtensionServiceSyncTest , GetSyncExtensionDataUserSettings ) {
 InitializeEmptyExtensionService ( ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 const Extension * extension = service ( ) -> GetInstalledExtension ( good_crx ) ;
 ASSERT_TRUE ( extension ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_TRUE ( data -> enabled ( ) ) ;
 EXPECT_FALSE ( data -> incognito_enabled ( ) ) ;
 EXPECT_EQ ( ExtensionSyncData : : BOOLEAN_UNSET , data -> all_urls_enabled ( ) ) ;
 }
 service ( ) -> DisableExtension ( good_crx , extensions : : disable_reason : : DISABLE_USER_ACTION ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_FALSE ( data -> enabled ( ) ) ;
 EXPECT_FALSE ( data -> incognito_enabled ( ) ) ;
 EXPECT_EQ ( ExtensionSyncData : : BOOLEAN_UNSET , data -> all_urls_enabled ( ) ) ;
 }
 extensions : : util : : SetIsIncognitoEnabled ( good_crx , profile ( ) , true ) ;
 ScriptingPermissionsModifier permissions_modifier ( profile ( ) , registry ( ) -> GetExtensionById ( good_crx , extensions : : ExtensionRegistry : : EVERYTHING ) ) ;
 permissions_modifier . SetAllowedOnAllUrls ( false ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_FALSE ( data -> enabled ( ) ) ;
 EXPECT_TRUE ( data -> incognito_enabled ( ) ) ;
 EXPECT_EQ ( ExtensionSyncData : : BOOLEAN_FALSE , data -> all_urls_enabled ( ) ) ;
 }
 service ( ) -> EnableExtension ( good_crx ) ;
 permissions_modifier . SetAllowedOnAllUrls ( true ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_TRUE ( data -> enabled ( ) ) ;
 EXPECT_TRUE ( data -> incognito_enabled ( ) ) ;
 EXPECT_EQ ( ExtensionSyncData : : BOOLEAN_TRUE , data -> all_urls_enabled ( ) ) ;
 }
 }