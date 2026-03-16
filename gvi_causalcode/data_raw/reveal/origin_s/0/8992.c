TEST_F ( ExtensionServiceSyncTest , SyncForUninstalledExternalExtension ) {
 InitializeEmptyExtensionService ( ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , Manifest : : EXTERNAL_PREF , INSTALL_NEW , Extension : : NO_FLAGS ) ;
 const Extension * extension = service ( ) -> GetInstalledExtension ( good_crx ) ;
 ASSERT_TRUE ( extension ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 StartSyncing ( syncer : : APPS ) ;
 UninstallExtension ( good_crx , false ) ;
 EXPECT_TRUE ( ExtensionPrefs : : Get ( profile ( ) ) -> IsExternalExtensionUninstalled ( good_crx ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : AppSpecifics * app_specifics = specifics . mutable_app ( ) ;
 sync_pb : : ExtensionSpecifics * extension_specifics = app_specifics -> mutable_extension ( ) ;
 extension_specifics -> set_id ( good_crx ) ;
 extension_specifics -> set_version ( "1.0" ) ;
 extension_specifics -> set_enabled ( true ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( ExtensionPrefs : : Get ( profile ( ) ) -> IsExternalExtensionUninstalled ( good_crx ) ) ;
 }