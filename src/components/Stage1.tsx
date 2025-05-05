import "./Stage1.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/startScene/bg.png";
import control_1p from "../resources/images/fontImg/minicube.png";
import { useSpaceKeyEffect } from "../hooks/useSpaceKeyEffect";

// Start Scene(Space is key)
export function Stage1() {
  const [isVisible, setIsVisible] = useState(false);

  useSpaceKeyEffect(() => {
    setIsVisible(true);
    setTimeout(() => setIsVisible(false), 300);
  });

  return (
    <div className="stage1-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`control_1p ${isVisible ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="bgImage" />
    </div>
  );
}
