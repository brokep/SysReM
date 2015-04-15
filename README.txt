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

4. Usage instruction:
	a. run "cmake ." and then "make" to compile the program
	b. run "./sysrem" with you chosen options:
        sysrem t n [-a] [-c] [-m] [-d] [-p] [-f [filename]]
    
        DESCRIPTION 
            Running sysrem without any arguments is eqiuvalent to running sysrem 1 10 -a.
            If arguemtns are specified, t and n must be specified fisrt. t is the interval 
            between measurements and n is the number of times meaurements are reported. 

        OPTIONS
            -a      reports all available measurements, equivalent to -c -d -m -p 

            -c      reports CPU utilization statistics

            -m      reports memory utilization statistics
    
            -d      reports disk utilization statistics
        
            -p      reports the top active process

            -f [filename]   sends the output of the program to filename(appends to the end if filename exists)
                            If filename not specified, default name "output" is used.





		
