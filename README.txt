SYSTEM RESOURCE MONITOR (SysReM)
Team members:
	- Jamison Gray (grayjm3)
	- Hoang Ly (lyhp)

1. Introduction:
SysReM aims to replicate the functionality of "sar" and "top" command.
The program collects and reports customized system activity information.

2. Description:
Below is the implementation SysReM's functionality:
	a. Processes information:
		- The program finds all current running processes listed by their
		pids in the folder "/proc/"
		- Then the program calculate the cpu utilization of each process
		by 
			+ going into "/proc/[pid]/stat" and collect the following number:
				i.(14) Amount of time that this process has been scheduled
				in user mode, measured in clock ticks
				ii.(15) Amount of time that this process has been scheduled
				in kernel mode, measured in clock ticks
			+ calculate cpu utilization based on those values.
		- Finally, the list of processes are sorted according to cpu
		utilization and an abirtrary number of top processes are chosen for
		output display.

	b. CPU information:

	c. Memory information:

	d. Disk information:

3. Program Design and Structure:

4. Usage instruction:
	a. run "cmake ." and then "make" to compile the program
	b. run "./sysrem" with you chosen options:
		-h
		