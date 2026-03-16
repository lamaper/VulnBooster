static jboolean ShouldUseSmartLockBranding ( JNIEnv * env , const JavaParamRef < jclass > & ) {
 const ProfileSyncService * sync_service = ProfileSyncServiceFactory : : GetForProfile ( ProfileManager : : GetLastUsedProfile ( ) ) ;
 return password_bubble_experiment : : IsSmartLockBrandingEnabled ( sync_service ) ;
 }