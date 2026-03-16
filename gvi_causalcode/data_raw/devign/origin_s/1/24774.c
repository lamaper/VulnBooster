void kvm_setup_guest_memory(void *start, size_t size)

{

    if (!kvm_has_sync_mmu()) {


        int ret = madvise(start, size, MADV_DONTFORK);



        if (ret) {

            perror("madvice");

            exit(1);

        }


        fprintf(stderr,

                "Need MADV_DONTFORK in absence of synchronous KVM MMU\n");

        exit(1);


    }

}
