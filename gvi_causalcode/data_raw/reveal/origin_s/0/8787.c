TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataNewExtension ) {
 InitializeEmptyExtensionService ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 const base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 const ExtensionPrefs * prefs = ExtensionPrefs : : Get ( profile ( ) ) ;
 struct TestCase {
 const char * name ;
 bool sync_enabled ;
 int sync_disable_reasons ;
 int expect_disable_reasons ;
 bool expect_permissions_granted ;
 }
 test_cases [ ] = {
 {
 "Standard" , true , 0 , 0 , true }
 , {
 "Disabled" , false , extensions : : disable_reason : : DISABLE_USER_ACTION , extensions : : disable_reason : : DISABLE_USER_ACTION , true }
 , {
 "Legacy" , false , - 1 , extensions : : disable_reason : : DISABLE_USER_ACTION , true }
 , {
 "PermissionsIncrease" , false , extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE , extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE , false }
 , }
 ;
 for ( const TestCase & test_case : test_cases ) {
 SCOPED_TRACE ( test_case . name ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( good_crx ) ;
 ext_specifics -> set_version ( base : : Version ( "1" ) . GetString ( ) ) ;
 ext_specifics -> set_enabled ( test_case . sync_enabled ) ;
 if ( test_case . sync_disable_reasons != - 1 ) ext_specifics -> set_disable_reasons ( test_case . sync_disable_reasons ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 ASSERT_TRUE ( service ( ) -> pending_extension_manager ( ) -> IsIdPending ( good_crx ) ) ;
 UpdateExtension ( good_crx , path , test_case . sync_enabled ? ENABLED : DISABLED ) ;
 EXPECT_EQ ( test_case . expect_disable_reasons , prefs -> GetDisableReasons ( good_crx ) ) ;
 std : : unique_ptr < const PermissionSet > permissions = prefs -> GetGrantedPermissions ( good_crx ) ;
 EXPECT_EQ ( test_case . expect_permissions_granted , ! permissions -> IsEmpty ( ) ) ;
 ASSERT_FALSE ( service ( ) -> pending_extension_manager ( ) -> IsIdPending ( good_crx ) ) ;
 UninstallExtension ( good_crx , false , test_case . sync_enabled ? Extension : : ENABLED : Extension : : DISABLED ) ;
 }
 }
 TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataTerminatedExtension ) {
 InitializeExtensionServiceWithUpdater ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 TerminateExtension ( good_crx ) ;
 EXPECT_TRUE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_FALSE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( good_crx ) ;
 ext_specifics -> set_version ( service ( ) -> GetInstalledExtension ( good_crx ) -> version ( ) -> GetString ( ) ) ;
 ext_specifics -> set_enabled ( false ) ;
 ext_specifics -> set_incognito_enabled ( true ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_TRUE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 EXPECT_FALSE ( service ( ) -> pending_extension_manager ( ) -> IsIdPending ( good_crx ) ) ;
 }
 TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataVersionCheck ) {
 InitializeExtensionServiceWithUpdater ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 EXPECT_TRUE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_FALSE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( good_crx ) ;
 ext_specifics -> set_enabled ( true ) ;
 const base : : Version installed_version = * service ( ) -> GetInstalledExtension ( good_crx ) -> version ( ) ;
 {
 ext_specifics -> set_version ( installed_version . GetString ( ) ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> updater ( ) -> WillCheckSoon ( ) ) ;
 syncer : : SyncDataList data = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( 1u , data . size ( ) ) ;
 std : : unique_ptr < ExtensionSyncData > extension_data = ExtensionSyncData : : CreateFromSyncData ( data [ 0 ] ) ;
 ASSERT_TRUE ( extension_data ) ;
 EXPECT_EQ ( installed_version , extension_data -> version ( ) ) ;
 }
 {
 ext_specifics -> set_version ( "0.0.0.0" ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( service ( ) -> updater ( ) -> WillCheckSoon ( ) ) ;
 syncer : : SyncDataList data = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( 1u , data . size ( ) ) ;
 std : : unique_ptr < ExtensionSyncData > extension_data = ExtensionSyncData : : CreateFromSyncData ( data [ 0 ] ) ;
 ASSERT_TRUE ( extension_data ) ;
 EXPECT_EQ ( installed_version , extension_data -> version ( ) ) ;
 }
 {
 const base : : Version new_version ( "9.9.9.9" ) ;
 ext_specifics -> set_version ( new_version . GetString ( ) ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( service ( ) -> updater ( ) -> WillCheckSoon ( ) ) ;
 syncer : : SyncDataList data = extension_sync_service ( ) -> GetAllSyncData ( syncer : : EXTENSIONS ) ;
 ASSERT_EQ ( 1u , data . size ( ) ) ;
 std : : unique_ptr < ExtensionSyncData > extension_data = ExtensionSyncData : : CreateFromSyncData ( data [ 0 ] ) ;
 ASSERT_TRUE ( extension_data ) ;
 EXPECT_EQ ( new_version , extension_data -> version ( ) ) ;
 }
 EXPECT_FALSE ( service ( ) -> pending_extension_manager ( ) -> IsIdPending ( good_crx ) ) ;
 }
 TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataNotInstalled ) {
 InitializeExtensionServiceWithUpdater ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( good_crx ) ;
 ext_specifics -> set_enabled ( false ) ;
 ext_specifics -> set_incognito_enabled ( true ) ;
 ext_specifics -> set_update_url ( "http://www.google.com/" ) ;
 ext_specifics -> set_version ( "1.2.3.4" ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 EXPECT_TRUE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_FALSE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( service ( ) -> updater ( ) -> WillCheckSoon ( ) ) ;
 EXPECT_FALSE ( service ( ) -> IsExtensionEnabled ( good_crx ) ) ;
 EXPECT_TRUE ( extensions : : util : : IsIncognitoEnabled ( good_crx , profile ( ) ) ) ;
 const extensions : : PendingExtensionInfo * info ;
 EXPECT_TRUE ( ( info = service ( ) -> pending_extension_manager ( ) -> GetById ( good_crx ) ) ) ;
 EXPECT_EQ ( ext_specifics -> update_url ( ) , info -> update_url ( ) . spec ( ) ) ;
 EXPECT_TRUE ( info -> is_from_sync ( ) ) ;
 EXPECT_EQ ( Manifest : : INTERNAL , info -> install_source ( ) ) ;
 }
 TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataEnableDisable ) {
 InitializeEmptyExtensionService ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 const ExtensionPrefs * prefs = ExtensionPrefs : : Get ( profile ( ) ) ;
 struct TestCase {
 const char * name ;
 int previous_disable_reasons ;
 bool sync_enable ;
 int sync_disable_reasons ;
 int expect_disable_reasons ;
 }
 test_cases [ ] = {
 {
 "NopEnable" , 0 , true , 0 , 0 }
 , {
 "NopDisable" , extensions : : disable_reason : : DISABLE_USER_ACTION , false , extensions : : disable_reason : : DISABLE_USER_ACTION , extensions : : disable_reason : : DISABLE_USER_ACTION }
 , {
 "Enable" , extensions : : disable_reason : : DISABLE_USER_ACTION , true , 0 , 0 }
 , {
 "Disable" , 0 , false , extensions : : disable_reason : : DISABLE_USER_ACTION , extensions : : disable_reason : : DISABLE_USER_ACTION }
 , {
 "AddDisableReason" , extensions : : disable_reason : : DISABLE_REMOTE_INSTALL , false , extensions : : disable_reason : : DISABLE_REMOTE_INSTALL | extensions : : disable_reason : : DISABLE_USER_ACTION , extensions : : disable_reason : : DISABLE_REMOTE_INSTALL | extensions : : disable_reason : : DISABLE_USER_ACTION }
 , {
 "RemoveDisableReason" , extensions : : disable_reason : : DISABLE_REMOTE_INSTALL | extensions : : disable_reason : : DISABLE_USER_ACTION , false , extensions : : disable_reason : : DISABLE_USER_ACTION , extensions : : disable_reason : : DISABLE_USER_ACTION }
 , {
 "PreserveLocalDisableReason" , extensions : : disable_reason : : DISABLE_RELOAD , true , 0 , extensions : : disable_reason : : DISABLE_RELOAD }
 , {
 "PreserveOnlyLocalDisableReason" , extensions : : disable_reason : : DISABLE_USER_ACTION | extensions : : disable_reason : : DISABLE_RELOAD , true , 0 , extensions : : disable_reason : : DISABLE_RELOAD }
 , {
 "M44Enable" , extensions : : disable_reason : : DISABLE_USER_ACTION , true , - 1 , 0 }
 , {
 "M44ReEnable" , extensions : : disable_reason : : DISABLE_USER_ACTION , true , extensions : : disable_reason : : DISABLE_USER_ACTION , 0 }
 , {
 "M44Disable" , 0 , false , - 1 , extensions : : disable_reason : : DISABLE_USER_ACTION }
 , {
 "M44ReDisable" , 0 , false , 0 , extensions : : disable_reason : : DISABLE_USER_ACTION }
 , {
 "M44AlreadyDisabledByUser" , extensions : : disable_reason : : DISABLE_USER_ACTION , false , - 1 , extensions : : disable_reason : : DISABLE_USER_ACTION }
 , {
 "M44AlreadyDisabledWithOtherReason" , extensions : : disable_reason : : DISABLE_REMOTE_INSTALL , false , - 1 , extensions : : disable_reason : : DISABLE_REMOTE_INSTALL | extensions : : disable_reason : : DISABLE_USER_ACTION }
 , }
 ;
 for ( const TestCase & test_case : test_cases ) {
 SCOPED_TRACE ( test_case . name ) ;
 std : : string id ;
 std : : string version ;
 {
 const Extension * extension = InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 ASSERT_TRUE ( extension ) ;
 id = extension -> id ( ) ;
 version = extension -> VersionString ( ) ;
 }
 ASSERT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 if ( test_case . previous_disable_reasons ) {
 service ( ) -> DisableExtension ( id , test_case . previous_disable_reasons ) ;
 ASSERT_TRUE ( registry ( ) -> disabled_extensions ( ) . Contains ( id ) ) ;
 }
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_enabled ( test_case . sync_enable ) ;
 ext_specifics -> set_version ( version ) ;
 if ( test_case . sync_disable_reasons != - 1 ) ext_specifics -> set_disable_reasons ( test_case . sync_disable_reasons ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 const bool expect_enabled = ! test_case . expect_disable_reasons ;
 EXPECT_EQ ( expect_enabled , service ( ) -> IsExtensionEnabled ( id ) ) ;
 EXPECT_EQ ( test_case . expect_disable_reasons , prefs -> GetDisableReasons ( id ) ) ;
 UninstallExtension ( id , false , expect_enabled ? Extension : : ENABLED : Extension : : DISABLED ) ;
 }
 }
 TEST_F ( ExtensionServiceSyncTest , ProcessSyncDataDeferredEnable ) {
 base : : CommandLine : : ForCurrentProcess ( ) -> AppendSwitchASCII ( switches : : kAppsGalleryUpdateURL , "http://localhost/autoupdate/updates.xml" ) ;
 InitializeEmptyExtensionService ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 base : : FilePath base_path = data_dir ( ) . AppendASCII ( "permissions_increase" ) ;
 base : : FilePath pem_path = base_path . AppendASCII ( "permissions.pem" ) ;
 base : : FilePath path = base_path . AppendASCII ( "v1" ) ;
 const Extension * extension = PackAndInstallCRX ( path , pem_path , INSTALL_NEW ) ;
 ASSERT_TRUE ( extension ) ;
 ASSERT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( extension -> id ( ) ) ) ;
 std : : string id = extension -> id ( ) ;
 path = base_path . AppendASCII ( "v2" ) ;
 PackCRXAndUpdateExtension ( id , path , pem_path , DISABLED ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_version ( "3" ) ;
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_disable_reasons ( extensions : : disable_reason : : DISABLE_NONE ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . Contains ( id ) ) ;
 path = base_path . AppendASCII ( "v3" ) ;
 PackCRXAndUpdateExtension ( id , path , pem_path , ENABLED ) ;
 }
 class ExtensionServiceSyncCustomGalleryTest : public ExtensionServiceSyncTest {
 public : void SetUp ( ) override {
 ExtensionServiceSyncTest : : SetUp ( ) ;
 base : : CommandLine : : ForCurrentProcess ( ) -> AppendSwitchASCII ( switches : : kAppsGalleryUpdateURL , "http://localhost/autoupdate/updates.xml" ) ;
 }
 }
 ;
 TEST_F ( ExtensionServiceSyncCustomGalleryTest , ProcessSyncDataPermissionApproval ) {
 InitializeEmptyExtensionService ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 const base : : FilePath base_path = data_dir ( ) . AppendASCII ( "permissions_increase" ) ;
 const base : : FilePath pem_path = base_path . AppendASCII ( "permissions.pem" ) ;
 const base : : FilePath path_v1 = base_path . AppendASCII ( "v1" ) ;
 const base : : FilePath path_v2 = base_path . AppendASCII ( "v2" ) ;
 base : : ScopedTempDir crx_dir ;
 ASSERT_TRUE ( crx_dir . CreateUniqueTempDir ( ) ) ;
 const base : : FilePath crx_path_v1 = crx_dir . GetPath ( ) . AppendASCII ( "temp1.crx" ) ;
 PackCRX ( path_v1 , pem_path , crx_path_v1 ) ;
 const base : : FilePath crx_path_v2 = crx_dir . GetPath ( ) . AppendASCII ( "temp2.crx" ) ;
 PackCRX ( path_v2 , pem_path , crx_path_v2 ) ;
 const std : : string v1 ( "1" ) ;
 const std : : string v2 ( "2" ) ;
 const ExtensionPrefs * prefs = ExtensionPrefs : : Get ( profile ( ) ) ;
 struct TestCase {
 const char * name ;
 const std : : string & sync_version ;
 int sync_disable_reasons ;
 int expect_disable_reasons ;
 bool expect_permissions_granted ;
 }
 test_cases [ ] = {
 {
 "OldVersion" , v1 , 0 , extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE , false }
 , {
 "Legacy" , v2 , - 1 , extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE , false }
 , {
 "GrantPermissions" , v2 , 0 , extensions : : disable_reason : : DISABLE_NONE , true }
 , }
 ;
 for ( const TestCase & test_case : test_cases ) {
 SCOPED_TRACE ( test_case . name ) ;
 std : : string id ;
 {
 const Extension * extension = InstallCRX ( crx_path_v1 , INSTALL_NEW ) ;
 ASSERT_TRUE ( extension ) ;
 ASSERT_EQ ( v1 , extension -> VersionString ( ) ) ;
 id = extension -> id ( ) ;
 }
 ASSERT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 std : : unique_ptr < const PermissionSet > granted_permissions_v1 = prefs -> GetGrantedPermissions ( id ) ;
 UpdateExtension ( id , crx_path_v2 , DISABLED ) ;
 {
 const Extension * extension = registry ( ) -> disabled_extensions ( ) . GetByID ( id ) ;
 ASSERT_TRUE ( extension ) ;
 ASSERT_EQ ( v2 , extension -> VersionString ( ) ) ;
 }
 ASSERT_TRUE ( prefs -> HasDisableReason ( id , extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE ) ) ;
 std : : unique_ptr < const PermissionSet > granted_permissions_v2 = prefs -> GetGrantedPermissions ( id ) ;
 ASSERT_EQ ( * granted_permissions_v1 , * granted_permissions_v2 ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_version ( test_case . sync_version ) ;
 if ( test_case . sync_disable_reasons != - 1 ) ext_specifics -> set_disable_reasons ( test_case . sync_disable_reasons ) ;
 SyncChangeList list = MakeSyncChangeList ( good_crx , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 const bool expect_enabled = ! test_case . expect_disable_reasons ;
 EXPECT_EQ ( expect_enabled , service ( ) -> IsExtensionEnabled ( id ) ) ;
 EXPECT_EQ ( test_case . expect_disable_reasons , prefs -> GetDisableReasons ( id ) ) ;
 std : : unique_ptr < const PermissionSet > granted_permissions = prefs -> GetGrantedPermissions ( id ) ;
 if ( test_case . expect_permissions_granted ) {
 std : : unique_ptr < const PermissionSet > active_permissions = prefs -> GetActivePermissions ( id ) ;
 EXPECT_EQ ( * granted_permissions , * active_permissions ) ;
 }
 else {
 EXPECT_EQ ( * granted_permissions , * granted_permissions_v1 ) ;
 }
 UninstallExtension ( id , false , expect_enabled ? Extension : : ENABLED : Extension : : DISABLED ) ;
 }
 }
 TEST_F ( ExtensionServiceSyncTest , DontSyncThemes ) {
 InitializeEmptyExtensionService ( ) ;
 ProfileSyncServiceFactory : : GetForProfile ( profile ( ) ) -> SetFirstSetupComplete ( ) ;
 extension_sync_service ( ) ;
 service ( ) -> Init ( ) ;
 ASSERT_TRUE ( service ( ) -> is_ready ( ) ) ;
 syncer : : FakeSyncChangeProcessor * processor = new syncer : : FakeSyncChangeProcessor ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : WrapUnique ( processor ) , base : : WrapUnique ( new syncer : : SyncErrorFactoryMock ) ) ;
 processor -> changes ( ) . clear ( ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "good.crx" ) , INSTALL_NEW ) ;
 EXPECT_EQ ( 1u , processor -> changes ( ) . size ( ) ) ;
 processor -> changes ( ) . clear ( ) ;
 InstallCRX ( data_dir ( ) . AppendASCII ( "theme.crx" ) , INSTALL_NEW ) ;
 content : : WindowedNotificationObserver theme_change_observer ( chrome : : NOTIFICATION_BROWSER_THEME_CHANGED , content : : Source < ThemeService > ( ThemeServiceFactory : : GetForProfile ( profile ( ) ) ) ) ;
 theme_change_observer . Wait ( ) ;
 EXPECT_TRUE ( processor -> changes ( ) . empty ( ) ) ;
 }

 public : ExtensionServiceTestSupervised ( ) : field_trial_list_ ( base : : MakeUnique < base : : MockEntropyProvider > ( ) ) {
 }
 void TearDown ( ) override {
 supervised_user_service ( ) -> SetDelegate ( nullptr ) ;
 ExtensionServiceSyncCustomGalleryTest : : TearDown ( ) ;
 }
 protected : void InitSupervisedUserInitiatedExtensionInstallFeature ( bool enabled ) {
 if ( enabled ) {
 scoped_feature_list_ . InitAndEnableFeature ( supervised_users : : kSupervisedUserInitiatedExtensionInstall ) ;
 }
 }
 bool IsPendingCustodianApproval ( const std : : string & extension_id ) {
 auto function = make_scoped_refptr ( new WebstorePrivateIsPendingCustodianApprovalFunction ( ) ) ;
 std : : unique_ptr < base : : Value > result ( RunFunctionAndReturnSingleResult ( function . get ( ) , "[\"" + extension_id + "\"]" , browser_context ( ) ) ) ;
 bool copy_bool_result = false ;
 EXPECT_TRUE ( result -> GetAsBoolean ( & copy_bool_result ) ) ;
 return copy_bool_result ;
 }
 void InitServices ( bool profile_is_supervised ) {
 ExtensionServiceInitParams params = CreateDefaultInitParams ( ) ;
 params . profile_is_supervised = profile_is_supervised ;
 if ( profile_is_supervised ) {
 params . pref_file = base : : FilePath ( ) ;
 }
 InitializeExtensionService ( params ) ;
 StartSyncing ( syncer : : EXTENSIONS ) ;
 supervised_user_service ( ) -> SetDelegate ( this ) ;
 supervised_user_service ( ) -> Init ( ) ;
 }
 std : : string InstallPermissionsTestExtension ( bool by_custodian ) {
 return InstallTestExtension ( permissions_increase , dir_path ( "1" ) , pem_path ( ) , by_custodian ) ;
 }
 void UpdatePermissionsTestExtension ( const std : : string & id , const std : : string & version , UpdateState expected_state ) {
 UpdateTestExtension ( dir_path ( version ) , pem_path ( ) , id , version , expected_state ) ;
 }
 std : : string InstallNoPermissionsTestExtension ( bool by_custodian ) {
 base : : FilePath base_path = data_dir ( ) . AppendASCII ( "autoupdate" ) ;
 base : : FilePath pem_path = base_path . AppendASCII ( "key.pem" ) ;
 base : : FilePath dir_path = base_path . AppendASCII ( "v1" ) ;
 return InstallTestExtension ( autoupdate , dir_path , pem_path , by_custodian ) ;
 }
 void UpdateNoPermissionsTestExtension ( const std : : string & id , const std : : string & version , UpdateState expected_state ) {
 base : : FilePath base_path = data_dir ( ) . AppendASCII ( "autoupdate" ) ;
 base : : FilePath pem_path = base_path . AppendASCII ( "key.pem" ) ;
 base : : FilePath dir_path = base_path . AppendASCII ( "v" + version ) ;
 UpdateTestExtension ( dir_path , pem_path , id , version , expected_state ) ;
 }
 std : : string InstallTestExtension ( const std : : string & id , const base : : FilePath & dir_path , const base : : FilePath & pem_path , bool by_custodian ) {
 InstallState expected_state = INSTALL_WITHOUT_LOAD ;
 if ( by_custodian ) {
 extensions : : util : : SetWasInstalledByCustodian ( id , profile ( ) , true ) ;
 expected_state = INSTALL_NEW ;
 }
 const Extension * extension = PackAndInstallCRX ( dir_path , pem_path , expected_state ) ;
 EXPECT_TRUE ( extension ) ;
 EXPECT_EQ ( extension -> id ( ) , id ) ;
 if ( by_custodian ) {
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 }
 else {
 CheckDisabledForCustodianApproval ( id ) ;
 }
 EXPECT_EQ ( * extension -> version ( ) , base : : Version ( "1" ) ) ;
 return id ;
 }
 void UpdateTestExtension ( const base : : FilePath & dir_path , const base : : FilePath & pem_path , const std : : string & id , const std : : string & version , const UpdateState & expected_state ) {
 PackCRXAndUpdateExtension ( id , dir_path , pem_path , expected_state ) ;
 const Extension * extension = registry ( ) -> GetInstalledExtension ( id ) ;
 ASSERT_TRUE ( extension ) ;
 EXPECT_EQ ( * extension -> version ( ) , base : : Version ( version ) ) ;
 }
 void SimulateCustodianApprovalChangeViaSync ( const std : : string & extension_id , const std : : string & version , SyncChange : : SyncChangeType type ) {
 std : : string key = SupervisedUserSettingsService : : MakeSplitSettingKey ( supervised_users : : kApprovedExtensions , extension_id ) ;
 syncer : : SyncData sync_data = SupervisedUserSettingsService : : CreateSyncDataForSetting ( key , base : : Value ( version ) ) ;
 SyncChangeList list ( 1 , SyncChange ( FROM_HERE , type , sync_data ) ) ;
 SupervisedUserSettingsService * supervised_user_settings_service = SupervisedUserSettingsServiceFactory : : GetForProfile ( profile ( ) ) ;
 supervised_user_settings_service -> ProcessSyncChanges ( FROM_HERE , list ) ;
 }
 void CheckDisabledForCustodianApproval ( const std : : string & extension_id ) {
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . Contains ( extension_id ) ) ;
 ExtensionPrefs * extension_prefs = ExtensionPrefs : : Get ( profile ( ) ) ;
 EXPECT_TRUE ( extension_prefs -> HasDisableReason ( extension_id , extensions : : disable_reason : : DISABLE_CUSTODIAN_APPROVAL_REQUIRED ) ) ;
 }
 SupervisedUserService * supervised_user_service ( ) {
 return SupervisedUserServiceFactory : : GetForProfile ( profile ( ) ) ;
 }
 static std : : string RequestId ( const std : : string & extension_id , const std : : string & version ) {
 return SupervisedUserService : : GetExtensionRequestId ( extension_id , base : : Version ( version ) ) ;
 }
 private : bool SetActive ( bool active ) override {
 return true ;
 }
 base : : FilePath base_path ( ) const {
 return data_dir ( ) . AppendASCII ( "permissions_increase" ) ;
 }
 base : : FilePath dir_path ( const std : : string & version ) const {
 return base_path ( ) . AppendASCII ( "v" + version ) ;
 }
 base : : FilePath pem_path ( ) const {
 return base_path ( ) . AppendASCII ( "permissions.pem" ) ;
 }
 base : : FieldTrialList field_trial_list_ ;
 base : : test : : ScopedFeatureList scoped_feature_list_ ;
 }
 ;
 class MockPermissionRequestCreator : public PermissionRequestCreator {
 public : MockPermissionRequestCreator ( ) {
 }
 ~ MockPermissionRequestCreator ( ) override {
 }
 bool IsEnabled ( ) const override {
 return true ;
 }
 void CreateURLAccessRequest ( const GURL & url_requested , const SuccessCallback & callback ) override {
 FAIL ( ) ;
 }
 MOCK_METHOD2 ( CreateExtensionInstallRequest , void ( const std : : string & id , const SupervisedUserService : : SuccessCallback & callback ) ) ;
 MOCK_METHOD2 ( CreateExtensionUpdateRequest , void ( const std : : string & id , const SupervisedUserService : : SuccessCallback & callback ) ) ;
 private : DISALLOW_COPY_AND_ASSIGN ( MockPermissionRequestCreator ) ;
 }
 ;
 TEST_F ( ExtensionServiceTestSupervised , InstallOnlyAllowedByCustodian ) {
 InitServices ( true ) ;
 InitSupervisedUserInitiatedExtensionInstallFeature ( false ) ;
 extensions : : util : : SetWasInstalledByCustodian ( good2048 , profile ( ) , true ) ;
 base : : FilePath path1 = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 base : : FilePath path2 = data_dir ( ) . AppendASCII ( "good2048.crx" ) ;
 const Extension * extensions [ ] = {
 InstallCRX ( path1 , INSTALL_FAILED ) , InstallCRX ( path2 , INSTALL_NEW ) }
 ;
 EXPECT_FALSE ( extensions [ 0 ] ) ;
 ASSERT_TRUE ( extensions [ 1 ] ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( extensions [ 1 ] -> id ( ) ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( extensions [ 1 ] -> id ( ) ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , DelegatedAndPreinstalledExtensionIsSUFirst ) {
 InitServices ( false ) ;
 InitSupervisedUserInitiatedExtensionInstallFeature ( false ) ;
 base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 const Extension * extension = InstallCRX ( path , INSTALL_NEW ) ;
 std : : string id = extension -> id ( ) ;
 const std : : string version ( "1.0.0.0" ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 profile ( ) -> AsTestingProfile ( ) -> SetSupervisedUserId ( supervised_users : : kChildAccountSUID ) ;
 EXPECT_FALSE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_disable_reasons ( extensions : : disable_reason : : DISABLE_NONE ) ;
 ext_specifics -> set_installed_by_custodian ( true ) ;
 ext_specifics -> set_version ( version ) ;
 SyncChangeList list = MakeSyncChangeList ( id , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_TRUE ( extensions : : util : : WasInstalledByCustodian ( id , profile ( ) ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , DelegatedAndPreinstalledExtensionSyncFirst ) {
 InitServices ( false ) ;
 InitSupervisedUserInitiatedExtensionInstallFeature ( false ) ;
 base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 const Extension * extension = InstallCRX ( path , INSTALL_NEW ) ;
 std : : string id = extension -> id ( ) ;
 const std : : string version ( "1.0.0.0" ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_disable_reasons ( extensions : : disable_reason : : DISABLE_NONE ) ;
 ext_specifics -> set_installed_by_custodian ( true ) ;
 ext_specifics -> set_version ( version ) ;
 SyncChangeList list = MakeSyncChangeList ( id , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_TRUE ( extensions : : util : : WasInstalledByCustodian ( id , profile ( ) ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , InstallAllowedByCustodianAndSupervisedUser ) {
 InitServices ( true ) ;
 InitSupervisedUserInitiatedExtensionInstallFeature ( true ) ;
 extensions : : util : : SetWasInstalledByCustodian ( good2048 , profile ( ) , true ) ;
 base : : FilePath path1 = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 base : : FilePath path2 = data_dir ( ) . AppendASCII ( "good2048.crx" ) ;
 const Extension * extensions [ ] = {
 InstallCRX ( path1 , INSTALL_WITHOUT_LOAD ) , InstallCRX ( path2 , INSTALL_NEW ) }
 ;
 ASSERT_TRUE ( extensions [ 0 ] ) ;
 ASSERT_TRUE ( extensions [ 1 ] ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . Contains ( extensions [ 0 ] -> id ( ) ) ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( extensions [ 0 ] -> id ( ) ) ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( extensions [ 1 ] -> id ( ) ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( extensions [ 1 ] -> id ( ) ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , PreinstalledExtensionWithSUInitiatedInstalls ) {
 InitServices ( false ) ;
 InitSupervisedUserInitiatedExtensionInstallFeature ( true ) ;
 base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 const Extension * extension = InstallCRX ( path , INSTALL_NEW ) ;
 std : : string id = extension -> id ( ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 MockPermissionRequestCreator * creator = new MockPermissionRequestCreator ;
 supervised_user_service ( ) -> AddPermissionRequestCreator ( base : : WrapUnique ( creator ) ) ;
 const std : : string version ( "1.0.0.0" ) ;
 EXPECT_CALL ( * creator , CreateExtensionInstallRequest ( RequestId ( good_crx , version ) , testing : : _ ) ) ;
 profile ( ) -> AsTestingProfile ( ) -> SetSupervisedUserId ( supervised_users : : kChildAccountSUID ) ;
 Mock : : VerifyAndClearExpectations ( creator ) ;
 CheckDisabledForCustodianApproval ( id ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , PreinstalledExtensionWithoutSUInitiatedInstalls ) {
 InitServices ( false ) ;
 InitSupervisedUserInitiatedExtensionInstallFeature ( false ) ;
 base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 const Extension * extension = InstallCRX ( path , INSTALL_NEW ) ;
 std : : string id = extension -> id ( ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 MockPermissionRequestCreator * creator = new MockPermissionRequestCreator ;
 supervised_user_service ( ) -> AddPermissionRequestCreator ( base : : WrapUnique ( creator ) ) ;
 const std : : string version ( "1.0.0.0" ) ;
 EXPECT_CALL ( * creator , CreateExtensionInstallRequest ( testing : : _ , testing : : _ ) ) . Times ( 0 ) ;
 profile ( ) -> AsTestingProfile ( ) -> SetSupervisedUserId ( supervised_users : : kChildAccountSUID ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_EQ ( extensions : : disable_reason : : DISABLE_BLOCKED_BY_POLICY , ExtensionPrefs : : Get ( profile ( ) ) -> GetDisableReasons ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , ExtensionApprovalBeforeInstallation ) {
 InitServices ( true ) ;
 InitSupervisedUserInitiatedExtensionInstallFeature ( true ) ;
 MockPermissionRequestCreator * creator = new MockPermissionRequestCreator ;
 supervised_user_service ( ) -> AddPermissionRequestCreator ( base : : WrapUnique ( creator ) ) ;
 std : : string id = good_crx ;
 std : : string version ( "1.0.0.0" ) ;
 SimulateCustodianApprovalChangeViaSync ( id , version , SyncChange : : ACTION_ADD ) ;
 base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 InstallCRX ( path , INSTALL_NEW ) ;
 EXPECT_CALL ( * creator , CreateExtensionInstallRequest ( testing : : _ , testing : : _ ) ) . Times ( 0 ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , UpdateWithoutPermissionIncrease ) {
 InitServices ( true ) ;
 std : : string id = InstallNoPermissionsTestExtension ( true ) ;
 std : : string version2 ( "2" ) ;
 UpdateNoPermissionsTestExtension ( id , version2 , ENABLED ) ;
 const Extension * extension = registry ( ) -> enabled_extensions ( ) . GetByID ( id ) ;
 ASSERT_TRUE ( extension ) ;
 EXPECT_EQ ( * extension -> version ( ) , base : : Version ( version2 ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , UpdateWithPermissionIncreaseApprovalOldVersion ) {
 InitServices ( true ) ;
 MockPermissionRequestCreator * creator = new MockPermissionRequestCreator ;
 supervised_user_service ( ) -> AddPermissionRequestCreator ( base : : WrapUnique ( creator ) ) ;
 const std : : string version1 ( "1" ) ;
 const std : : string version2 ( "2" ) ;
 std : : string id = InstallPermissionsTestExtension ( true ) ;
 EXPECT_CALL ( * creator , CreateExtensionUpdateRequest ( RequestId ( id , version2 ) , testing : : _ ) ) ;
 UpdatePermissionsTestExtension ( id , version2 , DISABLED ) ;
 Mock : : VerifyAndClearExpectations ( creator ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( id ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_disable_reasons ( extensions : : disable_reason : : DISABLE_NONE ) ;
 ext_specifics -> set_installed_by_custodian ( true ) ;
 ext_specifics -> set_version ( version1 ) ;
 EXPECT_CALL ( * creator , CreateExtensionUpdateRequest ( RequestId ( id , version2 ) , testing : : _ ) ) ;
 SyncChangeList list = MakeSyncChangeList ( id , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_FALSE ( extension_sync_service ( ) -> HasPendingReenable ( id , base : : Version ( version1 ) ) ) ;
 EXPECT_FALSE ( extension_sync_service ( ) -> HasPendingReenable ( id , base : : Version ( version2 ) ) ) ;
 Mock : : VerifyAndClearExpectations ( creator ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , UpdateWithPermissionIncreaseApprovalMatchingVersion ) {
 InitServices ( true ) ;
 MockPermissionRequestCreator * creator = new MockPermissionRequestCreator ;
 supervised_user_service ( ) -> AddPermissionRequestCreator ( base : : WrapUnique ( creator ) ) ;
 std : : string id = InstallPermissionsTestExtension ( true ) ;
 const std : : string version2 ( "2" ) ;
 EXPECT_CALL ( * creator , CreateExtensionUpdateRequest ( RequestId ( id , version2 ) , testing : : _ ) ) ;
 UpdatePermissionsTestExtension ( id , version2 , DISABLED ) ;
 Mock : : VerifyAndClearExpectations ( creator ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( id ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_disable_reasons ( extensions : : disable_reason : : DISABLE_NONE ) ;
 ext_specifics -> set_installed_by_custodian ( true ) ;
 ext_specifics -> set_version ( version2 ) ;
 SyncChangeList list = MakeSyncChangeList ( id , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , UpdateWithPermissionIncreaseApprovalNewVersion ) {
 InitServices ( true ) ;
 MockPermissionRequestCreator * creator = new MockPermissionRequestCreator ;
 supervised_user_service ( ) -> AddPermissionRequestCreator ( base : : WrapUnique ( creator ) ) ;
 std : : string id = InstallPermissionsTestExtension ( true ) ;
 const std : : string version2 ( "2" ) ;
 EXPECT_CALL ( * creator , CreateExtensionUpdateRequest ( RequestId ( id , version2 ) , testing : : _ ) ) ;
 UpdatePermissionsTestExtension ( id , version2 , DISABLED ) ;
 Mock : : VerifyAndClearExpectations ( creator ) ;
 const std : : string version3 ( "3" ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_enabled ( true ) ;
 ext_specifics -> set_disable_reasons ( extensions : : disable_reason : : DISABLE_NONE ) ;
 ext_specifics -> set_installed_by_custodian ( true ) ;
 ext_specifics -> set_version ( version3 ) ;
 EXPECT_CALL ( * creator , CreateExtensionUpdateRequest ( RequestId ( id , version3 ) , testing : : _ ) ) . Times ( 0 ) ;
 SyncChangeList list = MakeSyncChangeList ( id , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_FALSE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_TRUE ( extension_sync_service ( ) -> HasPendingReenable ( id , base : : Version ( version3 ) ) ) ;
 UpdatePermissionsTestExtension ( id , version3 , ENABLED ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , SupervisedUserInitiatedInstalls ) {
 InitSupervisedUserInitiatedExtensionInstallFeature ( true ) ;
 InitServices ( true ) ;
 MockPermissionRequestCreator * creator = new MockPermissionRequestCreator ;
 supervised_user_service ( ) -> AddPermissionRequestCreator ( base : : WrapUnique ( creator ) ) ;
 base : : FilePath path = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 std : : string version ( "1.0.0.0" ) ;
 EXPECT_CALL ( * creator , CreateExtensionInstallRequest ( RequestId ( good_crx , version ) , testing : : _ ) ) ;
 const Extension * extension = InstallCRX ( path , INSTALL_WITHOUT_LOAD ) ;
 ASSERT_TRUE ( extension ) ;
 ASSERT_EQ ( extension -> id ( ) , good_crx ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . Contains ( good_crx ) ) ;
 Mock : : VerifyAndClearExpectations ( creator ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( extension -> id ( ) ) ) ;
 SimulateCustodianApprovalChangeViaSync ( good_crx , version , SyncChange : : ACTION_ADD ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( good_crx ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( extension -> id ( ) ) ) ;
 SimulateCustodianApprovalChangeViaSync ( good_crx , version , SyncChange : : ACTION_DELETE ) ;
 EXPECT_TRUE ( registry ( ) -> disabled_extensions ( ) . Contains ( good_crx ) ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( extension -> id ( ) ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , UpdateSUInitiatedInstallWithoutPermissionIncrease ) {
 InitSupervisedUserInitiatedExtensionInstallFeature ( true ) ;
 InitServices ( true ) ;
 std : : string id = InstallNoPermissionsTestExtension ( false ) ;
 std : : string version1 ( "1" ) ;
 SimulateCustodianApprovalChangeViaSync ( id , version1 , SyncChange : : ACTION_ADD ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 std : : string version2 ( "2" ) ;
 UpdateNoPermissionsTestExtension ( id , version2 , ENABLED ) ;
 const Extension * extension = registry ( ) -> enabled_extensions ( ) . GetByID ( id ) ;
 ASSERT_TRUE ( extension ) ;
 EXPECT_EQ ( 1 , extension -> version ( ) -> CompareTo ( base : : Version ( version1 ) ) ) ;
 std : : string approved_version ;
 PrefService * pref_service = profile ( ) -> GetPrefs ( ) ;
 const base : : DictionaryValue * approved_extensions = pref_service -> GetDictionary ( prefs : : kSupervisedUserApprovedExtensions ) ;
 approved_extensions -> GetStringWithoutPathExpansion ( id , & approved_version ) ;
 EXPECT_EQ ( base : : Version ( approved_version ) , * extension -> version ( ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , UpdateSUInitiatedInstallWithPermissionIncrease ) {
 InitSupervisedUserInitiatedExtensionInstallFeature ( true ) ;
 InitServices ( true ) ;
 std : : string id = InstallPermissionsTestExtension ( false ) ;
 std : : string version1 ( "1" ) ;
 SimulateCustodianApprovalChangeViaSync ( id , version1 , SyncChange : : ACTION_ADD ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 std : : string version3 ( "3" ) ;
 UpdatePermissionsTestExtension ( id , version3 , DISABLED ) ;
 EXPECT_FALSE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_TRUE ( ExtensionPrefs : : Get ( profile ( ) ) -> HasDisableReason ( id , extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE ) ) ;
 std : : string version2 ( "2" ) ;
 SimulateCustodianApprovalChangeViaSync ( id , version2 , SyncChange : : ACTION_UPDATE ) ;
 EXPECT_FALSE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_TRUE ( ExtensionPrefs : : Get ( profile ( ) ) -> HasDisableReason ( id , extensions : : disable_reason : : DISABLE_PERMISSIONS_INCREASE ) ) ;
 EXPECT_TRUE ( ExtensionPrefs : : Get ( profile ( ) ) -> HasDisableReason ( id , extensions : : disable_reason : : DISABLE_CUSTODIAN_APPROVAL_REQUIRED ) ) ;
 EXPECT_TRUE ( IsPendingCustodianApproval ( id ) ) ;
 SimulateCustodianApprovalChangeViaSync ( id , version3 , SyncChange : : ACTION_UPDATE ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceTestSupervised , UpdateSUInitiatedInstallWithPermissionIncreaseApprovalArrivesFirst ) {
 InitSupervisedUserInitiatedExtensionInstallFeature ( true ) ;
 InitServices ( true ) ;
 std : : string id = InstallPermissionsTestExtension ( false ) ;
 std : : string version1 ( "1" ) ;
 SimulateCustodianApprovalChangeViaSync ( id , version1 , SyncChange : : ACTION_ADD ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 std : : string version2 ( "2" ) ;
 SimulateCustodianApprovalChangeViaSync ( id , version2 , SyncChange : : ACTION_UPDATE ) ;
 CheckDisabledForCustodianApproval ( id ) ;
 UpdatePermissionsTestExtension ( id , version2 , ENABLED ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( id ) ) ;
 EXPECT_FALSE ( IsPendingCustodianApproval ( id ) ) ;
 }
 TEST_F ( ExtensionServiceSyncTest , SyncUninstallByCustodianSkipsPolicy ) {
 InitializeEmptyExtensionService ( ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , base : : MakeUnique < syncer : : FakeSyncChangeProcessor > ( ) , base : : MakeUnique < syncer : : SyncErrorFactoryMock > ( ) ) ;
 extensions : : util : : SetWasInstalledByCustodian ( good2048 , profile ( ) , true ) ;
 base : : FilePath path1 = data_dir ( ) . AppendASCII ( "good.crx" ) ;
 base : : FilePath path2 = data_dir ( ) . AppendASCII ( "good2048.crx" ) ;
 const Extension * extensions [ ] = {
 InstallCRX ( path1 , INSTALL_NEW ) , InstallCRX ( path2 , INSTALL_NEW ) }
 ;
 extensions : : TestManagementPolicyProvider provider ( extensions : : TestManagementPolicyProvider : : PROHIBIT_MODIFY_STATUS ) ;
 ExtensionSystem : : Get ( browser_context ( ) ) -> management_policy ( ) -> RegisterProvider ( & provider ) ;
 SyncChangeList list ;
 for ( size_t i = 0 ;
 i < arraysize ( extensions ) ;
 i ++ ) {
 const std : : string & id = extensions [ i ] -> id ( ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_version ( "1.0" ) ;
 ext_specifics -> set_installed_by_custodian ( extensions : : util : : WasInstalledByCustodian ( id , profile ( ) ) ) ;
 syncer : : SyncData sync_data = syncer : : SyncData : : CreateLocalData ( id , "Name" , specifics ) ;
 list . push_back ( SyncChange ( FROM_HERE , SyncChange : : ACTION_DELETE , sync_data ) ) ;
 }
 std : : string extension_ids [ ] = {
 extensions [ 0 ] -> id ( ) , extensions [ 1 ] -> id ( ) }
 ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . Contains ( extension_ids [ 0 ] ) ) ;
 EXPECT_FALSE ( registry ( ) -> GenerateInstalledExtensionsSet ( ) -> Contains ( extension_ids [ 1 ] ) ) ;
 }
 TEST_F ( ExtensionServiceSyncTest , SyncExtensionHasAllhostsWithheld ) {
 InitializeEmptyExtensionService ( ) ;
 StartSyncing ( syncer : : EXTENSIONS ) ;
 const std : : string kName ( "extension" ) ;
 scoped_refptr < const Extension > extension = extensions : : ExtensionBuilder ( kName ) . SetLocation ( Manifest : : INTERNAL ) . AddPermission ( "*://*/*" ) . Build ( ) ;
 service ( ) -> AddExtension ( extension . get ( ) ) ;
 service ( ) -> GrantPermissionsAndEnableExtension ( extension . get ( ) ) ;
 const std : : string id = extension -> id ( ) ;
 EXPECT_TRUE ( registry ( ) -> enabled_extensions ( ) . GetByID ( id ) ) ;
 sync_pb : : EntitySpecifics specifics ;
 sync_pb : : ExtensionSpecifics * ext_specifics = specifics . mutable_extension ( ) ;
 ext_specifics -> set_id ( id ) ;
 ext_specifics -> set_name ( kName ) ;
 ext_specifics -> set_version ( "1.0" ) ;
 ext_specifics -> set_all_urls_enabled ( false ) ;
 ext_specifics -> set_enabled ( true ) ;
 SyncChangeList list = MakeSyncChangeList ( id , specifics , SyncChange : : ACTION_UPDATE ) ;
 extension_sync_service ( ) -> ProcessSyncChanges ( FROM_HERE , list ) ;
 const Extension * enabled_extension = registry ( ) -> enabled_extensions ( ) . GetByID ( id ) ;
 ASSERT_TRUE ( enabled_extension ) ;
 ScriptingPermissionsModifier modifier ( profile ( ) , enabled_extension ) ;
 EXPECT_FALSE ( modifier . IsAllowedOnAllUrls ( ) ) ;
 EXPECT_TRUE ( modifier . HasSetAllowedOnAllUrls ( ) ) ;
 }

 InitializeEmptyExtensionService ( ) ;
 service ( ) -> Init ( ) ;
 ASSERT_TRUE ( service ( ) -> is_ready ( ) ) ;
 const Extension * v1 = InstallCRX ( data_dir ( ) . AppendASCII ( "sync_datatypes" ) . AppendASCII ( "v1.crx" ) , INSTALL_NEW ) ;
 EXPECT_TRUE ( v1 -> is_app ( ) ) ;
 EXPECT_FALSE ( v1 -> is_extension ( ) ) ;
 std : : string id = v1 -> id ( ) ;
 StatefulChangeProcessor extensions_processor ( syncer : : ModelType : : EXTENSIONS ) ;
 StatefulChangeProcessor apps_processor ( syncer : : ModelType : : APPS ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , syncer : : SyncDataList ( ) , extensions_processor . GetWrapped ( ) , base : : WrapUnique ( new syncer : : SyncErrorFactoryMock ( ) ) ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : APPS , syncer : : SyncDataList ( ) , apps_processor . GetWrapped ( ) , base : : WrapUnique ( new syncer : : SyncErrorFactoryMock ( ) ) ) ;
 EXPECT_TRUE ( extensions_processor . changes ( ) . empty ( ) ) ;
 EXPECT_TRUE ( extensions_processor . data ( ) . empty ( ) ) ;
 EXPECT_EQ ( 1u , apps_processor . data ( ) . size ( ) ) ;
 ASSERT_EQ ( 1u , apps_processor . changes ( ) . size ( ) ) ;
 const SyncChange & app_change = apps_processor . changes ( ) [ 0 ] ;
 EXPECT_EQ ( SyncChange : : ACTION_ADD , app_change . change_type ( ) ) ;
 std : : unique_ptr < ExtensionSyncData > app_data = ExtensionSyncData : : CreateFromSyncData ( app_change . sync_data ( ) ) ;
 EXPECT_TRUE ( app_data -> is_app ( ) ) ;
 EXPECT_EQ ( id , app_data -> id ( ) ) ;
 EXPECT_EQ ( * v1 -> version ( ) , app_data -> version ( ) ) ;
 const Extension * v2 = InstallCRX ( data_dir ( ) . AppendASCII ( "sync_datatypes" ) . AppendASCII ( "v2.crx" ) , INSTALL_UPDATED ) ;
 EXPECT_FALSE ( v2 -> is_app ( ) ) ;
 EXPECT_TRUE ( v2 -> is_extension ( ) ) ;
 EXPECT_EQ ( id , v2 -> id ( ) ) ;
 ASSERT_EQ ( 1u , extensions_processor . changes ( ) . size ( ) ) ;
 const SyncChange & extension_change = extensions_processor . changes ( ) [ 0 ] ;
 EXPECT_EQ ( SyncChange : : ACTION_ADD , extension_change . change_type ( ) ) ;
 std : : unique_ptr < ExtensionSyncData > extension_data = ExtensionSyncData : : CreateFromSyncData ( extension_change . sync_data ( ) ) ;
 EXPECT_FALSE ( extension_data -> is_app ( ) ) ;
 EXPECT_EQ ( id , extension_data -> id ( ) ) ;
 EXPECT_EQ ( * v2 -> version ( ) , extension_data -> version ( ) ) ;
 syncer : : SyncDataList extensions_data = extensions_processor . GetAllSyncData ( syncer : : EXTENSIONS ) ;
 syncer : : SyncDataList apps_data = apps_processor . GetAllSyncData ( syncer : : APPS ) ;
 extension_sync_service ( ) -> StopSyncing ( syncer : : EXTENSIONS ) ;
 extension_sync_service ( ) -> StopSyncing ( syncer : : APPS ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : EXTENSIONS , extensions_data , extensions_processor . GetWrapped ( ) , base : : WrapUnique ( new syncer : : SyncErrorFactoryMock ( ) ) ) ;
 extension_sync_service ( ) -> MergeDataAndStartSyncing ( syncer : : APPS , apps_data , apps_processor . GetWrapped ( ) , base : : WrapUnique ( new syncer : : SyncErrorFactoryMock ( ) ) ) ;
 bool found_delete = false ;
 for ( const auto & change : apps_processor . changes ( ) ) {
 if ( change . change_type ( ) == SyncChange : : ACTION_DELETE ) {
 std : : unique_ptr < ExtensionSyncData > data = ExtensionSyncData : : CreateFromSyncChange ( change ) ;
 if ( data -> id ( ) == id ) {
 found_delete = true ;
 break ;
 }
 }
 }
 EXPECT_TRUE ( found_delete ) ;
 EXPECT_EQ ( 1u , extensions_processor . data ( ) . size ( ) ) ;
 EXPECT_TRUE ( apps_processor . data ( ) . empty ( ) ) ;
 }