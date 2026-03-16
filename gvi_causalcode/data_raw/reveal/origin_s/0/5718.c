TEST_F ( ExtensionServiceSyncTest , GetSyncDataTerminated ) {
 InitializeEmptyExtensionService ( ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 TerminateExtension ( good_crx ) ;
 const Extension * extension = service ( ) -> GetInstalledExtension ( good_crx ) ;
 ASSERT_TRUE ( extension ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 1U ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( list [ 0 ] ) ;
 ASSERT_TRUE ( data . get ( ) ) ;
 EXPECT_EQ ( extension -> id ( ) , data -> id ( ) ) ;
 EXPECT_FALSE ( data -> uninstalled ( ) ) ;
 EXPECT_EQ ( service ( ) -> IsExtensionEnabled ( good_crx ) , data -> enabled ( ) ) ;
 EXPECT_EQ ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) , data -> incognito_enabled ( ) ) ;
 EXPECT_EQ ( ExtensionSyncData : : BOOLEAN_UNSET , data -> all_urls_enabled ( ) ) ;
 EXPECT_EQ ( data -> version ( ) , * extension -> version ( ) ) ;
 EXPECT_EQ ( extensions : : ManifestURL : : GetUpdateURL ( extension ) , data -> update_url ( ) ) ;
 EXPECT_EQ ( extension -> name ( ) , data -> name ( ) ) ;
 }