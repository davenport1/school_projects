
(* 
Matthew Davenport 
COEN 171 HW 3
Binary search tree functions insert and member in ML 
	*)

datatype tree = empty | node of (int * tree * tree);

fun insert empty x = node (x, empty, empty) 
	| insert (node (data, left, right))
		if data = x 
			node(data, left, right)
		else if data < x
			node(data, left, insert right x)
		else
			node(data, right, insert left x);

fun member empty x = false
	| member (node(data, left, right)) x = 
		 if data = x then
            true
        else if x < data then
            member left x
        else
            member right x;
