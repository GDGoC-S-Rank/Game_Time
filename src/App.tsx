import "./App.css";
import { useState } from "react";
import { Stage1 } from "./scenes/Stage1";
import { Stage2 } from "./scenes/Stage2";
import { Stage3 } from "./scenes/Stage3";
import { Stage4 } from "./scenes/Stage4";
import { Stage5 } from "./scenes/Stage5";
import { Stage6 } from "./scenes/Stage6";
import { Stage7 } from "./scenes/Stage7";
import { Stage8 } from "./scenes/Stage8";
import { Stage9 } from "./scenes/Stage9";
import { Stage10 } from "./scenes/Stage10";
import { Stage11 } from "./scenes/Stage11";
import { Stage12 } from "./scenes/Stage12";
import { Stage13 } from "./scenes/Stage13";
import { Stage14 } from "./scenes/Stage14";
import { Stage15 } from "./scenes/Stage15";
import { Stage16 } from "./scenes/Stage16";

export default function App() {
  const [stage, setStage] = useState(1);

  return (
    <div onClick={() => setStage((prev) => prev + 1)}>
      {stage === 1 && <Stage1 />} {/* Start Scene(Space is key) */}
      {stage === 2 && <Stage2 />} {/* Heart Star */}
      {stage === 3 && <Stage3 />} {/* The Worlds Hardest Game */}
      {stage === 4 && <Stage4 />} {/* Crazy Traker */}
      {stage === 5 && <Stage5 />} {/* Light On Blue */}
      {stage === 6 && <Stage6 />} {/* Spikes tend to kill you */}
      {stage === 7 && <Stage7 />} {/* Exit path */}
      {stage === 8 && <Stage8 />} {/* Fear Less! */}
      {stage === 9 && <Stage9 />} {/* Last egg alive */}
      {stage === 10 && <Stage10 />} {/* Click drag type */}
      {stage === 11 && <Stage11 />} {/* pwong */}
      {stage === 12 && <Stage12 />} {/* Tower of heaven */}
      {stage === 13 && <Stage13 />} {/* anbot */}
      {stage === 14 && <Stage14 />} {/* Spewer */}
      {stage === 15 && <Stage15 />} {/* The I Of It */}
      {stage === 16 && <Stage16 />} {/* End Scene */}
    </div>
  );
}

// useState 값을 바꿔서 원하는 맵으로 이동하면 되는데 ;;
