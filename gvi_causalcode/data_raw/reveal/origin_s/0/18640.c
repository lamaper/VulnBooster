TEST_F ( AccountChooserDialogAndroidTest , CheckHistogramsReportingOnceAccountViaOnAccountClick ) {
 base : : HistogramTester histogram_tester ;
 AccountChooserDialogAndroid * dialog = CreateDialogOneAccount ( ) ;
 dialog -> OnCredentialClicked ( base : : android : : AttachCurrentThread ( ) , nullptr , , static_cast < int > ( password_manager : : CredentialType : : CREDENTIAL_TYPE_PASSWORD ) , false ) ;
 dialog -> Destroy ( base : : android : : AttachCurrentThread ( ) , nullptr ) ;
 histogram_tester . ExpectUniqueSample ( "PasswordManager.AccountChooserDialog" , password_manager : : metrics_util : : ACCOUNT_CHOOSER_CREDENTIAL_CHOSEN , 1 ) ;
 histogram_tester . ExpectUniqueSample ( "PasswordManager.AccountChooserDialogOneAccount" , password_manager : : metrics_util : : ACCOUNT_CHOOSER_CREDENTIAL_CHOSEN , 1 ) ;
 histogram_tester . ExpectTotalCount ( "PasswordManager.AccountChooserDialogMultipleAccounts" , 0 ) ;
 }