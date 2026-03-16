TEST_F ( ExtensionServiceSyncTest , DefaultInstalledExtensionsAreNotReenabledOrDisabledBySync ) {
 InitializeEmptyExtensionService ( ) ;
 browser_sync : : ProfileSyncService * sync_service = ProfileSyncServiceFactory : : GetForProfile ( profile ( ) ) ;
 sync_service -> SetFirstSetupComplete ( ) ;
 service ( ) -> Init ( ) ;
 extensions : : ChromeTestExtensionLoader extension_loader ( profile ( ) ) ;
 extension_loader . set_pack_extension ( true ) ;
 extension_loader . add_creation_flag ( Extension : : WAS_INSTALLED_BY_DEFAULT ) ;
 scoped_refptr < const Extension > extension = extension_loader . LoadExtension ( data_dir ( ) . AppendASCII ( "simple_with_file" ) ) ;
 ASSERT_TRUE ( extension ) ;
 EXPECT_FALSE ( extensions : : util : : ShouldSync ( extension . get ( ) , profile ( ) ) ) ;
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
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 EXPECT_TRUE ( processor_raw -> changes ( ) . empty ( ) ) ;
 service ( ) -> DisableExtension ( kExtensionId , extensions : : disable_reason : : DISABLE_USER_ACTION ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 EXPECT_TRUE ( processor_raw -> changes ( ) . empty ( ) ) ;
 EnableExtensionFromSync ( * extension ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 EXPECT_TRUE ( processor_raw -> changes ( ) . empty ( ) ) ;
 service ( ) -> EnableExtension ( kExtensionId ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . GetByID ( kExtensionId ) ) ;
 EXPECT_TRUE ( processor_raw -> changes ( ) . empty ( ) ) ;
 }