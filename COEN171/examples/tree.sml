datatype 'a tree = empty | node of 'a tree * 'a * 'a tree;

fun height empty = 0
  | height (node(l,_,r)) =
	let
	    val lh = height l
	    val rh = height r
	in
	    if lh > rh then 1 + lh else 1 + rh
	end;
