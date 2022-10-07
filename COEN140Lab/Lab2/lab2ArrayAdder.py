# Class: COEN 140 Lab Machine Learning/Data Mining
# Name: Matthew Davenport
# Date: 9/25/2022
# Title: Lab 2 – multi dimensional array adder
# Description: This program will create two 100x100 2D arrays
#		and add them together using a loop and the + operator 
#		1000 times, recording the average times to show the differences
#		in efficiency. This program shows that the + operator
#		from numpy is several orders of magnitude faster than 
#		a double for loop method.

from matplotlib import pyplot as plt
import numpy as np 
import time
import math


# adding using for loops
def loop_add(arr1, arr2):
	arr3 = np.full((100,100),0)					# init array to return using numpy
	for x, a in enumerate(arr1):				# iterate through rows in arr1 keeping track of index
		for y, b in enumerate(a):				# iterate through each element in arr1 keeping track of index
			arr3[x,y] = b + arr2[x,y]			# add current element to the element in the same index spot in arr2


	return arr3



# adding using the + operator
def op_add(arr1, arr2):
	arr3 = arr1 + arr2							# init arr3 with the added arr1 nd arr2 using + operator
	return arr3



# execute the different adding methods 1000 times
def adder(): 
	# initialize two 100x100 2D arrays with 5 as every element using numpy
	arr1 = np.full((100,100), 5)
	arr2 = np.full((100,100), 5)
	loop_times = []
	op_times = []

	# add two arrays using for loop
	for x in range(0,1000):
		start = time.time()						# time stamp
		arrLooped = loop_add(arr1, arr2)		# add using loop addition
		end = time.time()
		loop_times.append(end - start)			# put times to complete addition in list
	loop_vector = np.array(loop_times)			# store times for loop addition in vector

	# add two arrays using + operator
	for x in range(0,1000):
		start = time.time()						# time stamp 
		arrOped = op_add(arr1, arr2)			# add using operator
		end = time.time()
		op_times.append(end - start)			# put times to complete addition using operator in list
	op_vector = np.array(op_times) 				# store times for operator addition in vector

	# calculate averages and standard deviations
	loop_avg = np.mean(loop_vector)				# loop average time
	loop_stdev = np.std(loop_vector)			# loop standard deviation
	op_avg = np.mean(op_vector)					# operator add average time
	op_stdev = np.std(op_vector)				# operator add standard deviation

	# loop_hist = np.histogram(loop_vector)		# histogram for loop times vector
	# op_hist = np.histogram(op_vector)			# histogram for operator add times vector




	print("Average times for loop iterations: ", loop_avg, " and standard deviation: ", loop_stdev)
	print("Average times for operator iterations: ", op_avg, " and standard deviation: ", op_stdev)
	print("Loop times histogram: ")
	plt.hist(loop_vector, bins=np.linspace(0.0015, 0.0025, 30))	# create histogram for the loop times vector
	plt.title("Loop Times Histogram")							# assign name
	plt.show()													# display the loop vector histogram
	print("Operator times histogram: ")
	plt.hist(op_vector,bins=np.linspace(0.000001, 0.000005,30))	# create histogram for the operator times vector
	plt.title("Operator Times Histogram")						# assign and display 
	plt.show()


	return 0


#execute the adder function
adder()