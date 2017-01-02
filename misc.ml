let do_option f = function
    Some x -> f x
  | None -> ()
