static jlong Init ( JNIEnv * env , const JavaParamRef < jobject > & obj ) {
 PasswordUIViewAndroid * controller = new PasswordUIViewAndroid ( env , obj ) ;
 return reinterpret_cast < intptr_t > ( controller ) ;
 }