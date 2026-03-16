TEST_F ( ExtensionServiceSyncTest , GetSyncDataList ) {
 InitializeEmptyExtensionService ( ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "page_action.crx" ) , INSTALL_NEW ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "theme.crx" ) , INSTALL_NEW ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "theme2.crx" ) , INSTALL_NEW ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : APPS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 service ( ) -> DisableExtension ( page_action , extensions : : disable_reason : : DISABLE_USER_ACTION ) ;
 TerminateExtension ( theme2_crx ) ;
 EXPECT_EQ ( 0u , extension_sync_service ( ) -> GetAllSyncData ( syncer : : APPS ) . size ( ) ) ;
 EXPECT_EQ ( 2u , extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) . size ( ) ) ;
 }