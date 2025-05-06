import "./Stage2.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import heartBg from "../resources/images/hs/hbg.png";
import hfloor from "../resources/images/hs/hfloor.png";
import control_panel from "../resources/images/fontImg/15.png";
import control_1p from "../resources/images/fontImg/cube.png";
import control_2p from "../resources/images/fontImg/exchangeRB.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// Heart Star
export function Stage2() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);
  const [isVisible_2p, setIsVisible_2p] = useState(false);

  useKeyEffect((key) => {
    if (key === "Space") {
      setIsVisible_1p(true);
      setTimeout(() => setIsVisible_1p(false), 300);
    } else if (key === "ArrowUp") {
      setIsVisible_2p(true);
      setTimeout(() => setIsVisible_2p(false), 300);
    }
  });

  return (
    <div className="stage2-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={hfloor} alt="hfloor" className="hfloor" />
      <img src={heartBg} alt="heartBg" className="heartBg" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="control_1p"
        className={`stage2_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="control_2p"
        className={`stage2_control_2p ${isVisible_2p ? "visible" : ""}`}
      />
    </div>
  );
}
