let rec getIndexes = (a, elem, idx) => {
  switch (a) {
  | [] => []
  | [h, ...r] when h == elem => [idx, ...getIndexes(r, elem, idx + 1)]
  | [_, ...r] => [...getIndexes(r, elem, idx + 1)]
  };
};

let rec listContains = (a, elem) => {
  switch (a) {
  | [] => false
  | [h, ..._] when h == elem => true
  | [_, ...r] => listContains(r, elem)
  };
};

let rec playerHasWon = squares => {
  switch (squares) {
  | [] => false
  | [0, 1, 2, ..._] => true
  | [3, 4, 5, ..._] => true
  | [6, 7, 8] => true
  | [0, ...r] when listContains(r, 4) && listContains(r, 8) => true
  | [0, ...r] when listContains(r, 3) && listContains(r, 6) => true
  | [1, ...r] when listContains(r, 4) && listContains(r, 7) => true
  | [2, ...r] when listContains(r, 4) && listContains(r, 6) => true
  | [2, ...r] when listContains(r, 5) && listContains(r, 8) => true
  | [_, ...r] => playerHasWon(r)
  };
};

[@react.component]
let make = () => {

  let (squares, setSquares) = React.useState(() => Array.make(9, ""));
  let (xIsNext, setXIsNext) = React.useState(() => true);

  let handleClick = i => {
    let squaresCopy = squares->Array.copy;
    Array.set(squaresCopy, i, xIsNext ? "X" : "O");
    setSquares(_ => squaresCopy);
    setXIsNext(xIsNext => ! xIsNext);
  };

  let renderSquare = i => <Square value={i |> Array.get(squares)} onClick={() => handleClick(i)} />;

  let xSquares = getIndexes(squares->Array.to_list, "X", 0);
  let oSquares = getIndexes(squares->Array.to_list, "O", 0);
  let xIsWinner = playerHasWon(xSquares);
  let oIsWinner = playerHasWon(oSquares);
  let winner = xIsWinner ? "X" : oIsWinner ? "O" : "";
  
  let status = () => {
    switch (winner) {
    | "X" => "Winner: X"
    | "O" => "Winner: O"
    | "" | _ => "Next player: " ++ (xIsNext ? "X" : "O")
    };
  };

  <div>
    <div className="status">{status()->React.string}</div>
    <div className="board-row">
      {renderSquare(0)}
      {renderSquare(1)}
      {renderSquare(2)}
    </div>
    <div className="board-row">
      {renderSquare(3)}
      {renderSquare(4)}
      {renderSquare(5)}
    </div>
    <div className="board-row">
      {renderSquare(6)}
      {renderSquare(7)}
      {renderSquare(8)}
    </div>
  </div>
};
