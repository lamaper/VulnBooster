static bool host_tsx_blacklisted ( void ) {
 int family , model , stepping ;
 char vendor [ CPUID_VENDOR_SZ + 1 ] ;
 host_vendor_fms ( vendor , & family , & model , & stepping ) ;
 return ! strcmp ( vendor , CPUID_VENDOR_INTEL ) && ( family == 6 ) && ( ( model == 63 && stepping < 4 ) || model == 60 || model == 69 || model == 70 ) ;
 }