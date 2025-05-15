import "./Stage14.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/spewer/bg1.png";
import control_panel from "../resources/images/fontImg/17.png";
import control_1p from "../resources/images/fontImg/spewer1p.png";
import control_2p from "../resources/images/fontImg/spew_float.png";
import { useKeyEffect2 } from "../hooks/useKeyEffect2";

// Spewer
export function Stage14() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);
  const [isVisible_2p, setIsVisible_2p] = useState(false);

  useKeyEffect2(
    (key) => {
      if (key === "Space") {
        setIsVisible_1p(true);
      } else if (key === "ArrowUp") {
        setIsVisible_2p(true);
      }
    },
    (key) => {
      if (key === "Space") {
        setIsVisible_1p(false);
      } else if (key === "ArrowUp") {
        setIsVisible_2p(false);
      }
    }
  );

  return (
    <div className="stage14-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage14_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="contral_2p"
        className={`stage14_control_2p ${isVisible_2p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="stage14-bgImage" />
    </div>
  );
}
