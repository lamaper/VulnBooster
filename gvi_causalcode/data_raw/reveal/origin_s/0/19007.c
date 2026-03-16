static void DangerousDownloadValidated ( JNIEnv * env , const JavaParamRef < jclass > & clazz , const JavaParamRef < jobject > & tab , jint download_id , jboolean accept ) {
 TabAndroid * tab_android = TabAndroid : : GetNativeTab ( env , tab ) ;
 DownloadControllerAndroid : : Get ( ) -> DangerousDownloadValidated ( tab_android -> web_contents ( ) , download_id , accept ) ;
 }