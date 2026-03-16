TEST_F ( ExtensionServiceSyncTest , GetSyncDataFilter ) {
 InitializeEmptyExtensionService ( ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 const Extension * extension = service ( ) -> GetInstalledExtension ( good_crx ) ;
 ASSERT_TRUE ( extension ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : APPS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( list . size ( ) , 0U ) ;
 }