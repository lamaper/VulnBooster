static bool host_supports_vmx ( void ) {
 uint32_t ecx , unused ;
 host_cpuid ( 1 , 0 , & unused , & unused , & ecx , & unused ) ;
 return ecx & CPUID_EXT_VMX ;
 }