TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataSettings ) {
 InitializeEmptyExtensionService ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 EXPECT_TRUE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_FALSE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 auto get_permissions_modifier = [ this ] ( ) {
 const Extension * extension = registry ( ) -> GetExtensionById ( good_crx , extensions : : ExtensionRegistry : : EVERYTHING ) ;
 return base : : MakeUnique < ScriptingPermissionsModifier > ( profile ( ) , extension ) ;
 }
 ;
 EXPECT_FALSE ( get_permissions_modifier ( ) -> HasSetAllowedOnAllUrls ( ) ) ;
 const bool kDefaultAllowedScripting = ScriptingPermissionsModifier : : DefaultAllowedOnAllUrls ( ) ;
 EXPECT_EQ ( kDefaultAllowedScripting , get_permissions_modifier ( ) -> IsAllowedOnAllUrls ( ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( good_crx ) ;
 ext_specifics -> set_version ( service ( ) -> GetInstalledExtension ( good_crx ) -> version ( ) -> GetString ( ) ) ;
 ext_specifics -> set_enabled ( false ) ;
 {
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_FALSE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 EXPECT_FALSE ( get_permissions_modifier ( ) -> HasSetAllowedOnAllUrls ( ) ) ;
 EXPECT_EQ ( kDefaultAllowedScripting , get_permissions_modifier ( ) -> IsAllowedOnAllUrls ( ) ) ;
 }
 {
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_incognito_enabled ( true ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_TRUE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 }
 {
 ext_specifics -> set_enabled ( false ) ;
 ext_specifics -> set_incognito_enabled ( true ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_TRUE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 }
 {
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_all_urls_enabled ( ! kDefaultAllowedScripting ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_TRUE ( get_permissions_modifier ( ) -> HasSetAllowedOnAllUrls ( ) ) ;
 EXPECT_EQ ( ! kDefaultAllowedScripting , get_permissions_modifier ( ) -> IsAllowedOnAllUrls ( ) ) ;
 }
 {
 ext_specifics -> set_all_urls_enabled ( kDefaultAllowedScripting ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_TRUE ( get_permissions_modifier ( ) -> HasSetAllowedOnAllUrls ( ) ) ;
 EXPECT_EQ ( kDefaultAllowedScripting , get_permissions_modifier ( ) -> IsAllowedOnAllUrls ( ) ) ;
 }
 EXPECT_FALSE ( service ( ) -> pending_extension_manager ( ) -> IsIdPending ( good_crx ) ) ;
 }