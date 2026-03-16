TEST_F ( ExtensionServiceSyncTest , DisableExtensionFromSync ) {
 base : : FilePath source_install_dir = data_dir ( ) . AppendASCII ( "good" ) . AppendASCII ( "Extensions" ) ;
 base : : FilePath pref_path = source_install_dir . DirName ( ) . Append ( chrome : : kPreferencesFilename ) ;
 InitializeInstalledExtensionService ( pref_path , source_install_dir ) ;
 browser_sync : : ProfileSyncService * sync_service = ProfileSyncServiceFactory : : GetForProfile ( profile ( ) ) ;
 sync_service -> SetFirstSetupComplete ( ) ;
 service ( ) -> Init ( ) ;
 ASSERT_TRUE ( service ( ) -> is_ready ( ) ) ;
 ASSERT_EQ ( 3u , loaded_ . size ( ) ) ;
 const Extension * extension = service ( ) -> GetExtensionById ( good0 , true ) ;
 ASSERT_TRUE ( extension ) ;
 ASSERT_TRUE ( service ( ) -> IsExtensionEnabled ( good0 ) ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 ExtensionSyncData disable_good_crx ( * extension , false , extensions : : disable_reason : : DISABLE_USER_ACTION , false , false , ExtensionSyncData : : BOOLEAN_UNSET , false ) ;
 SyncChangeList list ( 1 , disable_good_crx . GetSyncChange ( SyncChange : : ACTION_UPDATE ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 ASSERT_FALSE ( service ( ) -> IsExtensionEnabled ( good0 ) ) ;
 }