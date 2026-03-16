TEST_F ( ExtensionServiceSyncTest , DeferredSyncStartupPreInstalledComponent ) {
 InitializeEmptyExtensionService ( ) ;
 bool flare_was_called = false ;
 syncer : : ModelType triggered_type ( syncer : : UNSPECIFIED ) ;
 base : : WeakPtrFactory < ExtensionServiceSyncTest > factory ( this ) ;
 extension_sync_service ( ) -> SetSyncStartFlareForTesting ( base : : Bind ( & ExtensionServiceSyncTest : : MockSyncStartFlare , factory . GetWeakPtr ( ) , & flare_was_called , & triggered_type ) ) ;
 std : : string manifest ;
 ASSERT_TRUE ( base : : ReadFileToString ( good0_path ( ) . Append ( extensions : : kManifestFilename ) , & manifest ) ) ;
 service ( ) -> component_loader ( ) -> Add ( manifest , good0_path ( ) ) ;
 ASSERT_FALSE ( service ( ) -> is_ready ( ) ) ;
 service ( ) -> Init ( ) ;
 ASSERT_TRUE ( service ( ) -> is_ready ( ) ) ;
 EXPECT_FALSE ( flare_was_called ) ;
 ASSERT_EQ ( syncer : : UNSPECIFIED , triggered_type ) ;
 }