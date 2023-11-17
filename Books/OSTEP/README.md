# [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)

---
Book: [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)

Projects: <https://github.com/GuG-Shadamu/ostep-projects>

## Processes

- process: a running program
- mechanisms: low level methods or protocols
- context switch: stop&start a program
- scheduling policy
- a process can read or update the memory

- ### Process API

    1. create
    2. destroy
    3. wait
    4. control
    5. status

- ### Process Create

    1. load code and static data into memeory
    2. allocate memory for program's run-time **stack** (for example local variables)
    3. allocate memory for program's heap (e.g. dynamic variables)
    4. initialize I/O

## Virtualize CPU

- Limited direct execution via **Time Sharing**
- Two processor modes: **Kernal Mode** / **User Mode**
- **System Calls**: to execute a system call, a program will
  - execute **trap** instruction -> to kernal mode
  - perform system call
  - OS calls **return-from-trap** -> to user mode
  
  - There is a **trap table** contains **trap handlers**

## Scheduling

- Switching context from one process to another
- achieved by **Timer** (CPU control)
- FIFO / SJF (shortest job first) / Round Roubin

## Scheduler: Multi-Level Feedback Queue 

- multiple Queues with difference priority
- Different process within the same Queue has the same priority (Round Roubin within the same queue)
- The algorithm learns about the process

```
- Rule 1: If Priority(A) > Priority(B), A runs (B doesn’t).
- Rule 2: If Priority(A) = Priority(B), A & B run in round-robin fashion using the time slice (quantum length) of the given queue
- Rule 3: When a job enters the system, it is placed at the highest priority (the topmost queue).
- Rule 4: Once a job uses up its time allotment at a given level (regardless of how many times it has given up the CPU), its priority is reduced (i.e., it moves down one queue).
- Rule 5: After some time period S, move all the jobs in the system to the topmost queue.
```

## Scheduler: fair-share


- Resource Allocation Based on Shares: FSS assigns a certain number of shares to each user or group. These shares represent the proportion of resources that the user or group is entitled to receive.

- Dynamic Adjustment: The allocation of resources is dynamically adjusted based on the actual usage. If a user or group uses less than their allocated share, the unused portion can be temporarily reallocated to others.

- Priority Adjustment: The scheduler may adjust priorities based on various factors, such as the length of time a job has been waiting, to ensure fair access to resources over time.

- Fairness: The fundamental goal of FSS is to ensure that all users or groups receive a fair amount of resources over a given period, according to their assigned shares.

- Usage Tracking: The scheduler keeps track of the resources used by each user or group, which helps in ensuring the enforcement of the fair share policy.

- User Experience: By ensuring fair distribution, FSS aims to provide a consistent and predictable user experience, avoiding scenarios where some users monopolize resources at the expense of others.