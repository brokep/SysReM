FINAL PROJECT PROPOSAL
Jamison Gray and Hoang Ly
Description:
 	System Resource Monitor (SysReM)
Identify the currently available resources in the system and periodically report the activity on the screen.
–Take as input the polling interval and the number of times the activity should be reported.
–Consider the following resources
•CPU utilization
•Memory (including swap utilization)
•Disk
•List N most active processes (activity defined by the total CPU utilization). For those processes,
–Report CPU utilization
–Number of threads
–Whether they are CPU bound or IO Bound


2. Solution Approach:
Initially work with the sar utility to get all resource information available from that. 
After having a framework to handle and display this information appropriately, add more utilities to report any more useful resource information.

3. Language used: We will be using C++ for out project.

4. Milestones:
March 24 – Submit a report about the design. Ideally have framework to collect and store data from sar utility at this point.
April 9 – status update and submit a set of slides describing what you have done till now. Have some information being displayed at this point. Basic form of the final program completed.
April 12-13 - Add final touches to resource display and add any additional resource stats	 
April 21 – final report and presentation


