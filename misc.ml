let do_option f = function
    Some x -> f x
  | None -> ()

let push l x = (l := x :: !l)
