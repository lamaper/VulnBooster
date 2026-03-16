TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataUninstall ) {
 InitializeEmptyExtensionService ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( good_crx ) ;
 ext_specifics -> set_version ( "1.0" ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_DELETE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> GetExtensionById ( good_crx , true ) ) ;
 base : : FilePath extension_path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 InstallCRX ( extension_path , INSTALL_NEW ) ;
 EXPECT_TRUE ( service ( ) -> GetExtensionById ( good_crx , true ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> GetExtensionById ( good_crx , true ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> GetExtensionById ( good_crx , true ) ) ;
 }