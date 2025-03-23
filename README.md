# 3D Subtensor Sum

This project implements a C++ program to count the number of sub-tensors (sub-cubes) within a 3D tensor whose element sums are equal to a specified target value. It uses an optimized 3D prefix sum approach to calculate subregion sums efficiently.

## Overview

Given a sparse 3D tensor representation and a target sum, the program reads the input from a file, constructs the tensor, and computes the number of sub-tensors that match the target sum. This problem is particularly useful in scientific computing, volumetric data analysis, and algorithm research.

## Features

- Efficient sub-tensor sum calculations using 3D prefix sums
- Support for sparse tensor input format
- Floating-point comparison tolerance with epsilon margin
- Simple command-line usage

## Input Format

The input is read from a `.txt` file and should follow the format below:

- First line: Dimensions of the 3D tensor
- Second line: Target sum
- Subsequent lines: Non-zero tensor entries (`x y z value`)

## How to Build

Use a C++ compiler such as `g++`. From the root directory of the project:

```bash
g++ src/main.cpp -o build/main
