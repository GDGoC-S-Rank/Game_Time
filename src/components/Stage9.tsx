import "./Stage9.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage1 from "../resources/images/egg/bg1.png";
import bgImage2 from "../resources/images/egg/bg2.png"; // object
import control_1p from "../resources/images/fontImg/cube.png";
import control_2p from "../resources/images/fontImg/useitem.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// Last egg alive
export function Stage9() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);
  const [isVisible_2p, setIsVisible_2p] = useState(false);

  useKeyEffect((key) => {
    if (key === "Space") {
      setIsVisible_1p(true);
      setTimeout(() => setIsVisible_1p(false), 300);
    } else if (key === "ArrowUp") {
      setIsVisible_2p(true);
      setTimeout(() => setIsVisible_2p(false), 300);
    }
  });

  return (
    <div className="stage9-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage9_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="contral_2p"
        className={`stage9_control_2p ${isVisible_2p ? "visible" : ""}`}
      />
      <img src={bgImage1} alt="bg1" className="stage9-bgImage1" />
      <img src={bgImage2} alt="bg2" className="stage9-bgImage2" />
    </div>
  );
}
