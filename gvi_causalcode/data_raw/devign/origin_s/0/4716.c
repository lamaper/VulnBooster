setup_return(CPUState *env, struct emulated_sigaction *ka,

	     abi_ulong *rc, void *frame, int usig)

{

	abi_ulong handler = (abi_ulong)ka->sa._sa_handler;

	abi_ulong retcode;

	int thumb = 0;



	abi_ulong cpsr = env->cpsr;



	 

	if (ka->sa.sa_flags & SA_THIRTYTWO)

		cpsr = (cpsr & ~MODE_MASK) | USR_MODE;


	if (elf_hwcap & HWCAP_THUMB) {

		 

		thumb = handler & 1;



		if (thumb)

			cpsr |= T_BIT;

		else

			cpsr &= ~T_BIT;

	}






	if (ka->sa.sa_flags & TARGET_SA_RESTORER) {

		retcode = (abi_ulong)ka->sa.sa_restorer;

	} else {

		unsigned int idx = thumb;



		if (ka->sa.sa_flags & TARGET_SA_SIGINFO)

			idx += 2;



		if (__put_user(retcodes[idx], rc))

			return 1;


		flush_icache_range((abi_ulong)rc,

				   (abi_ulong)(rc + 1));


		retcode = ((abi_ulong)rc) + thumb;

	}



	env->regs[0] = usig;

	env->regs[13] = h2g(frame);

	env->regs[14] = retcode;

	env->regs[15] = handler & (thumb ? ~1 : ~3);



	env->cpsr = cpsr;





	return 0;

}
