TEST_F ( ExtensionServiceSyncTest , DontSelfNotify ) {
 base : : FilePath source_install_dir = data_dir ( ) . AppendASCII ( "good" ) . AppendASCII ( "Extensions" ) ;
 base : : FilePath pref_path = source_install_dir . DirName ( ) . Append ( chrome : : kPreferencesFilename ) ;
 InitializeInstalledExtensionService ( pref_path , source_install_dir ) ;
 ProfileSyncServiceFactory : : GetForProfile ( profile ( ) ) -> SetFirstSetupComplete ( ) ;
 extension_sync_service ( ) ;
 service ( ) -> Init ( ) ;
 ASSERT_TRUE ( service ( ) -> is_ready ( ) ) ;
 ASSERT_EQ ( 3u , loaded_ . size ( ) ) ;
 ASSERT_TRUE ( service ( ) -> IsExtensionEnabled ( good0 ) ) ;
 syncer : : FakeSyncChangeProcessor * processor = new syncer : : FakeSyncChangeProcessor ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : WrapUnique ( processor ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 processor -> changes ( ) . clear ( ) ;
 {
 const Extension * extension = service ( ) -> GetExtensionById ( good0 , true ) ;
 ASSERT_TRUE ( extension ) ;
 ExtensionSyncData data ( * extension , false , extensions : : disable_reason : : DISABLE_USER_ACTION , false , false , ExtensionSyncData : : BOOLEAN_UNSET , false ) ;
 SyncChangeList list ( 1 , data . GetSyncChange ( SyncChange : : ACTION_UPDATE ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( processor -> changes ( ) . empty ( ) ) ;
 }
 {
 const Extension * extension = service ( ) -> GetExtensionById ( good0 , true ) ;
 ASSERT_TRUE ( extension ) ;
 ExtensionSyncData data ( * extension , false , extensions : : disable_reason : : DISABLE_NONE , true , false , ExtensionSyncData : : BOOLEAN_UNSET , false ) ;
 SyncChangeList list ( 1 , data . GetSyncChange ( SyncChange : : ACTION_UPDATE ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( processor -> changes ( ) . empty ( ) ) ;
 }
 {
 const Extension * extension = service ( ) -> GetExtensionById ( good0 , true ) ;
 ASSERT_TRUE ( extension ) ;
 ExtensionSyncData data ( * extension , false , extensions : : disable_reason : : DISABLE_USER_ACTION | extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE , false , false , ExtensionSyncData : : BOOLEAN_UNSET , false ) ;
 SyncChangeList list ( 1 , data . GetSyncChange ( SyncChange : : ACTION_UPDATE ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( processor -> changes ( ) . empty ( ) ) ;
 }
 {
 const Extension * extension = service ( ) -> GetExtensionById ( good0 , true ) ;
 ASSERT_TRUE ( extension ) ;
 ExtensionSyncData data ( * extension , false , extensions : : disable_reason : : DISABLE_USER_ACTION | extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE , false , false , ExtensionSyncData : : BOOLEAN_UNSET , false ) ;
 SyncChangeList list ( 1 , data . GetSyncChange ( SyncChange : : ACTION_DELETE ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( processor -> changes ( ) . empty ( ) ) ;
 }
 }