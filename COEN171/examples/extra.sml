(* minlist: int list -> int
   return the smallest value in a list *)

fun minlist nil = raise Empty
  | minlist [x] = x
  | minlist (x::xs) = if x < minlist xs then x else minlist xs;


(* minlist: int list -> int
   same function but with a local let to avoid recursing twice *)

fun minlist nil = raise Empty
  | minlist [x] = x
  | minlist (x::xs) = let val mintail = minlist xs in
			if x < mintail then x else mintail end;


(* atleast: int x int list -> int
   return count of number of items whose value is at least a given value *)

fun atleast (v, nil) = 0
  | atleast (v, x::xs) = if x >= v then 1 + atleast (v, xs) else atleast (v, xs);


(* atleast: int -> int list -> int
   curried version of the same function *)

fun atleast v nil = 0
  | atleast v (x::xs) = if x >= v then 1 + atleast v xs else atleast v xs;
