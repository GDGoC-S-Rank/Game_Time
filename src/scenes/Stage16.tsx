import "./Stage16.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/ending.png";
import control_1p from "../resources/images/fontImg/minicube.png";
import control_panel from "../resources/images/fontImg/24.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// End Scene
export function Stage16() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);

  useKeyEffect((key) => {
    if (key === "Space") {
      setIsVisible_1p(true);
      setTimeout(() => setIsVisible_1p(false), 300);
    }
  });

  return (
    <div className="stage16-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage16_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="bgImage" />
    </div>
  );
}
