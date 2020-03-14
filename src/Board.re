/* Check Adjacent and follow path, looking for a next step and exiting if none.
 * The idea is that we crawl to the left and down, we check adjacent squares to see
 * if we should investigate a path.
 *
 *  0 | 1 | 2
 * ---|---|---
 *  3 | 4 | 5 
 * ---|---|---
 *  6 | 7 | 8
 * 
 * Starting Postions are:
 * 0, 2, 3, 6
 * 
 *   1 - 2 E
 *  / 
 * 0 - 4 - 8 SE
 *  \ 
 *   3 - 6 S
 *
 * 1 - 4 -7 S
 *
 * 2 - 5 - 8 S
 *  \
 *   4 - 6 SW
 * 
 * 3 - 4 - 5 E
 *
 * 6 - 7 - 8 E
 * 
 * Given a list of strings
 * [X, O, X, O, X, X, X, O, O]
 * 
 * Correpsonding to
 * 
 *  X | O | X
 * -----------
 *  O | X | X
 * -----------
 *  X | O | O
 * 
 * i = 0
 * previousDirection = null
 * squares[i] = "X"
 *
 * adjacents = {
 *  east: "O",
 *  south: "O",
 *  southeast: "X",
 *  southwest: ()
 * }
 * 
 * Choose next step
 * -> southeast
 * 
 * ---
 * 
 * i = 4
 * previousDirection = SOUTHEAST
 * squares[i] = "X"
 * adjacents = {
 *  east: ()
 *  south: ()
 *  southeast: "O"
 *  southwest: ()
 * }
 *
 * Choose next step
 * -> NO PATH
 *
 * ---
 *
 * i = 2
 * previousDirection = null
 * squares[i] = "O"
 * adjacents = {
 *   east: ()
 *   south: "X"
 *   southeast: ()
 *   southwest: ()
 * }
 *
 * Choose next step
 * -> NO PATH
 *
 */

type directionVariant =
  | EAST
  | SOUTHEAST
  | SOUTH
  | SOUTHWEST;

let checkInDirection = (i, direction, squares) => {
  switch (direction) {
    | SOUTH when i <= 5 => squares[i+3]
    | SOUTH => ()
    | SOUTHEAST when i mod 4 == 0 => squares[i+4]
    | SOUTHEAST => ()
    | EAST when i mod 3 == 0 => squares[i+1]
    | EAST => ()
    | SOUTHWEST when i mod 2  == 0 && i > 6 => squares[i+2]
    | SOUTHWEST => ()
  };
};

let checkAdjacent = (i, squares) => {
  switch(i) {
  | _ => ()
  };
}


let lookForPath = (i, squares, ~direction=()) => {
    let adjacents = checkAdjacent(i, squares)
};

let investigatePath = () => {};

type adjacentSquares = {
    east: string,
    southeast: string,
    south: string,
    southwest: string
}

/* Know which cells are adjacent to what */
let checkAdjacent = (i, squares) => {
    switch (i) {
    | 0 => {east: checkInDirection(0, EAST, squares)}
    | 1 =>
    | 2 =>
    | 3 =>
    | 4 =>
    | 5 =>
    | 6 =>
    | 7 =>
    | _ => ()
    };
};

let calculateWinner = (i, squares) => {
  switch (i) {
    | 
    | _ => ()
  }
};

let calculateWinner = squares => {
  switch (squares) {
  | "" => ""
  | 
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
