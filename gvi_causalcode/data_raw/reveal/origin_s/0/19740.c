TEST_F ( ExtensionServiceSyncTest , DeferredSyncStartupOnInstall ) {
 InitializeEmptyExtensionService ( ) ;
 service ( ) -> Init ( ) ;
 ASSERT_TRUE ( service ( ) -> is_ready ( ) ) ;
 bool flare_was_called = false ;
 syncer : : ModelType triggered_type ( syncer : : UNSPECIFIED ) ;
 base : : WeakPtrFactory < ExtensionServiceSyncTest > factory ( this ) ;
 extension_sync_service ( ) -> SetSyncStartFlareForTesting ( base : : Bind ( & ExtensionServiceSyncTest : : MockSyncStartFlare , factory . GetWeakPtr ( ) , & flare_was_called , & triggered_type ) ) ;
 base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 InstallCRX ( path , INSTALL_NEW ) ;
 EXPECT_TRUE ( flare_was_called ) ;
 EXPECT_EQ ( syncer : : EXTENSIONS , triggered_type ) ;
 flare_was_called = false ;
 triggered_type = syncer : : UNSPECIFIED ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 path = data_dir ( ) . AppendASCII ( "page_action.crx" ) ;
 InstallCRX ( path , INSTALL_NEW ) ;
 EXPECT_FALSE ( flare_was_called ) ;
 ASSERT_EQ ( syncer : : UNSPECIFIED , triggered_type ) ;
 }