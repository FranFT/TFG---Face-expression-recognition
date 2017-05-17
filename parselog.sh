#! /bin/bash
python caffe-master/tools/extra/parse_log.py $1 .

gnuplot -persist gnuplot_commands
