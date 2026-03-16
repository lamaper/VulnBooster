TEST_P ( PasswordStoreXTest , NativeMigration ) {
 ScopedVector < autofill : : PasswordForm > expected_autofillable ;
 InitExpectedForms ( true , 50 , & expected_autofillable ) ;
 ScopedVector < autofill : : PasswordForm > expected_blacklisted ;
 InitExpectedForms ( false , 50 , & expected_blacklisted ) ;
 const base : : FilePath login_db_file = test_login_db_file_path ( ) ;
 std : : unique_ptr < password_manager : : LoginDatabase > login_db ( new password_manager : : LoginDatabase ( login_db_file ) ) ;
 ASSERT_TRUE ( login_db -> Init ( ) ) ;
 base : : File : : Info db_file_start_info ;
 ASSERT_TRUE ( base : : GetFileInfo ( login_db_file , & db_file_start_info ) ) ;
 for ( const autofill : : PasswordForm * form : expected_autofillable ) {
 EXPECT_EQ ( AddChangeForForm ( * form ) , login_db -> AddLogin ( * form ) ) ;
 }
 for ( const autofill : : PasswordForm * form : expected_blacklisted ) {
 EXPECT_EQ ( AddChangeForForm ( * form ) , login_db -> AddLogin ( * form ) ) ;
 }
 base : : File : : Info db_file_full_info ;
 ASSERT_TRUE ( base : : GetFileInfo ( login_db_file , & db_file_full_info ) ) ;
 EXPECT_GT ( db_file_full_info . size , db_file_start_info . size ) ;
 login_db . reset ( new password_manager : : LoginDatabase ( login_db_file ) ) ;
 scoped_refptr < PasswordStoreX > store ( new PasswordStoreX ( base : : ThreadTaskRunnerHandle : : Get ( ) , base : : ThreadTaskRunnerHandle : : Get ( ) , std : : move ( login_db ) , GetBackend ( GetParam ( ) ) ) ) ;
 store -> Init ( syncer : : SyncableService : : StartSyncFlare ( ) ) ;
 MockPasswordStoreConsumer consumer ;
 EXPECT_CALL ( consumer , OnGetPasswordStoreResultsConstRef ( UnorderedPasswordFormElementsAre ( expected_autofillable . get ( ) ) ) ) ;
 store -> GetAutofillableLogins ( & consumer ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 EXPECT_CALL ( consumer , OnGetPasswordStoreResultsConstRef ( UnorderedPasswordFormElementsAre ( expected_blacklisted . get ( ) ) ) ) ;
 store -> GetBlacklistLogins ( & consumer ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 MockLoginDatabaseReturn ld_return ;
 if ( GetParam ( ) == WORKING_BACKEND ) {
 EXPECT_CALL ( ld_return , OnLoginDatabaseQueryDone ( IsEmpty ( ) ) ) ;
 }
 else {
 EXPECT_CALL ( ld_return , OnLoginDatabaseQueryDone ( UnorderedPasswordFormElementsAre ( expected_autofillable . get ( ) ) ) ) ;
 }
 LoginDatabaseQueryCallback ( store -> login_db ( ) , true , & ld_return ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 if ( GetParam ( ) == WORKING_BACKEND ) {
 EXPECT_CALL ( ld_return , OnLoginDatabaseQueryDone ( IsEmpty ( ) ) ) ;
 }
 else {
 EXPECT_CALL ( ld_return , OnLoginDatabaseQueryDone ( UnorderedPasswordFormElementsAre ( expected_blacklisted . get ( ) ) ) ) ;
 }
 LoginDatabaseQueryCallback ( store -> login_db ( ) , false , & ld_return ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 if ( GetParam ( ) == WORKING_BACKEND ) {
 base : : File : : Info db_file_end_info ;
 ASSERT_TRUE ( base : : GetFileInfo ( login_db_file , & db_file_end_info ) ) ;
 EXPECT_EQ ( db_file_start_info . size , db_file_end_info . size ) ;
 }
 store -> ShutdownOnUIThread ( ) ;
 }