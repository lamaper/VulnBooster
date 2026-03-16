TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataWrongType ) {
 InitializeEmptyExtensionService ( ) ;
 StartSyncing ( syncer : : EXTENSIONS ) ;
 StartSyncing ( syncer : : APPS ) ;
 base : : FilePath extension_path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 InstallCRX ( extension_path , INSTALL_NEW ) ;
 EXPECT_TRUE ( service ( ) -> GetExtensionById ( good_crx , true ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : AppSpecifics * app_specifics = specifics . mutable_app ( ) ;
 sync_pb : : ExtensionSpecifics * extension_specifics = app_specifics -> mutable_extension ( ) ;
 extension_specifics -> set_id ( good_crx ) ;
 extension_specifics -> set_version ( service ( ) -> GetInstalledExtension ( good_crx ) -> version ( ) -> GetString ( ) ) ;
 {
 extension_specifics -> set_enabled ( true ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_DELETE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( service ( ) -> GetExtensionById ( good_crx , true ) ) ;
 }
 {
 extension_specifics -> set_enabled ( false ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( service ( ) -> GetExtensionById ( good_crx , false ) ) ;
 }
 }