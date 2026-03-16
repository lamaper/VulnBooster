void ResolveNTFunctionPtr ( const char * name , void * ptr ) {
 static volatile HMODULE ntdll = NULL ;
 if ( ! ntdll ) {
 HMODULE ntdll_local = : : GetModuleHandle ( sandbox : : kNtdllName ) ;
 base : : win : : PEImage ntdll_peimage ( ntdll_local ) ;
 CHECK_NT ( ntdll_peimage . VerifyMagic ( ) ) ;
 : : InterlockedCompareExchangePointer ( reinterpret_cast < PVOID volatile * > ( & ntdll ) , ntdll_local , NULL ) ;
 }
 CHECK_NT ( ntdll ) ;
 FARPROC * function_ptr = reinterpret_cast < FARPROC * > ( ptr ) ;
 * function_ptr = : : GetProcAddress ( ntdll , name ) ;
 CHECK_NT ( * function_ptr ) ;
 }