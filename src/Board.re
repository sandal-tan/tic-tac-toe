/* Check Adjacent and follow path, looking for a next step and exiting if none.
 * The idea is that we crawl to the left and down, we check adjacent squares to see
 * if we should investigate a path.
 *
 *  0 | 1 | 2
 * ---|---|---
 *  3 | 4 | 5 
 * ---|---|---
 *  6 | 7 | 8
 */

type directionVariant =
  | EAST
  | SOUTHEAST
  | SOUTH
  | SOUTHWEST;

/* TODO: Actually handle cases */
let checkInDirection = (i, direction, squares) => {
  switch (direction) {
    | SOUTH when i <= 5 => squares[i+3]
    | SOUTH => ()
    | SOUTHEAST when Num.i mod 4 == 0 => squares[i+4]
    | EAST => squares[i+1]
    | SOUTHWEST => squares[i+2]
  };
};

/* Know which cells are adjacent to what */
let checkAdjacent = (_i, _squares) => {

};

let calculateWinner = squares => {
  switch (squares) {
  | [||] => ""
  | _ => ""
  };
};

[@react.component]
let make = () => {

  let (squares, setSquares) = React.useState(() => Array.make(9, ""));
  let (xIsNext, setXIsNext) = React.useState(() => true);

  let handleClick = i => {
    let squaresCopy = squares->Array.copy;
    Array.set(squaresCopy, i, xIsNext ? "X" : "O");
    setSquares(_squares => squaresCopy);
    setXIsNext(xIsNext => ! xIsNext);
  };

  let renderSquare = i => <Square value={i |> Array.get(squares)} onClick={() => handleClick(i)} />;






  
  let winner = calculateWinner(squares);
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
