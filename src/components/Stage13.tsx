import "./Stage13.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/light/bg.png";
import control_panel from "../resources/images/fontImg/11.png";
import control_1p from "../resources/images/fontImg/L1p.png";
import control_2p from "../resources/images/fontImg/L2p.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// Anbot
export function Stage13() {
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
    <div className="stage13-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_panel}
        alt="control_panel"
        className="stage13_control_panel"
      />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage13_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="contral_2p"
        className={`stage13_control_2p ${isVisible_2p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="stage13-bgImage" />
    </div>
  );
}
