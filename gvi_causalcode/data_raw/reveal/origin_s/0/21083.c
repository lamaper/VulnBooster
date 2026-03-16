static jboolean IsDownloadDangerous ( JNIEnv * env , const JavaParamRef < jclass > & clazz , const JavaParamRef < jstring > & filename ) {
 base : : FilePath path ( base : : android : : ConvertJavaStringToUTF8 ( env , filename ) ) ;
 return download_util : : GetFileDangerLevel ( path ) != download_util : : NOT_DANGEROUS ;
 }