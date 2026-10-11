(* OCaml: immutable lists and higher-order functions. *)
let mean values =
  match values with
  | [] -> invalid_arg "Input cannot be empty"
  | _ ->
      let total = List.fold_left ( +. ) 0.0 (List.map float_of_int values) in
      total /. float_of_int (List.length values)

let median values =
  let sorted = List.sort compare values in
  let n = List.length sorted in
  if n = 0 then invalid_arg "Input cannot be empty"
  else if n mod 2 = 1 then float_of_int (List.nth sorted (n / 2))
  else
    (float_of_int (List.nth sorted (n / 2 - 1))
     +. float_of_int (List.nth sorted (n / 2))) /. 2.0

let modes values =
  if values = [] then invalid_arg "Input cannot be empty";
  let frequencies =
    List.fold_left
      (fun counts x ->
        let current = match List.assoc_opt x counts with Some n -> n | None -> 0 in
        (x, current + 1) :: List.remove_assoc x counts)
      [] values
  in
  let highest = List.fold_left (fun acc (_, n) -> max acc n) 0 frequencies in
  if highest = 1 then []
  else frequencies
       |> List.filter (fun (_, n) -> n = highest)
       |> List.map fst
       |> List.sort compare

let () =
  let values = [4; 2; 7; 2; 9; 4; 2] in
  Printf.printf "OCaml (Functional) | Count: %d\n" (List.length values);
  Printf.printf "Mean: %.2f\nMedian: %.2f\n" (mean values) (median values);
  match modes values with
  | [] -> print_endline "Mode: none (all values occur once)"
  | result ->
      Printf.printf "Mode(s): %s\n"
        (String.concat ", " (List.map string_of_int result))
