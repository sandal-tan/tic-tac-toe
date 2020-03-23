/**
 * Recusrively get the indexes of an element in a List
 */
let rec getIndexes = (a, elem, idx) => {
  switch (a) {
  | [] => []
  | [h, ...r] when h == elem => [idx, ...getIndexes(r, elem, idx + 1)]
  | [_, ...r] => [...getIndexes(r, elem, idx + 1)]
  };
};

/**
 * Recusrively check if a list contains an element.
 */
let rec listContains = (a, elem) => {
  switch (a) {
  | [] => false
  | [h, ..._] when h == elem => true
  | [_, ...r] => listContains(r, elem)
  };
};

/**
 * Check to see if a player has won based on their square precense.
 * This recurisvely looks at the indexes of a players pieces and 
 */
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
let make = () =>{

  /* Game State */
  let (history, setHistory) = React.useState(() => [Array.make(9, "")]);
  let (xIsNext, setXIsNext) = React.useState(() => true);
  let (stepNumber, setStepNumber) = React.useState(() => 0);

  let currentSquares = stepNumber|>List.nth(history);

  let xSquares = getIndexes(currentSquares->Array.to_list, "X", 0);
  let oSquares = getIndexes(currentSquares->Array.to_list, "O", 0);
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

  let handleClick = i => {
    if (winner == "" && currentSquares[i] == "") {
      let squaresCopy = currentSquares->Array.copy;
      Array.set(squaresCopy, i, xIsNext ? "X" : "O");
      setHistory(hist => [squaresCopy] |> List.append(hist));
      setXIsNext(xIsNext => ! xIsNext);
      setStepNumber(stepNumber => stepNumber + 1)
    }
  };

  let jumpTo = step: int => {
    setStepNumber(step);
    setXIsNext(_ => {(step mod 0) == 0});
  };

  let traverseHistory = (step, move) => {
    let desc = move != 0 ? "Go to move #" ++ move->string_of_int : "Go to game start";
    <li>
      <button onClick={() => jumpTo(step)}>{desc}</button>
    </li>
  };

  let moves = history|>List.mapi(traverseHistory);

/* ---------- JSX --------------- */
  <div className="game">
    <div className="game-board">
      <Board
        squares={currentSquares}
        onClick={(i) => handleClick(i)}
      />
    </div>
    <div className="game-info">
      <div>{status()->React.string}</div>
      <ol>{moves}</ol>
    </div>
  </div>
};
