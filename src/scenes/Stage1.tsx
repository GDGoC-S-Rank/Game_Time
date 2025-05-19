import "./Stage1.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/startScene/bg.png";
import control_1p from "../resources/images/fontImg/minicube.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// Start Scene(Space is key)
export function Stage1() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);

  useKeyEffect((key) => {
    if (key === "Space") {
      setIsVisible_1p(true);
      setTimeout(() => setIsVisible_1p(false), 300);
    }
  });

  return (
    <div className="stage1-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage1_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="bgImage" />
    </div>
  );
}
