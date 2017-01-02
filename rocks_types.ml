open Result

type status_t = {code : int ; subcode : int ; msg : string option }
let format_status st =
  Printf.sprintf "<%d, %d, %s>\n" st.code st.subcode
    (match st.msg with None -> "<>"
    | Some s -> Printf.sprintf "\"%s\"" (String.escaped s))

let status_to_result st =
  if 0 == st.code then Ok ()
  else Error (format_status st)

let status2_to_result (st, rv) =
  if 0 == st.code then Ok rv
  else Error (format_status st)

let status3_to_result (st, rv1, rv2) =
  if 0 == st.code then Ok (rv1, rv2)
  else Error (format_status st)

let error_to_failure ?(msg="") = function
  | Error s -> 
    failwith (msg^": "^s)
  | Ok s -> s

let error_to_assert_failure = function
  | Error s ->
    assert false
  | Ok s -> s

let none_to_failure ?(msg="") = function
  | None -> 
    failwith msg
  | Some s -> s
