TEST_F ( ExtensionServiceSyncTest , GetSyncAppDataUserSettingsOnExtensionMoved ) {
 InitializeEmptyExtensionService ( ) ;
 const size_t kAppCount = 3 ;
 const Extension * apps [ kAppCount ] ;
 apps [ 0 ] = PackAndInstallCRX ( data_dir ( ) . AppendASCII ( "app1" ) , INSTALL_NEW ) ;
 apps [ 1 ] = PackAndInstallCRX ( data_dir ( ) . AppendASCII ( "app2" ) , INSTALL_NEW ) ;
 apps [ 2 ] = PackAndInstallCRX ( data_dir ( ) . AppendASCII ( "app4" ) , INSTALL_NEW ) ;
 for ( size_t i = 0 ;
 i < kAppCount ;
 ++ i ) {
 ASSERT_TRUE ( apps [ i ] ) ;
 ASSERT_TRUE ( apps [ i ] -> is_app ( ) ) ;
 }
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : APPS , syncer : : SyncDataList ( ) , base : : WrapUnique ( new syncer : : FakeSyncChangeProcessor ( ) ) , base : : WrapUnique ( new syncer : : SyncErrorFactoryMock ( ) ) ) ;
 ExtensionSystem : : Get ( service ( ) -> GetBrowserContext ( ) ) -> app_sorting ( ) -> OnExtensionMoved ( apps [ 0 ] -> id ( ) , apps [ 1 ] -> id ( ) , apps [ 2 ] -> id ( ) ) ;
 {
 syncer : : SyncDataList list = extension_sync_service ( ) -> GetAllSyncData ( syncer : : APPS ) ;
 ASSERT_EQ ( list . size ( ) , 3U ) ;
 std : : unique_ptr < ExtensionSyncData > data [ kAppCount ] ;
 for ( size_t i = 0 ;
 i < kAppCount ;
 ++ i ) {
 data [ i ] = ExtensionSyncData : : CreateFromSyncData ( list [ i ] ) ;
 ASSERT_TRUE ( data [ i ] . get ( ) ) ;
 }
 syncer : : StringOrdinal app_launch_ordinals [ kAppCount ] ;
 for ( size_t i = 0 ;
 i < kAppCount ;
 ++ i ) {
 for ( size_t j = 0 ;
 j < kAppCount ;
 ++ j ) {
 if ( apps [ i ] -> id ( ) == data [ j ] -> id ( ) ) app_launch_ordinals [ i ] = data [ j ] -> app_launch_ordinal ( ) ;
 }
 }
 EXPECT_TRUE ( app_launch_ordinals [ 1 ] . LessThan ( app_launch_ordinals [ 0 ] ) ) ;
 EXPECT_TRUE ( app_launch_ordinals [ 0 ] . LessThan ( app_launch_ordinals [ 2 ] ) ) ;
 }
 }