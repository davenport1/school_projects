# Class: COEN 140 Lab Machine Learning/Data Mining
# Name: Matthew Davenport
# Date: 9/25/2022
# Title: Lab 2 – dot product calculator
# Description: This program will create two 100 element vectors
#		and calculate their dot product using a loop and the dot product 
#		function from numpy 1000 times, recording the average times 
# 		to show the differences in efficiency. The program shows
#		that the dot product function from numpy is still an order of magnitude
#		faster than a conventional for loop. 

from matplotlib import pyplot as plt
import numpy as np 
import time
import math


# dot product using for loop
def loop_dot(v1, v2):
	dot_prod = 0
	for x, a in enumerate(v1):				# iterate through rows in arr1 keeping track of index
		dot_prod += a * v2[x]


	return dot_prod



# dot_product using dot product function from numpy
def op_dot(v1,v2):
	dot_prod = np.dot(v1,v2)
	return dot_prod




# execute the different dot product methods 1000 times
def adder(): 
	# initialize two 100 element vectors
	v1 = np.full((100), 5)
	v2 = np.full((100), 5)
	loop_times = []
	op_times = []

	# dot product using for loop
	for x in range(0,1000):
		start = time.time()						# time stamp
		dotLooped = loop_dot(v1, v2)			# dot product using loop
		end = time.time()
		loop_times.append(end - start)			# put times to complete dot product in list
	loop_vector = np.array(loop_times)			# store times for loop dot product in vector

	# add two arrays using + operator
	for x in range(0,1000):
		start = time.time()						# time stamp 
		dotOped = op_dot(v1, v2)				# dot produt using operator
		end = time.time()
		op_times.append(end - start)			# put times to complete dot product using operator in list
	op_vector = np.array(op_times) 				# store times for operator dot product in vector

	# calculate averages and standard deviations
	loop_avg = np.mean(loop_vector)				# loop average time
	loop_stdev = np.std(loop_vector)			# loop standard deviation
	op_avg = np.mean(op_vector)					# operator average time
	op_stdev = np.std(op_vector)				# operator standard deviation

	# loop_hist = np.histogram(loop_vector)		# histogram for loop times vector
	# op_hist = np.histogram(op_vector)			# histogram for operator add times vector




	print("Average times for loop iterations: ", loop_avg, " and standard deviation: ", loop_stdev)
	print("Average times for operator iterations: ", op_avg, " and standard deviation: ", op_stdev)
	print("Loop times histogram: ")
	plt.hist(loop_vector, bins=np.linspace(0.00001, 0.00002, 30))	# create histogram for the loop times vector
	plt.title("Loop Times Histogram")							# assign name
	plt.show()													# display the loop vector histogram
	print("Operator times histogram: ")
	plt.hist(op_vector,bins=np.linspace(0.000001, 0.000005,30))	# create histogram for the operator times vector
	plt.title("Operator Times Histogram")						# assign and display 
	plt.show()


	return 0


#execute the adder function
adder()