TEST_F ( ExtensionServiceSyncTest , ReenableDisabledExtensionFromSync ) {
 InitializeEmptyExtensionService ( ) ;
 browser_sync : : ProfileSyncService * sync_service = ProfileSyncServiceFactory : : GetForProfile ( profile ( ) ) ;
 sync_service -> SetFirstSetupComplete ( ) ;
 service ( ) -> Init ( ) ;
 extensions : : ChromeTestExtensionLoader extension_loader ( profile ( ) ) ;
 extension_loader . set_pack_extension ( true ) ;
 scoped_refptr < const Extension > extension = extension_loader . LoadExtension ( data_dir ( ) . AppendASCII ( "simple_with_file" ) ) ;
 ASSERT_TRUE ( extension ) ;
 const std : : string kExtensionId = extension -> id ( ) ;
 ASSERT_TRUE ( registry ( ) -> enabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 syncer : : FakeSyncChangeProcessor * processor_raw = nullptr ;
 {
 auto processor = base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) ;
 processor_raw = processor . get ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , std : : move ( processor ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 }
 processor_raw -> changes ( ) . clear ( ) ;
 DisableExtensionFromSync ( * extension , extensions : : disable_reason : : DISABLE_USER_ACTION ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 EXPECT_EQ ( extensions : : disable_reason : : DISABLE_USER_ACTION , ExtensionPrefs : : Get ( profile ( ) ) -> GetDisableReasons ( kExtensionId ) ) ;
 EXPECT_TRUE ( processor_raw -> changes ( ) . empty ( ) ) ;
 service ( ) -> EnableExtension ( kExtensionId ) ;
 {
 ASSERT_EQ ( 1u , processor_raw -> changes ( ) . size ( ) ) ;
 const SyncChange & change = processor_raw -> changes ( ) [ 0 ] ;
 EXPECT_EQ ( SyncChange : : ACTION_UPDATE , change . change_type ( ) ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( change . sync_data ( ) ) ;
 EXPECT_EQ ( kExtensionId , data -> id ( ) ) ;
 EXPECT_EQ ( 0 , data -> disable_reasons ( ) ) ;
 EXPECT_TRUE ( data -> enabled ( ) ) ;
 }
 processor_raw -> changes ( ) . clear ( ) ;
 service ( ) -> DisableExtension ( kExtensionId , extensions : : disable_reason : : DISABLE_USER_ACTION ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 {
 ASSERT_EQ ( 1u , processor_raw -> changes ( ) . size ( ) ) ;
 const SyncChange & change = processor_raw -> changes ( ) [ 0 ] ;
 EXPECT_EQ ( SyncChange : : ACTION_UPDATE , change . change_type ( ) ) ;
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncData ( change . sync_data ( ) ) ;
 EXPECT_EQ ( kExtensionId , data -> id ( ) ) ;
 EXPECT_EQ ( extensions : : disable_reason : : DISABLE_USER_ACTION , data -> disable_reasons ( ) ) ;
 EXPECT_FALSE ( data -> enabled ( ) ) ;
 }
 processor_raw -> changes ( ) . clear ( ) ;
 EnableExtensionFromSync ( * extension ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 EXPECT_TRUE ( processor_raw -> changes ( ) . empty ( ) ) ;
 }