int qemu_pipe(int pipefd[2])

{

    int ret;


    ret = pipe2(pipefd, O_CLOEXEC);


    ret = pipe(pipefd);

    if (ret == 0) {

        qemu_set_cloexec(pipefd[0]);

        qemu_set_cloexec(pipefd[1]);

    }




    return ret;

}
