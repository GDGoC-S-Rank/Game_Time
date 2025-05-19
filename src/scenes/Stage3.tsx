import "./Stage3.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/world/bg.png";
import control_panel from "../resources/images/fontImg/13.png";
import control_1p from "../resources/images/fontImg/14.png";
import { useKeyEffect2 } from "../hooks/useKeyEffect2";

// The Worlds Hardest Game
export function Stage3() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);

  useKeyEffect2(
    (key) => {
      if (key === "Space") {
        setIsVisible_1p(true);
      }
    },
    (key) => {
      if (key === "Space") {
        setIsVisible_1p(false);
      }
    }
  );

  return (
    <div className="stage3-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage3_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="stage3-bgImage" />
    </div>
  );
}
