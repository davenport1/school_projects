(* demonstrates how each val declaration creates a new name and binding *)

val x = 1;
fun f y = x + y;	(* always adds one to its parameter *)
val x = 2;		(* this is a different x *)
f 7;			(* 8 and not 9 *)

fun g y = x * y;	(* always doubles it parameter *)
val x = 3;		(* another different x *)
g 8;			(* 16 and not 24 *)


(* demonstrates how each fun declarations creates a new name and binding,
   but be careful of the different between val and fun bindings *)

fun h y = y;
fun h y = if y = 1 then 1 else y * h (y - 1);		(* different h *)
h 4;							(* 4 * 3 * 2 * 1 = 24 *)

fun q y = y;
val q = fn y => if y = 1 then 1 else y * q (y - 1);	(* q from above *)
q 4;							(* 4 * 3 = 12 *)
