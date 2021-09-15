int i = 5;
if (fork() == 0) {
// I’m the child
i++;
} else {
// I’m the parent
sleep(3); // sleep for 3 seconds
printf("%d\n", i); // what happens here ?? Explain
}
