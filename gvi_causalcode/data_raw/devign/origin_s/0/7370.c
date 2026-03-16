static void cpu_exit_tb_from_sighandler(CPUState *cpu, void *puc)

{


    struct ucontext *uc = puc;


    struct sigcontext *uc = puc;




    sigprocmask(SIG_SETMASK, (sigset_t *)&uc->uc_sigmask, NULL);


    sigprocmask(SIG_SETMASK, &uc->uc_sigmask, NULL);



    sigprocmask(SIG_SETMASK, &uc->sc_mask, NULL);




    cpu_resume_from_signal(cpu, NULL);

}
