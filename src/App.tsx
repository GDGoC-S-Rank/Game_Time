import "./App.css";
import { useState } from "react";
import { Stage1 } from "./components/Stage1";
import { Stage2 } from "./components/Stage2";
import { Stage3 } from "./components/Stage3";
import { Stage4 } from "./components/Stage4";

export default function App() {
  const [stage, setStage] = useState(1);

  return (
    <div onClick={() => setStage((prev) => prev + 1)}>
      {stage === 1 && <Stage1 />}
      {stage === 2 && <Stage2 />}
      {stage === 3 && <Stage3 />}
      {stage === 4 && <Stage4 />}
    </div>
  );
}
