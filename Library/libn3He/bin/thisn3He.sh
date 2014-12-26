n3HeBIN=$(dirname $BASH_ARGV[0])
n3HeROOT=$(cd $n3HeBIN/..;pwd)

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$n3HeROOT/lib
export PATH=$PATH:$n3HeROOT/bin


