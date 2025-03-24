cmake_minimum_required(VERSION 3.16)

# Set custom partition table
set(PARTITION_TABLE_CSV_FILE "partitions.csv")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(hardpanel) 