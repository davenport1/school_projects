fun filter f nil = nil
  | filter f (x::xs) = if f x then x :: filter f xs else filter f xs;

fun quicksort nil = nil
  | quicksort (x::xs) =
	let
	    fun above y = y >= x
	    fun below y = y < x
	in
	    quicksort (filter below xs) @ x :: quicksort (filter above xs)
	end;

