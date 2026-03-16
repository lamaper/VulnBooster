TEST_P ( PasswordStoreXTest , Notifications ) {
 std : : unique_ptr < password_manager : : LoginDatabase > login_db ( new password_manager : : LoginDatabase ( test_login_db_file_path ( ) ) ) ;
 scoped_refptr < PasswordStoreX > store ( new PasswordStoreX ( base : : ThreadTaskRunnerHandle : : Get ( ) , base : : ThreadTaskRunnerHandle : : Get ( ) , std : : move ( login_db ) , GetBackend ( GetParam ( ) ) ) ) ;
 store -> Init ( syncer : : SyncableService : : StartSyncFlare ( ) ) ;
 password_manager : : PasswordFormData form_data = {
 PasswordForm : : SCHEME_HTML , "http://bar.example.com" , "http://bar.example.com/origin" , "http://bar.example.com/action" , L"submit_element" , L"username_element" , L"password_element" , L"username_value" , L"password_value" , true , false , 1 }
 ;
 std : : unique_ptr < PasswordForm > form = CreatePasswordFormFromDataForTesting ( form_data ) ;
 password_manager : : MockPasswordStoreObserver observer ;
 store -> AddObserver ( & observer ) ;
 const PasswordStoreChange expected_add_changes [ ] = {
 PasswordStoreChange ( PasswordStoreChange : : ADD , * form ) , }
 ;
 EXPECT_CALL ( observer , OnLoginsChanged ( ElementsAreArray ( expected_add_changes ) ) ) ;
 store -> AddLogin ( * form ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 form -> password_value = base : : ASCIIToUTF16 ( "a different password" ) ;
 const PasswordStoreChange expected_update_changes [ ] = {
 PasswordStoreChange ( PasswordStoreChange : : UPDATE , * form ) , }
 ;
 EXPECT_CALL ( observer , OnLoginsChanged ( ElementsAreArray ( expected_update_changes ) ) ) ;
 store -> UpdateLogin ( * form ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 const PasswordStoreChange expected_delete_changes [ ] = {
 PasswordStoreChange ( PasswordStoreChange : : REMOVE , * form ) , }
 ;
 EXPECT_CALL ( observer , OnLoginsChanged ( ElementsAreArray ( expected_delete_changes ) ) ) ;
 store -> RemoveLogin ( * form ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 store -> RemoveObserver ( & observer ) ;
 store -> ShutdownOnUIThread ( ) ;
 }