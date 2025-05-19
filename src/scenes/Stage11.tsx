import "./Stage11.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/black.png";
import bgImage2 from "../resources/images/pwong/w1.png";
import control_panel from "../resources/images/fontImg/01.png";
import control_1p from "../resources/images/fontImg/goleft.png";
import control_2p from "../resources/images/fontImg/goright.png";
import { useKeyEffect2 } from "../hooks/useKeyEffect2";

// Pwong
export function Stage11() {
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
    <div className="stage11-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage11_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="contral_2p"
        className={`stage11_control_2p ${isVisible_2p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="stage11-bgImage" />
      <img src={bgImage2} alt="bg2" className="stage11-bgImage2" />
    </div>
  );
}
