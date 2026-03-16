static void OnLocationSettingsDialogOutcome ( JNIEnv * env , const base : : android : : JavaParamRef < jclass > & jcaller , jlong callback_ptr , int result ) {
 auto * callback = reinterpret_cast < LocationSettingsDialogOutcomeCallback * > ( callback_ptr ) ;
 std : : move ( * callback ) . Run ( static_cast < LocationSettingsDialogOutcome > ( result ) ) ;
 delete callback ;
 }