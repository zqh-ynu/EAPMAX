The HPC systems have 360 machines and the machines are evenly distributed.  There are 30 task types.  The ETC and EPC data was generated from benchmarks as much as possible.

Files (all data is in CSV format):

Input files:
ETC.csv -- estimated time to compute matrix [s] 
EPC.csv -- estimate power consumption matrix [W]  
MPT.csv -- number of machines of each type
TPT.csv -- number of tasks of each type

Results:
"no_idle" directory is the results without any idle power and "10% idle" is with 10% idle power.

lower_bound.csv -- lower bound to the Pareto front (energy [j], makespan [s])
round_near.csv -- integer solution to the Pareto front (energy [j], makespan [s])
full_allocation.csv -- upper bound to the Pareto front (energy [j], makespan [s])
priceSweep.csv -- results for sweeping the profit ratio

feasible_region.csv -- the points that makeup the feasible region.
