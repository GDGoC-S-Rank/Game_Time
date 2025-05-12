import "./Stage7.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/light/bg.png";
import control_panel from "../resources/images/fontImg/11.png";
import control_1p from "../resources/images/fontImg/L1p.png";
import { useKeyEffect2 } from "../hooks/useKeyEffect2";

// Exit path
export function Stage7() {
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
    <div className="stage7-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage7_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="stage7-bgImage" />
    </div>
  );
}
