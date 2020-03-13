[@react.component]
let make = (~value, ~onClick) => {
  <button className="square" onClick={_ => onClick()}>
    {value->React.string}
  </button>
};
