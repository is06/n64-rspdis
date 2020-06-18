cmake_minimum_required(VERSION 3.10)
project(rspdis)
add_executable(rspdis rspdis.c base.c cop0.c regimm.c special.c vector.c)
