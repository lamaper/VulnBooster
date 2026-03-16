QEMU_BUILD_BUG_ON ( XSAVE_BYTE_OFFSET ( word_offset ) != offsetof ( X86XSaveArea , field ) ) ASSERT_OFFSET ( XSAVE_FCW_FSW , legacy . fcw ) ;
 ASSERT_OFFSET ( XSAVE_FTW_FOP , legacy . ftw ) ;
 ASSERT_OFFSET ( XSAVE_CWD_RIP , legacy . fpip ) ;
 ASSERT_OFFSET ( XSAVE_CWD_RDP , legacy . fpdp ) ;
 ASSERT_OFFSET ( XSAVE_MXCSR , legacy . mxcsr ) ;
 ASSERT_OFFSET ( XSAVE_ST_SPACE , legacy . fpregs ) ;
 ASSERT_OFFSET ( XSAVE_XMM_SPACE , legacy . xmm_regs ) ;
 ASSERT_OFFSET ( XSAVE_XSTATE_BV , header . xstate_bv ) ;
 ASSERT_OFFSET ( XSAVE_YMMH_SPACE , avx_state ) ;
 ASSERT_OFFSET ( XSAVE_BNDREGS , bndreg_state ) ;
 ASSERT_OFFSET ( XSAVE_BNDCSR , bndcsr_state ) ;
 ASSERT_OFFSET ( XSAVE_OPMASK , opmask_state ) ;
 ASSERT_OFFSET ( XSAVE_ZMM_Hi256 , zmm_hi256_state ) ;
 ASSERT_OFFSET ( XSAVE_Hi16_ZMM , hi16_zmm_state ) ;
 ASSERT_OFFSET ( XSAVE_PKRU , pkru_state )