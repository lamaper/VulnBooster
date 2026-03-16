static void LaunchPermissionUpdateInfoBar ( JNIEnv * env , const JavaParamRef < jclass > & clazz , const JavaParamRef < jobject > & tab , const JavaParamRef < jstring > & jpermission , jlong callback_id ) {
 TabAndroid * tab_android = TabAndroid : : GetNativeTab ( env , tab ) ;
 std : : string permission = base : : android : : ConvertJavaStringToUTF8 ( env , jpermission ) ;
 scoped_ptr < DownloadControllerAndroid : : AcquireFileAccessPermissionCallback > cb ( reinterpret_cast < DownloadControllerAndroid : : AcquireFileAccessPermissionCallback * > ( callback_id ) ) ;
 std : : vector < std : : string > permissions ;
 permissions . push_back ( permission ) ;
 PermissionUpdateInfoBarDelegate : : Create ( tab_android -> web_contents ( ) , permissions , IDS_MISSING_STORAGE_PERMISSION_DOWNLOAD_EDUCATION_TEXT , * cb ) ;
 }