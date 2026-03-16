restore_fpu_state(CPUSPARCState *env, qemu_siginfo_fpu_t *fpu)

{

        int err;



        if (current->flags & PF_USEDFPU)

                regs->psr &= ~PSR_EF;


        if (current == last_task_used_math) {

                last_task_used_math = 0;

                regs->psr &= ~PSR_EF;

        }


        current->used_math = 1;

        current->flags &= ~PF_USEDFPU;



        if (verify_area (VERIFY_READ, fpu, sizeof(*fpu)))

                return -EFAULT;



         

        err = __copy_from_user(&env->fpr[0], &fpu->si_float_regs[0],

	                             (sizeof(unsigned long) * 32));


        err |= __get_user(env->fsr, &fpu->si_fsr);


        err |= __get_user(current->thread.fpqdepth, &fpu->si_fpqdepth);

        if (current->thread.fpqdepth != 0)

                err |= __copy_from_user(&current->thread.fpqueue[0],

                                        &fpu->si_fpqueue[0],

                                        ((sizeof(unsigned long) +

                                        (sizeof(unsigned long *)))*16));


        return err;

}
