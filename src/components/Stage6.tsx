import "./Stage6.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/light/bg.png";
import control_panel from "../resources/images/fontImg/11.png";
import control_1p from "../resources/images/fontImg/L1p.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// Spikes tend to kill you
export function Stage6() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);

  useKeyEffect((key) => {
    if (key === "Space") {
      setIsVisible_1p(true);
      setTimeout(() => setIsVisible_1p(false), 300);
    }
  });

  return (
    <div className="stage6-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_panel}
        alt="control_panel"
        className="stage6_control_panel"
      />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage6_control_1p ${isVisible_1p ? "visible" : ""}`}
      />

      <img src={bgImage} alt="bg" className="stage6-bgImage" />
    </div>
  );
}
