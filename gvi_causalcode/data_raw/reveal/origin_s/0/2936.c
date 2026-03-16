TEST_F ( ExtensionServiceSyncTest , DeferredSyncStartupPreInstalledNormal ) {
 InitializeGoodInstalledExtensionService ( ) ;
 bool flare_was_called = false ;
 syncer : : ModelType triggered_type ( syncer : : UNSPECIFIED ) ;
 base : : WeakPtrFactory < ExtensionServiceSyncTest > factory ( this ) ;
 extension_sync_service ( ) -> SetSyncStartFlareForTesting ( base : : Bind ( & ExtensionServiceSyncTest : : MockSyncStartFlare , factory . GetWeakPtr ( ) , & flare_was_called , & triggered_type ) ) ;
 ASSERT_FALSE ( service ( ) -> is_ready ( ) ) ;
 service ( ) -> Init ( ) ;
 ASSERT_EQ ( 3u , loaded_ . size ( ) ) ;
 ASSERT_TRUE ( service ( ) -> is_ready ( ) ) ;
 EXPECT_FALSE ( flare_was_called ) ;
 ASSERT_EQ ( syncer : : UNSPECIFIED , triggered_type ) ;
 }