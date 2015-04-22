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
			+ calculate cpu utilization for each process by the formular:
				%cpu = 100 * (delta (stime + utime) * number of cores)/ delta (cputime)
		- Finally, the list of processes are sorted according to cpu
		utilization and an abirtrary number of top processes are chosen for
		output display.

	b. CPU information:
        - CPU utuilization information is found in /proc/stats
        - Values from this file are recorded at two points in time and then compared 
        to determine how much of the CPU is being used to do certain things.

	c. Memory information:
        - Memory information is found in /proc/meminfo
        - Information is read from here and then reported directly

	d. Disk information:
        - Disk Staistics are found in /proc/diskstats
        - The disk thread first locates all relevant devices, those that start with "sd".
        - Next it reads the values associated with those devices at two points in time and 
        and determines the reads/s sectorsRead/s and writes etc...

3. Program Design and Structure:
	- Stat is a virtual base class that defines the public interface for those
	classes that measure and present statistic for individual component of
	the system. Stat has:
		+ measure(): calculates the difference in component statistics (such
		as process's ticks) over a period of time
		+ read(): return a string representing the information that is about
		to be printed out to the screen
	- Children classes of Stat class implement the measure() and read() methods
	specifically for each component, those includes:
		+ CPUStat
		+ DiskStat
		+ MemStat
		+ ProcStat
			a. Due to the fact that ProcStat needs to find and the statistics
			of n top processes, ProcMan class acts as the manager of each
			process to help ProcStat maintains its public interface to
			all processes.
	- The StatGen class acts as a factory class that generates a list of
	different Stat classes based on what the user wants to measure.
	- Reader class acts as a visitor class that visit all instances of Stat
	classes in the list and call the measure() of those classes to calculate
	the statisitc, and then call read() of those classes to print the result
	to the screen.

4. Usage instruction:
	a. run "cmake ." and then "make" to compile the program
	b. run "./sysrem" with your chosen options:
        SYNOPSIS
        sysrem t n [-a] [-c] [-m] [-d] [-p] [-n num] [-f [filename]]
    
        DESCRIPTION 
            Running sysrem without any arguments is equivalent to running sysrem 1 10 -a -n 4.
            If arguments are specified, t and n must be specified fisrt. 

        OPTIONS
			 t 			interval between measurements (mandatory)
			 n			number of times measurements are reported 
            -a          reports all available measurements, equivalent to -c -d -m -p 

            -c          reports CPU utilization statistics

            -m          reports memory utilization statistics
    
            -d          reports disk utilization statistics
        
            -p          reports the top active process

            -n num      sets the number of top processes to be reported. 

            -f [filename]   sends the output of the program to filename(appends to the end if filename exists)
                            If filename not specified, default name "output" is used.





		
