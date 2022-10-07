(* ML lists in ML.  The names have been changed to avoid conflicts. *)

datatype 'a List = Nil | ::: of 'a * 'a List;

infixr 5 :::;


(* Null: 'a List -> bool *)

fun Null Nil = true
  | Null _   = false;


(* Hd: 'a List -> 'a *)

fun Hd Nil = raise Empty
  | Hd (x:::_) = x;


(* Tl: 'a List -> 'a List *)

fun Tl Nil = raise Empty
  | Tl (_:::xs) = xs;


(* Length: 'a List -> int *)

fun Length Nil = 0
  | Length (_:::xs) = 1 + Length xs;


(* @@: 'a List * 'a List -> 'a List *)

fun @@ (Nil, ys) = ys
  | @@ (x:::xs, ys) = x ::: @@ (xs, ys);

infixr 5 @@;


(* cvt: 'a list -> 'a List *)

fun cvt nil = Nil
  | cvt (x::xs) = x ::: cvt xs;


val List1 = cvt [1, 2, 3];
val List2 = cvt [4, 5, 6];

List1 @@ List2;
