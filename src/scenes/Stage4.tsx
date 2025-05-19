import "./Stage4.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/traker/bg.png";
import bgImage2 from "../resources/images/traker/bg2.png";
import control_panel from "../resources/images/fontImg/05.png";
import control_1p from "../resources/images/fontImg/06.png";
import { useKeyEffect2 } from "../hooks/useKeyEffect2";

// Crazy Traker
export function Stage4() {
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
    <div className="stage4-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage4_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img src={bgImage} alt="bg" className="stage4-bgImage" />
      <img src={bgImage2} alt="bg2" className="stage4-bgImage2" />
    </div>
  );
}
