int xmlThrDefKeepBlanksDefaultValue ( int v ) {
 int ret ;
 xmlMutexLock ( xmlThrDefMutex ) ;
 ret = xmlKeepBlanksDefaultValueThrDef ;
 xmlKeepBlanksDefaultValueThrDef = v ;
 xmlMutexUnlock ( xmlThrDefMutex ) ;
 return ret ;
 }