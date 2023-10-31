PART 1: NICE
    nice system call:
        usage: nice <pid> <nice value to increment/decrement>
        this will increment the nice value of the process with the given pid with the given value.
        to decrease the value, pass the argument as a negative number.
        maximum possible nice value = 19; minimum possible nice value = -20
        nice values lower than or greater than the mentioned bounds will be set to their respective bound.

    ps system call:
        usage: ps
        this will display all existing processes and a few of their attributes in the process table.

    test utility (nicetest):
        advisory: child will NOT inherit the nice value of the parent and will be initialized with nice = 0.
        usage: nicetest
        this will create a dummy process and its child, i.e., 2 dummy processes will be created.
        the child will find the number of prime numbers under 99999 to consume CPU time.
        the processes will exist for long enough to update their nice values multiple times.
        many processes can be created together by letting multiple nicetest processes run in the background.
        example usage: nicetest &; nicetest &; nicetest &
            this will create 6 dummy processes and we can use the nice system call to change their nice values.
            changed nice values can be verified with the ps system call

PART 2: RANDOM NUMBER GENERATOR
    random system call:
        usage: random <max value>
        this will generate and return a random value between 0 and the provided max value (inclusive).
        it is not truly random. it is pseudo-random, i.e., the sequence of generated numbers will repeat.

    test utility (randtest):
        usage: randtest <max value>
        this will use the random system call to generate 1000 random numbers and return their min, max and mean.
        can be used to verify that the random numbers generated are not skewed and are reasonably random.
        if the min is relatively close to the lower bound, max is relatively close to upper bound, and mean is 
        relatively close to (upper - lower) / 2, we can say that the random function generates reasonably random values

PART 3: SCHEDULER
    advisory: Make sure to use the -w flag for grep when finding for nice = -1, -2 or 1. 
              Otherwise the result will be incorrect since -1 will include values for -10, -11, -12, -13 and so on, 
              -2 will include values for -20, and 1 will include values for 10, 11, 12,13 and so on.
              Keep in mind that child will NOT inherit the nice value of the parent and will be initialized with nice = 0.
    lottery scheduling:
        usage: to enable lottery scheduling, pass -DLOTTERY during compilation of proc.c
               this can be done by making sure line 81 in makefile is uncommented (CFLAGS += -DLOTTERY).
               doing this will define LOTTERY in each compiled file including proc.c and enable lottery scheduling.
               otherwise the default round robin scheduling will be used.
        processes will hold a certain number of tickets based on their nice value and a random number will be generated.
        a process will be chosen for execution if it holds a ticket with the random number.
        the number of tickets will determine the probability of the process to be chosen for execution by the scheduler.
        the number of tickets held will be inversely proportional to the nice value.
        for calculating the number of tickets, we will subtract the nice value from 20 and multiply the result by 10.

    testing utilities:
        basic testing (lotterytestv1):
            this will verify that the processes with the least nice value are executed the most number of times and vice versa.
            usage: lotterytestv1
                   this will create 5 processes with different nice values.
                   they will print identifying information when they complete a loop 10000 times.
                   this will help us identify which processes got to run the most and vice versa.
            example usage: redirect the output of make qemu-nox to a text file (lotterytestv1out.txt in this case).
                           execute lotterytestv1 and let it run for sometime.
                           terminate qemu and see how much each process got to execute using grep and wc
                           for e.g., cat lotterytestv1out.txt | grep 'LEAST NICE' | wc
                           this will give wc of how much the process with least nice value printed.
                           do the same for other processes to compare how their nice values affect their executions.
            
        testing if processes with highest nice value get to run (lotterytestv2):
            this will verify that even the processes with the max possible nice value get some CPU time.
            usage: lotterytestv2
                   this will create 3 child processes with different nice values.
                   one process will have nice = -20, one will have 0, and one will have nice = 19.
                   they will print identifying information when they complete a loop 10000 times.
            example usage: redirect the output of make qemu-nox to a text file (lotterytestv2out.txt in this case).
                           execute lotterytestv2 and let it run for sometime.
                           terminate qemu and see how much each process got to execute using grep and wc
                           for e.g., cat lotterytestv2out.txt | grep 'MOST NICE' | wc
                           this will give wc of how much the process with most nice value printed.
                           if wc gives us more than 0 lines, it means that the process with max nice value got to execute.
                           do the same for other processes to compare how their nice values affect their executions.

        load testing when processes have different nice values (lotterytestv3):
            this will load test the scheduler when it has to deal with many processes - each with different nice values.
            usage: lotterytestv3
                   this will create 40 child processes with every possible nice value (-20 to 19).
                   they will print identifying information when they complete a loop 10000 times.
            example usage: redirect the output of make qemu-nox to a text file (lotterytestv3out.txt in this case).
                           execute lotterytestv3 and let it run for sometime.
                           terminate qemu and see how much each process got to execute using grep and wc
                           for eg. cat lotterytestv3out.txt | grep 'nice = -20' | wc
                           this will give wc of how much the process with nice = -20 printed.
                           repeat for different nice values and observe how lines of wc decrease when nice increases.

        load testing when processes have same nice values(lotterytestv4):
            this will load test the scheduler when it ahs to deal with many processes - each with same nice value (default = 0).
            usage: lotterytestv4
                   this will create 10 child processes. nice values will not be touched and all will have default nice value = 0.
                   they will print identifying information when they complete a loop 10000 times.
            example usage: redirect the output of make qemu-nox to a text file (lotterytestv4out.txt in this case).
                           execute lotterytestv4 and let it run for sometime.
                           terminate qemu and see how much each process got to execute using grep and wc
                           for eg. cat lotterytestv4out.txt | grep 8 | wc
                           this will give wc of how much the process with pid = 8 printed.
                           repeat for different processes and observe how lines of wc remain similar.

        dynamic nice value testing:
            this will check if decreasing nice value of a process after sometime increases how much it gets chosen for execution.
            usage: lotterytestv5
                   this will create 3 child processes with different nice values.
                   one process will have nice = -20, one will have 0, and one will have nice = 19.
                   when process with nice = 19 executes the loop 50000 times, its nice value is decremented by 30.
                   they will print identifying information when they complete a loop 10000 times.
            example usage: redirect the output of make qemu-nox to a text file (lotterytestv5out.txt in this case).
                           execute lotterytestv5 and let it run for sometime.
                           terminate qemu and see how much each process got to execute using sed, grep, and wc
                           for e.g., sed '/Decreasing/q' lotterytestv5out.txt | grep TEST | wc
                           this will give wc of how much the test process printed before its nice value was decremented.
                           also, awk '/Decreasing/,0' lotterytestv5out.txt | grep TEST | wc
                           this will give wc of how much the test process printed after its nice vlaue was decremented.
                           both commands them can be used for other 2 processes to estimate how much CPU time they got.
                           compare assigned CPU time before and after the nice value gets decremented.
                           observe how test processes starts getting more CPU time after nice value is decremented.
                           

    