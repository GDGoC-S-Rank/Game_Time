import "./Stage10.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/drag/bg.png";
import control_1p from "../resources/images/fontImg/turnL.png";
import control_2p from "../resources/images/fontImg/TurnR.png";
import { useKeyEffect2 } from "../hooks/useKeyEffect2";

// Click drag type
export function Stage10() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);
  const [isVisible_2p, setIsVisible_2p] = useState(false);

  useKeyEffect2(
    (key: string) => {
      if (key === "Space") {
        setIsVisible_1p(true);
      } else if (key === "ArrowUp") {
        setIsVisible_2p(true);
      }
    },
    (key: string) => {
      if (key === "Space") {
        setIsVisible_1p(false);
      } else if (key === "ArrowUp") {
        setIsVisible_2p(false);
      }
    }
  );

  return (
    <div className="stage10-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage10_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="contral_2p"
        className={`stage10_control_2p ${isVisible_2p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="stage10-bgImage" />
    </div>
  );
}
