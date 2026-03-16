TEST_F ( NativeBackendLibsecretTest , PSLMatchingDisabledForNonHTMLForms ) {
 CheckMatchingWithScheme ( PasswordForm : : SCHEME_BASIC ) ;
 CheckMatchingWithScheme ( PasswordForm : : SCHEME_DIGEST ) ;
 CheckMatchingWithScheme ( PasswordForm : : SCHEME_OTHER ) ;
 }