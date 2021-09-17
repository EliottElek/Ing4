int main(){


    // display the process id
    printf("\nThis is the ID : %d\n",getpid());

    // simply use any exec call !
    char cmd[30];
    strcpy(cmd,"Firefox");
    execl("/bin/sh","sh","-c",cmd, (char) NULL);


    return 0;
}