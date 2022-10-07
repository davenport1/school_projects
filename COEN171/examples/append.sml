(* append_tupled: 'a list * 'a list -> 'a list *)

fun append_tupled (nil, ys) = ys
  | append_tupled (x::xs, ys) = x :: append_tupled(xs, ys);


(* append_curried: 'a list -> 'a list -> 'a list *)

fun append_curried nil ys = ys
  | append_curried (x::xs) ys = x :: append_curried xs ys;
