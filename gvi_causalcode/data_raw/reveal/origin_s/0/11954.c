static bfd_boolean srec_set_arch_mach ( bfd * abfd , enum bfd_architecture arch , unsigned long mach ) {
 if ( arch != bfd_arch_unknown ) return bfd_default_set_arch_mach ( abfd , arch , mach ) ;
 abfd -> arch_info = & bfd_default_arch_struct ;
 return TRUE ;
 }