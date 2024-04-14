############################################################
# this file should be called sortrace.sh
# it must have execute privilege set to run
# run it as a background task like this:
#
#      $ sortrace.sh > sortrace.log &    # run in the background
#
# using > will overwrite any existing file while >> will add to any existing file
############################################################
echo "=======Start======="
date
whoami
echo My machine has this many processors
nproc				# this is for Windows machines
# sysctl -n hw. Ncpu	# this is for Mac machines
echo Generating 1000000 random numbers
sleep 1
./generate 1000000 1000000 9999999
sleep 1
echo Starting system sort
sleep 1
{ time sort -n numbers.dat > systemsort.out; } 2>> sortrace.log
sleep 1
echo Starting my sort
sleep 1
{ time ./bucketList numbers.dat bucketList.out 600; } 2>> sortrace.log
sleep 1
echo "List file details (ls -l)"    # must use quotes to protect ( )
ls -l systemsort.out
ls -l bucketList.out
echo "List word count details (wc)" # must use quotes to protect ( )
wc systemsort.out bucketList.out
echo Comparing systemsort.out to bucketList.out
diff systemsort.out bucketList.out 2>> sortrace.log
echo All done
echo "=======End======="
date
